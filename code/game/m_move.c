// m_move.c
//

#include "g_local.h"

#define	STEPSIZE	18

/*
=============
M_CheckBottom

Returns false if any part of the bottom of the entity is off an edge that
is not a staircase.

=============
*/
int c_yes, c_no;

qboolean M_CheckBottom(gentity_t* ent)
{
	vec3_t	mins, maxs, start, stop;
	trace_t	trace;
	int		x, y;
	float	mid, bottom;

	VectorAdd(ent->r.currentOrigin, ent->r.mins, mins);
	VectorAdd(ent->r.currentOrigin, ent->r.maxs, maxs);

	// if all of the points under the corners are solid world, don't bother
	// with the tougher checks
	// the corners must be within 16 of the midpoint
	start[2] = mins[2] - 1;
	for (x = 0; x <= 1; x++)
		for (y = 0; y <= 1; y++)
		{
			start[0] = x ? maxs[0] : mins[0];
			start[1] = y ? maxs[1] : mins[1];
			if ( trap_PointContents(start, -1) != CONTENTS_SOLID)
				goto realcheck;
		}

	c_yes++;
	return qtrue;		// we got out easy

realcheck:
	c_no++;
	//
	// check it for real...
	//
	start[2] = mins[2];

	// the midpoint must be within 16 of the bottom
	start[0] = stop[0] = (mins[0] + maxs[0]) * 0.5;
	start[1] = stop[1] = (mins[1] + maxs[1]) * 0.5;
	stop[2] = start[2] - 2 * STEPSIZE;
	trap_Trace(&trace, start, vec3_origin, vec3_origin, stop, ent - g_entities, MASK_MONSTERSOLID);

	if (trace.fraction == 1.0)
		return qfalse;
	mid = bottom = trace.endpos[2];

	// the corners must be within 16 of the midpoint	
	for (x = 0; x <= 1; x++)
		for (y = 0; y <= 1; y++)
		{
			start[0] = stop[0] = x ? maxs[0] : mins[0];
			start[1] = stop[1] = y ? maxs[1] : mins[1];

			trap_Trace(&trace, start, vec3_origin, vec3_origin, stop, ent - g_entities, MASK_MONSTERSOLID);

			if (trace.fraction != 1.0 && trace.endpos[2] > bottom)
				bottom = trace.endpos[2];
			if (trace.fraction == 1.0 || mid - trace.endpos[2] > STEPSIZE)
				return qfalse;
		}

	c_yes++;
	return qtrue;
}


/*
=============
SV_movestep

Called by monster program code.
The move will be adjusted for slopes and stairs, but if the move isn't
possible, no move is done, false is returned, and
pr_global_struct->trace_normal is set to the normal of the blocking wall
=============
*/
//FIXME since we need to test end position contents here, can we avoid doing
//it again later in catagorize position?
qboolean SV_movestep(gentity_t* ent, vec3_t move, qboolean relink)
{
	float		dz;
	vec3_t		oldorg, neworg, end;
	trace_t		trace;
	int			i;
	float		stepsize;
	vec3_t		test;
	int			contents;

	// try the move	
	VectorCopy(ent->r.currentOrigin, oldorg);
	VectorAdd(ent->r.currentOrigin, move, neworg);

	// flying monsters don't step up
	if (ent->flags & (FL_SWIM | FL_FLY))
	{
		// try one move with vertical motion, then one without
		for (i = 0; i < 2; i++)
		{
			VectorAdd(ent->r.currentOrigin, move, neworg);
			if (i == 0 && ent->enemy)
			{
				if (!ent->goalentity)
					ent->goalentity = ent->enemy;
				dz = ent->r.currentOrigin[2] - ent->goalentity->r.currentOrigin[2];
				if (ent->goalentity->client)
				{
					if (dz > 40)
						neworg[2] -= 8;
					if (!((ent->flags & FL_SWIM) && (ent->waterlevel < 2)))
						if (dz < 30)
							neworg[2] += 8;
				}
				else
				{
					if (dz > 8)
						neworg[2] -= 8;
					else if (dz > 0)
						neworg[2] -= dz;
					else if (dz < -8)
						neworg[2] += 8;
					else
						neworg[2] += dz;
				}
			}
			trap_Trace(&trace, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, neworg, ent - g_entities, MASK_MONSTERSOLID);

			// fly monsters don't enter water voluntarily
			if (ent->flags & FL_FLY)
			{
				if (!ent->waterlevel)
				{
					test[0] = trace.endpos[0];
					test[1] = trace.endpos[1];
					test[2] = trace.endpos[2] + ent->r.mins[2] + 1;
					contents = trap_PointContents(test, -1);
					if (contents & MASK_WATER)
						return qfalse;
				}
			}

			// swim monsters don't exit water voluntarily
			if (ent->flags & FL_SWIM)
			{
				if (ent->waterlevel < 2)
				{
					test[0] = trace.endpos[0];
					test[1] = trace.endpos[1];
					test[2] = trace.endpos[2] + ent->r.mins[2] + 1;
					contents = trap_PointContents(test, -1);
					if (!(contents & MASK_WATER))
						return qfalse;
				}
			}

			if (trace.fraction == 1)
			{
				VectorCopy(trace.endpos, ent->r.currentOrigin);
				if (relink)
				{
					trap_LinkEntity(ent);
					G_TouchTriggers(ent);
				}
				return qtrue;
			}

			if (!ent->enemy)
				break;
		}

		return qfalse;
	}

	// push down from a step height above the wished position
	if (!(ent->monsterinfo.aiflags & AI_NOSTEP))
		stepsize = STEPSIZE;
	else
		stepsize = 1;

	neworg[2] += stepsize;
	VectorCopy(neworg, end);
	end[2] -= stepsize * 2;

	trap_Trace(&trace, neworg, ent->r.mins, ent->r.maxs, end, ent - g_entities, MASK_MONSTERSOLID);

	if (trace.allsolid)
		return qfalse;

	if (trace.startsolid)
	{
		neworg[2] -= stepsize;
		trap_Trace(&trace, neworg, ent->r.mins, ent->r.maxs, end, ent - g_entities, MASK_MONSTERSOLID);
		if (trace.allsolid || trace.startsolid)
			return qfalse;
	}


	// don't go in to water
	if (ent->waterlevel == 0)
	{
		test[0] = trace.endpos[0];
		test[1] = trace.endpos[1];
		test[2] = trace.endpos[2] + ent->r.mins[2] + 1;
		contents = trap_PointContents(test, -1);

		if (contents & MASK_WATER)
			return qfalse;
	}

	if (trace.fraction == 1)
	{
		// if monster had the ground pulled out, go ahead and fall
		if (ent->flags & FL_PARTIALGROUND)
		{
			VectorAdd(ent->r.currentOrigin, move, ent->r.currentOrigin);
			if (relink)
			{
				trap_LinkEntity(ent);
				G_TouchTriggers(ent);
			}
			ent->groundentity = NULL;
			return qtrue;
		}

		return qfalse;		// walked off an edge
	}

	// check point traces down for dangling corners
	VectorCopy(trace.endpos, ent->r.currentOrigin);

	if (!M_CheckBottom(ent))
	{
		if (ent->flags & FL_PARTIALGROUND)
		{	// entity had floor mostly pulled out from underneath it
			// and is trying to correct
			if (relink)
			{
				trap_LinkEntity(ent);
				G_TouchTriggers(ent);
			}
			return qtrue;
		}
		VectorCopy(oldorg, ent->r.currentOrigin);
		return qfalse;
	}

	if (ent->flags & FL_PARTIALGROUND)
	{
		ent->flags &= ~FL_PARTIALGROUND;
	}
	ent->groundentity = &g_entities[trace.entityNum];
	//ent->groundentity_linkcount = trace.ent->linkcount;

	// the move is ok
	if (relink)
	{
		trap_LinkEntity(ent);
		G_TouchTriggers(ent);
	}
	return qtrue;
}


//============================================================================

/*
===============
M_ChangeYaw

===============
*/
void M_ChangeYaw(gentity_t* ent)
{
	float	ideal;
	float	current;
	float	move;
	float	speed;

	current = anglemod(ent->s.angles[YAW]);
	ideal = ent->ideal_yaw;

	if (current == ideal)
		return;

	move = ideal - current;
	speed = ent->yaw_speed;
	if (ideal > current)
	{
		if (move >= 180)
			move = move - 360;
	}
	else
	{
		if (move <= -180)
			move = move + 360;
	}
	if (move > 0)
	{
		if (move > speed)
			move = speed;
	}
	else
	{
		if (move < -speed)
			move = -speed;
	}

	ent->s.angles[YAW] = anglemod(current + move);
}


/*
======================
SV_StepDirection

Turns to the movement direction, and walks the current distance if
facing it.

======================
*/
qboolean SV_StepDirection(gentity_t* ent, float yaw, float dist)
{
	vec3_t		move, oldorigin;
	float		delta;

	ent->ideal_yaw = yaw;
	M_ChangeYaw(ent);

	yaw = yaw * M_PI * 2 / 360;
	move[0] = cos(yaw) * dist;
	move[1] = sin(yaw) * dist;
	move[2] = 0;

	VectorCopy(ent->r.currentOrigin, oldorigin);
	if (SV_movestep(ent, move, qfalse))
	{
		delta = ent->s.angles[YAW] - ent->ideal_yaw;
		if (delta > 45 && delta < 315)
		{		// not turned far enough, so don't take the step
			VectorCopy(oldorigin, ent->r.currentOrigin);
		}
		trap_LinkEntity(ent);
		G_TouchTriggers(ent);
		return qtrue;
	}
	//gi.linkentity(ent);
	trap_LinkEntity(ent);
	G_TouchTriggers(ent);
	return qfalse;
}

/*
======================
SV_FixCheckBottom

======================
*/
void SV_FixCheckBottom(gentity_t* ent)
{
	ent->flags |= FL_PARTIALGROUND;
}



/*
================
SV_NewChaseDir

================
*/
#define	DI_NODIR	-1
void SV_NewChaseDir(gentity_t* actor, gentity_t* enemy, float dist)
{
	float	deltax, deltay;
	float	d[3];
	float	tdir, olddir, turnaround;

	//FIXME: how did we get here with no enemy
	if (!enemy)
		return;

	olddir = anglemod((int)(actor->ideal_yaw / 45) * 45);
	turnaround = anglemod(olddir - 180);

	deltax = enemy->r.currentOrigin[0] - actor->r.currentOrigin[0];
	deltay = enemy->r.currentOrigin[1] - actor->r.currentOrigin[1];
	if (deltax > 10)
		d[1] = 0;
	else if (deltax < -10)
		d[1] = 180;
	else
		d[1] = DI_NODIR;
	if (deltay < -10)
		d[2] = 270;
	else if (deltay > 10)
		d[2] = 90;
	else
		d[2] = DI_NODIR;

	// try direct route
	if (d[1] != DI_NODIR && d[2] != DI_NODIR)
	{
		if (d[1] == 0)
			tdir = d[2] == 90 ? 45 : 315;
		else
			tdir = d[2] == 90 ? 135 : 215;

		if (tdir != turnaround && SV_StepDirection(actor, tdir, dist))
			return;
	}

	// try other directions
	if (((rand() & 3) & 1) || abs(deltay) > abs(deltax))
	{
		tdir = d[1];
		d[1] = d[2];
		d[2] = tdir;
	}

	if (d[1] != DI_NODIR && d[1] != turnaround
		&& SV_StepDirection(actor, d[1], dist))
		return;

	if (d[2] != DI_NODIR && d[2] != turnaround
		&& SV_StepDirection(actor, d[2], dist))
		return;

	/* there is no direct path to the player, so pick another direction */

	if (olddir != DI_NODIR && SV_StepDirection(actor, olddir, dist))
		return;

	if (rand() & 1) 	/*randomly determine direction of search*/
	{
		for (tdir = 0; tdir <= 315; tdir += 45)
			if (tdir != turnaround && SV_StepDirection(actor, tdir, dist))
				return;
	}
	else
	{
		for (tdir = 315; tdir >= 0; tdir -= 45)
			if (tdir != turnaround && SV_StepDirection(actor, tdir, dist))
				return;
	}

	if (turnaround != DI_NODIR && SV_StepDirection(actor, turnaround, dist))
		return;

	actor->ideal_yaw = olddir;		// can't move

// if a bridge was pulled out from underneath a monster, it may not have
// a valid standing position at all

	if (!M_CheckBottom(actor))
		SV_FixCheckBottom(actor);
}

/*
======================
SV_CloseEnough

======================
*/
qboolean SV_CloseEnough(gentity_t* ent, gentity_t* goal, float dist)
{
	int		i;

	for (i = 0; i < 3; i++)
	{
		if (abs(goal->r.mins[i]) > abs(goal->r.maxs[i]) + dist)
			return qfalse;
		if (abs(goal->r.maxs[i]) < abs(goal->r.mins[i]) - dist)
			return qfalse;
	}
	return qtrue;
}


/*
======================
M_MoveToGoal
======================
*/
void M_MoveToGoal(gentity_t* ent, float dist)
{
	gentity_t* goal;

	goal = ent->goalentity;
/*
	if (!ent->groundentity && !(ent->flags & (FL_FLY | FL_SWIM)))
		return;

	// if the next step hits the enemy, return immediately
	if (ent->enemy && SV_CloseEnough(ent, ent->enemy, dist))
		return;
		*/
	// bump around...
	if ((rand() & 3) == 1 || !SV_StepDirection(ent, ent->ideal_yaw, dist))
	{
		if (ent->inuse)
			SV_NewChaseDir(ent, goal, dist);
	}
}


/*
===============
M_walkmove
===============
*/
qboolean M_walkmove(gentity_t* ent, float yaw, float dist)
{
	vec3_t	move;

	if (!ent->groundentity && !(ent->flags & (FL_FLY | FL_SWIM)))
		return qfalse;

	yaw = yaw * M_PI * 2 / 360;

	move[0] = cos(yaw) * dist;
	move[1] = sin(yaw) * dist;
	move[2] = 0;

	return SV_movestep(ent, move, qtrue);
}
