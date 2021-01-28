#include "Common.hlsl"

struct ShadowHitInfo {
  bool isHit;
  float4 vertinfo;
};

struct sceneLightInfo_t {
	float4 origin_radius;
	float4 light_color;
	float4 light_clamp;
	float4 light_color2;
};

// #DXR Extra: Perspective Camera
cbuffer CameraParams : register(b0)
{
  float4 timeViewOrg;
  float4 skyInfo;
  float4 fogInfo;
  float4 notUsed1;
  float4x4 projection;
  float4x4 viewI;
  float4x4 projectionI;
}


StructuredBuffer<STriVertex> BTriVertex : register(t0);
Texture2D<float4> MegaTexture : register(t1);
StructuredBuffer<SInstanceProperties> BInstanceProperties : register(t2);
RaytracingAccelerationStructure SceneBVH : register(t3);
StructuredBuffer<sceneLightInfo_t> lightInfo : register(t4);
Texture2D<float4> MegaTextureNormal : register(t5);

float3 QuakeCoords(float3 xyz) {
	return float3(xyz.x, -xyz.z, xyz.y);
}

float attenuation(float r, float f, float d, float3 normal, float3 dir) {
	float angle = dot (dir, normal);
	
	return (r / pow(d, 1.3)) * angle;
}
float attenuation_arealight(float r, float f, float d, float3 normal, float3 dir) {
	float angle = dot (dir, normal);
	return (r / pow(d, 1.3)) * angle;
}

// Utility function to get a vector perpendicular to an input vector 
//    (from "Efficient Construction of Perpendicular Vectors Without Branching")
float3 getPerpendicularVector(float3 u)
{
	float3 a = abs(u);
	uint xm = ((a.x - a.y)<0 && (a.x - a.z)<0) ? 1 : 0;
	uint ym = (a.y - a.z)<0 ? (1 ^ xm) : 0;
	uint zm = 1 ^ (xm | ym);
	return cross(u, float3(xm, ym, zm));
}

// Generates a seed for a random number generator from 2 inputs plus a backoff
uint initRand(uint val0, uint val1, uint backoff = 16)
{
	uint v0 = val0, v1 = val1, s0 = 0;

	[unroll]
	for (uint n = 0; n < backoff; n++)
	{
		s0 += 0x9e3779b9;
		v0 += ((v1 << 4) + 0xa341316c) ^ (v1 + s0) ^ ((v1 >> 5) + 0xc8013ea4);
		v1 += ((v0 << 4) + 0xad90777d) ^ (v0 + s0) ^ ((v0 >> 5) + 0x7e95761e);
	}
	return v0;
}

// Takes our seed, updates it, and returns a pseudorandom float in [0..1]
float nextRand(inout uint s)
{
	s = (1664525u * s + 1013904223u);
	return float(s & 0x00FFFFFF) / float(0x01000000);
}

// Get a cosine-weighted random vector centered around a specified normal direction.
float3 getCosHemisphereSample(inout uint randSeed, float3 hitNorm)
{
	// Get 2 random numbers to select our sample with
	float2 randVal = float2(nextRand(randSeed), nextRand(randSeed));

	// Cosine weighted hemisphere sample from RNG
	float3 bitangent = getPerpendicularVector(hitNorm);
	float3 tangent = cross(bitangent, hitNorm);
	float r = sqrt(randVal.x);
	float phi = 2.0f * 3.14159265f * randVal.y;

	// Get our cosine-weighted hemisphere lobe sample direction
	return tangent * (r * cos(phi).x) + bitangent * (r * sin(phi)) + hitNorm.xyz * sqrt(1 - randVal.x);
}


bool IsLightShadowed(float3 worldOrigin, float3 lightDir, float distance, float3 normal)
{	
	 // Fire a shadow ray. The direction is hard-coded here, but can be fetched
     // from a constant-buffer
     RayDesc ray;
     ray.Origin = worldOrigin;
     ray.Direction = lightDir;
     ray.TMin = 0.01;
     ray.TMax = distance;
     bool hit = true;
     
     // Initialize the ray payload
     ShadowHitInfo shadowPayload;
     shadowPayload.isHit = false;
     
     // Trace the ray
     TraceRay(
     	// Acceleration structure
     	SceneBVH,
     	// Flags can be used to specify the behavior upon hitting a surface
     	RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH | RAY_FLAG_CULL_FRONT_FACING_TRIANGLES,
     	// Instance inclusion mask, which can be used to mask out some geometry to
     	// this ray by and-ing the mask with a geometry mask. The 0xFF flag then
     	// indicates no geometry will be masked
     	0x80,
     	// Depending on the type of ray, a given object can have several hit
     	// groups attached (ie. what to do when hitting to compute regular
     	// shading, and what to do when hitting to compute shadows). Those hit
     	// groups are specified sequentially in the SBT, so the value below
     	// indicates which offset (on 4 bits) to apply to the hit groups for this
     	// ray. In this sample we only have one hit group per object, hence an
     	// offset of 0.
     	1,
     	// The offsets in the SBT can be computed from the object ID, its instance
     	// ID, but also simply by the order the objects have been pushed in the
     	// acceleration structure. This allows the application to group shaders in
     	// the SBT in the same order as they are added in the AS, in which case
     	// the value below represents the stride (4 bits representing the number
     	// of hit groups) between two consecutive objects.
     	0,
     	// Index of the miss shader to use in case several consecutive miss
     	// shaders are present in the SBT. This allows to change the behavior of
     	// the program when no geometry have been hit, for example one to return a
     	// sky color for regular rendering, and another returning a full
     	// visibility value for shadow rays. This sample has only one miss shader,
     	// hence an index 0
     	1,
     	// Ray information to trace
     	ray,
     	// Payload associated to the ray, which will be used to communicate
     	// between the hit/miss shaders and the raygen
     	shadowPayload);
		
	if(!shadowPayload.isHit)
		return false;
		
	float world_dist = length(shadowPayload.vertinfo.xyz - worldOrigin);
	return world_dist < distance - 2;
}

float3 FireSecondRay(float3 worldOrigin, float distance, float3 normal)
{	
	 // Fire a shadow ray. The direction is hard-coded here, but can be fetched
     // from a constant-buffer
     RayDesc ray;
     ray.Origin = worldOrigin;
     ray.Direction = normal;
     ray.TMin = 3.0;
     ray.TMax = distance;
     bool hit = true;
     
     // Initialize the ray payload
     SecondHitInfo payload;
     payload.payload_color = float4(0, 0, 0, 0);
     
     // Trace the ray
     TraceRay(
     	// Acceleration structure
     	SceneBVH,
     	// Flags can be used to specify the behavior upon hitting a surface
     	RAY_FLAG_NONE,
     	// Instance inclusion mask, which can be used to mask out some geometry to
     	// this ray by and-ing the mask with a geometry mask. The 0xFF flag then
     	// indicates no geometry will be masked
     	0x80,
     	// Depending on the type of ray, a given object can have several hit
     	// groups attached (ie. what to do when hitting to compute regular
     	// shading, and what to do when hitting to compute shadows). Those hit
     	// groups are specified sequentially in the SBT, so the value below
     	// indicates which offset (on 4 bits) to apply to the hit groups for this
     	// ray. In this sample we only have one hit group per object, hence an
     	// offset of 0.
     	2,
     	// The offsets in the SBT can be computed from the object ID, its instance
     	// ID, but also simply by the order the objects have been pushed in the
     	// acceleration structure. This allows the application to group shaders in
     	// the SBT in the same order as they are added in the AS, in which case
     	// the value below represents the stride (4 bits representing the number
     	// of hit groups) between two consecutive objects.
     	0,
     	// Index of the miss shader to use in case several consecutive miss
     	// shaders are present in the SBT. This allows to change the behavior of
     	// the program when no geometry have been hit, for example one to return a
     	// sky color for regular rendering, and another returning a full
     	// visibility value for shadow rays. This sample has only one miss shader,
     	// hence an index 0
     	2,
     	// Ray information to trace
     	ray,
     	// Payload associated to the ray, which will be used to communicate
     	// between the hit/miss shaders and the raygen
     	payload);
		
	if(payload.payload_color.w == 0) // Missed.
		return float3(0, 0, 0);
		
	uint bounceVertId = BInstanceProperties[int(payload.payload_vert_info.y)].startVertex + (payload.payload_vert_info.x);
	float3 bounceNormal = BTriVertex[bounceVertId].normal;
    float3 bounceWorldOrigin = payload.payload_color.xyz;	
	float3 result = float3(0, 0, 0);
	int numLights = 0;
	for(int i = 0; i < 80; i++)
	{	 		
		if(lightInfo[i].origin_radius.w == 0)
			continue;
			
		if(abs(lightInfo[i].origin_radius.w) > 400)
			continue;
		
		float r = 0; 
		if(lightInfo[i].origin_radius.w > 0) // point lights
		{
			float3 lightPos = (lightInfo[i].origin_radius.xyz);
			float3 centerLightDir = lightPos - bounceWorldOrigin;
			float lightDistance = length(centerLightDir);
			
			float angle = dot (normalize(centerLightDir), bounceNormal);
			
			r = (lightInfo[i].origin_radius.w / pow(lightDistance, 1.3)) - 1.0;
			//r = r * angle;
		}
		else // area lights
		{
			float3 lightPos = (lightInfo[i].origin_radius.xyz);
			float3 centerLightDir = lightPos - bounceWorldOrigin;
			float lightDistance = length(centerLightDir);
			
			float angle = dot (normalize(centerLightDir), bounceNormal);
			
			r = (-lightInfo[i].origin_radius.w / pow(lightDistance, 1.7)) * angle;
			//r = r * angle;
		}
		
		r = clamp(r, 0.0, 1.0);
		
		result += float3(r, r, r) * lightInfo[i].light_color2.xyz;
		numLights++;
	}	
	
	return result;
}

// better noise function available at https://github.com/ashima/webgl-noise
float rand( float2 co ) {
    return frac( sin( dot( co.xy, float2( 12.9898, 78.233 ) ) ) * 43758.5453 );
}

float DistributionGGX(float3 N, float3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	float PI = 3.14159265359;

	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(float3 N, float3 V, float3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

float3 fresnelSchlick(float cosTheta, float3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
} 

float3 CalcPBR(float3 cameraVector, float3 N, float3 L, float roughness, float3 Cd, float3 metallic)
{
	float3 V = normalize(cameraVector);
	float3 H = normalize(V + L);

	float3 F0 = float3(0.04, 0.04, 0.04); 
	F0 = lerp(F0, Cd.xyz, metallic.xyz);
			
	// cook-torrance brdf
	float NDF = DistributionGGX(N, H, roughness);        
	float G   = GeometrySmith(N, V, L, roughness);      
	float3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
			
	float3 kS = F;
	float3 kD = float3(1.0, 1.0, 1.0) - kS;
	kD *= 1.0 - metallic;	  
			
	float3 numerator    = NDF * G * F;
	float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
	return numerator / max(denominator, 0.001);  
}

int sideOfPlane(float3 p, float3 pc, float3 pn){
   if (dot(p-pc,pn)>=0.0) return 1; else return 0;
}

float packNormal(float3 color) {
    return color.r + color.g * 256.0 + color.b * 256.0 * 256.0;
}

[shader("closesthit")] void ClosestHit(inout HitInfo payload,
                                       Attributes attrib) {
  float3 barycentrics =
      float3(1.f - attrib.bary.x - attrib.bary.y, attrib.bary.x, attrib.bary.y);
	  
	  
  float3 viewPos = float3(timeViewOrg.y, timeViewOrg.z, timeViewOrg.w);	

  uint vertId = BInstanceProperties[InstanceID()].startVertex + (3 * PrimitiveIndex());
  float3 hitColor = float3(1, 0, 0);
  
  // Find the world - space hit position
  float3 worldOrigin = WorldRayOrigin() + RayTCurrent() * WorldRayDirection();
  
  float3 ndotl = float3(0.0, 0.0, 0.0);
  float3 debug = float3(1, 1, 1);
  float3 hitNormalMap = float3(1, 1, 1);
  
  if(BTriVertex[vertId + 0].vtinfo.x != -1)
  {
	  float u = 0, v = 0;
	  for(int i = 0; i < 3; i++)
	  {
			u += BTriVertex[vertId + i].st.x * barycentrics[i];
			v += BTriVertex[vertId + i].st.y * barycentrics[i];
	  }
	  
	  u = frac(u) / 16384;
	  v = frac(v) / 16384;
	  
	  u = u * BTriVertex[vertId + 0].vtinfo.z;
	  v = v * BTriVertex[vertId + 0].vtinfo.w;
	  
	  u = u + (BTriVertex[vertId + 0].vtinfo.x / 16384);
	  v = v + (BTriVertex[vertId + 0].vtinfo.y / 16384);
	  

	  //u *= BTriVertex[vertId + 0].vtinfo.z + (BTriVertex[vertId + 0].vtinfo.x / 16384);
	  //v *= BTriVertex[vertId + 0].vtinfo.w + (BTriVertex[vertId + 0].vtinfo.y / 16384);
	  //hitColor = float3(u, v, 0);
	  hitColor = MegaTexture.Load(int3(u * 16384, v * 16384, 0)).rgb; //normalize(BTriVertex[vertId + 0].vertex) * 4;
//	  hitNormalMap = MegaTextureNormal.Load(int3(u * 16384, v * 16384, 0)).rgb * 2.0 - 1.0;
  }
  else
  {
	float u = 0, v = 0;
	  for(int i = 0; i < 3; i++)
	  {
			u += BTriVertex[vertId + i].st.x * barycentrics[i];
			v += BTriVertex[vertId + i].st.y * barycentrics[i];
	  }
	  
	  u = frac(u);
	  v = frac(v);
	  hitColor = float3(u, v, 0);
  }
  
  float3 vnormal = float3(0, 0, 0);
  for(int i = 0; i < 3; i++)
  {
		vnormal.x += BTriVertex[vertId + i].normal.x * barycentrics[i];
		vnormal.y += BTriVertex[vertId + i].normal.y * barycentrics[i];
		vnormal.z += BTriVertex[vertId + i].normal.z * barycentrics[i];
  }

  float4 vtangent = float4(0, 0, 0, 1);
  for(int i = 0; i < 3; i++)
  {
		vtangent.x += BTriVertex[vertId + i].tangent.x * barycentrics[i];
		vtangent.y += BTriVertex[vertId + i].tangent.y * barycentrics[i];
		vtangent.z += BTriVertex[vertId + i].tangent.z * barycentrics[i];
  }
  
  float4 vbinormal = float4(0, 0, 0, 1);
  for(int i = 0; i < 3; i++)
  {
		vbinormal.x += BTriVertex[vertId + i].binormal.x * barycentrics[i];
		vbinormal.y += BTriVertex[vertId + i].binormal.y * barycentrics[i];
		vbinormal.z += BTriVertex[vertId + i].binormal.z * barycentrics[i];
  }

  float3 normal = normalize(vnormal);
  float3 orig_normal = normalize(vnormal);
  bool isBackFacing = dot(normal, WorldRayDirection()) > 0.f;
  if (isBackFacing)
	normal = -normal;
	
  float3 tangent = normalize(vtangent);
  float3 binormal = normalize(vbinormal); 
  
  // 2 is emissive
  float spec_contrib = 0.0;
  float emissive = 1;
  float3 spec_lit = 0;
  if(BTriVertex[vertId + 0].st.z != 2 && BTriVertex[vertId + 0].st.z != 3)
  {
	for(int i = 0; i < 120; i++)
	{	 		
		if(lightInfo[i].origin_radius.w == 0)
			continue;
		
		if(lightInfo[i].origin_radius.w > 0) // point lights
		{
			float3 lightPos = (lightInfo[i].origin_radius.xyz);
			float3 centerLightDir = lightPos - worldOrigin;
			float3 shadowLightDir = (worldOrigin + (normal * 5)) - lightPos;
			float shadowDistance = length(shadowLightDir);
			float lightDistance = length(centerLightDir);
			float falloff = attenuation(lightInfo[i].origin_radius.w, 1.0, lightDistance, normal, normalize(centerLightDir));
			float attentype = lightInfo[i].light_color.w;

			falloff = falloff - 0.1;  
			
			falloff = clamp(falloff, 0.0, 1.0);
			
			//bool isShadowed = dot(normal, centerLightDir) < 0;	  
			//if(!isShadowed)
			if(falloff > 0)
			{
					if(!IsLightShadowed(lightPos, normalize(shadowLightDir), shadowDistance, normal))
					{
						float3 V = viewPos - worldOrigin;
						float spec = CalcPBR(V, normal, normalize(centerLightDir), 0.5, float3(1, 1, 1), float3(0.5, 0.5, 0.5));
						ndotl += lightInfo[i].light_color.xyz * falloff; // normalize(centerLightDir); //max(0.f, dot(normal, normalize(centerLightDir))); 
						spec_contrib += spec * falloff * 4;
					}
			}	  			
		}
		else // area lights
		{
			// Project the point on our plane.
			float3 v = worldOrigin - lightInfo[i].origin_radius.xyz; // origin_radius is the center of our plane.
			float dist = dot(v, normal.xyz); // lightInfo[i].light_color.xyz is the normal, temp hack!
			float3 plane_point = worldOrigin - dist * normal.xyz;
			
			float3 plane_normal = lightInfo[i].light_color.xyz;
			
			float x_sign = sign(normal[0]);
			float y_sign = sign(normal[1]);
			float z_sign = sign(normal[2]);
			
			// Clamp the point within the distance of the plane.
			float3 plane_point_dist = plane_point - lightInfo[i].origin_radius.xyz;
			plane_point_dist[0] = clamp(plane_point_dist[0], -lightInfo[i].light_clamp[0] * 0.5, lightInfo[i].light_clamp[0] * 0.5) * x_sign;
			plane_point_dist[1] = clamp(plane_point_dist[1], -lightInfo[i].light_clamp[1] * 0.5, lightInfo[i].light_clamp[1] * 0.5) * y_sign;
			plane_point_dist[2] = clamp(plane_point_dist[2], -lightInfo[i].light_clamp[2] * 0.5, lightInfo[i].light_clamp[2] * 0.5) * z_sign;
			
			float3 clamped_point = lightInfo[i].origin_radius.xyz + plane_point_dist;
			
			float3 centerLightDir = clamped_point - worldOrigin;			
			float3 areaLightDir;
			areaLightDir.x = dot(tangent, centerLightDir);
			areaLightDir.y = dot(binormal, centerLightDir);
			areaLightDir.z = dot(orig_normal, centerLightDir);
			
			float lightDistance = length(centerLightDir);
			
			float falloff = 0;
			
			if(BTriVertex[vertId + 0].st.z == 0) {
				falloff = attenuation_arealight(-lightInfo[i].origin_radius.w, 1.0, lightDistance, hitNormalMap, normalize(areaLightDir)) - 0.05;  			
			}
			else {
				falloff = attenuation_arealight(-lightInfo[i].origin_radius.w, 1.0, lightDistance, normal, normalize(centerLightDir)) - 0.05;  			
			}
			falloff = clamp(falloff, 0.0, 1.0);
						
			if(falloff > 0)
			{
				if(!IsLightShadowed(worldOrigin, normalize(centerLightDir), lightDistance, normal))
				{
					float3 v_old = viewPos - worldOrigin;
					float3 V;
					V.x = dot(tangent, v_old);
					V.y = dot(binormal, v_old);
					V.z = dot(normal, v_old);
										
					ndotl += clamp(falloff, 0.0, 1.0) * lightInfo[i].light_color2.xyz;
					
					if(BTriVertex[vertId + 0].st.z == 0) {
						float spec = CalcPBR(V, hitNormalMap, normalize(areaLightDir), 0.5, float3(1, 1, 1), float3(0.5, 0.5, 0.5));
						spec_lit += spec * falloff * pow(lightInfo[i].light_color2.xyz, 2);
					}
				}
			}
		}
	}
	ndotl += 0.05;
  }
  else
  {
	ndotl = float3(1, 1, 1) * 2;
	emissive = 2;
  }  

  if(BTriVertex[vertId + 0].st.z >= 0)
  {
	for(int i = 4; i < 9; i++)
	{
		uint2 pixIdx = DispatchRaysIndex().xy;
		uint randSeed = initRand( pixIdx.x + pixIdx.y * 1920, 0 );
		int r = length(float3(worldOrigin.x + worldOrigin.y, worldOrigin.x + worldOrigin.y, worldOrigin.x + worldOrigin.y)) * i;
		float3 worldDir = getCosHemisphereSample(r, normal);
		if(IsLightShadowed(worldOrigin, worldDir, 5 * ( i * 0.1), normal)) {
			ndotl *= 0.01;
		}
	}
  }

  


	// Fire the secondary bounce
	//{
	//	int r = 1;
	//	float3 bounce = float3(0, 0, 0);
	//	for(int i = 1; i < 10; i++)
	//	{
	//		float3 worldDir = getCosHemisphereSample(r , orig_normal);
	//		bounce += FireSecondRay(worldOrigin, 250, worldDir);
	//	}
	//	if(length(bounce) > 0)
	//	{
	//		ndotl += (bounce / 10);
	//	}
	//	//ndotl += FireSecondRay(worldOrigin, 500, orig_normal);
	//}

  //hitColor = float3(InstanceID(), 0, 0);
 // float3 spec_final = pow(spec_lit, 0.5);
  //ndotl = lerp(ndotl, spec_final, length(spec_final) * 1.5);  
  //ndotl = max(ndotl, 0.1);
  //ndotl *= float3(227.0 / 255.0, 107.0 / 255.0, 0.0);  

  // Pack the normals into the alpha.
  float nrm = packNormal(BTriVertex[vertId].normal);

  payload.colorAndDistance += float4(hitColor, (nrm + 2) * (InstanceID() + 1));//float4(hitColor * ndotl * debug, RayTCurrent());
  payload.lightColor += float4(ndotl, BTriVertex[vertId + 0].st.z);
  payload.worldOrigin.xyz = worldOrigin.xyz;
  payload.worldOrigin.w = spec_contrib;

  payload.worldNormal.x = normal.x;
  payload.worldNormal.y = normal.y;
  payload.worldNormal.z = normal.z;
}
