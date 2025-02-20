// This file has been auto generated by the QuakeToC conversion tool
// 

#include "../../game/g_local.h "
#include "../superscript.h"
extern "C" {
	#include "generated_ogre.h"

};

void ogre_stand1(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand1, stand1, &frame, ogre_stand2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_stand,stand1,stand9);
}
void ogre_stand2(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand2, stand2, &frame, ogre_stand3};
	self->monsterinfo.currentmove = &move;
}
void ogre_stand3(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand3, stand3, &frame, ogre_stand4};
	self->monsterinfo.currentmove = &move;
}
void ogre_stand4(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand4, stand4, &frame, ogre_stand5};
	self->monsterinfo.currentmove = &move;
}
void ogre_stand5(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand5, stand5, &frame, ogre_stand6};
	self->monsterinfo.currentmove = &move;

if (random() < 0.2)
	sound (self, CHAN_VOICE, "ogre/ogidle.wav", 1, ATTN_IDLE);

}
void ogre_stand6(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand6, stand6, &frame, ogre_stand7};
	self->monsterinfo.currentmove = &move;
}
void ogre_stand7(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand7, stand7, &frame, ogre_stand8};
	self->monsterinfo.currentmove = &move;
}
void ogre_stand8(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand8, stand8, &frame, ogre_stand9};
	self->monsterinfo.currentmove = &move;
}
void ogre_stand9(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { stand9, stand9, &frame, ogre_stand1};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk1(gentity_t *self) {
	static mframe_t frame = { ai_walk,3, NULL };
	static mmove_t move = { walk1, walk1, &frame, ogre_walk2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_walk,walk1,walk16);
}
void ogre_walk2(gentity_t *self) {
	static mframe_t frame = { ai_walk,2, NULL };
	static mmove_t move = { walk2, walk2, &frame, ogre_walk3};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk3(gentity_t *self) {
	static mframe_t frame = { ai_walk,2, NULL };
	static mmove_t move = { walk3, walk3, &frame, ogre_walk4};
	self->monsterinfo.currentmove = &move;


if (random() < 0.2)
	sound (self, CHAN_VOICE, "ogre/ogidle.wav", 1, ATTN_IDLE);
}
void ogre_walk4(gentity_t *self) {
	static mframe_t frame = { ai_walk,2, NULL };
	static mmove_t move = { walk4, walk4, &frame, ogre_walk5};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk5(gentity_t *self) {
	static mframe_t frame = { ai_walk,2, NULL };
	static mmove_t move = { walk5, walk5, &frame, ogre_walk6};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk6(gentity_t *self) {
	static mframe_t frame = { ai_walk,5, NULL };
	static mmove_t move = { walk6, walk6, &frame, ogre_walk7};
	self->monsterinfo.currentmove = &move;


if (random() < 0.1)
	sound (self, CHAN_VOICE, "ogre/ogdrag.wav", 1, ATTN_IDLE);
}
void ogre_walk7(gentity_t *self) {
	static mframe_t frame = { ai_walk,3, NULL };
	static mmove_t move = { walk7, walk7, &frame, ogre_walk8};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk8(gentity_t *self) {
	static mframe_t frame = { ai_walk,2, NULL };
	static mmove_t move = { walk8, walk8, &frame, ogre_walk9};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk9(gentity_t *self) {
	static mframe_t frame = { ai_walk,3, NULL };
	static mmove_t move = { walk9, walk9, &frame, ogre_walk10};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk10(gentity_t *self) {
	static mframe_t frame = { ai_walk,1, NULL };
	static mmove_t move = { walk10, walk10, &frame, ogre_walk11};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk11(gentity_t *self) {
	static mframe_t frame = { ai_walk,2, NULL };
	static mmove_t move = { walk11, walk11, &frame, ogre_walk12};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk12(gentity_t *self) {
	static mframe_t frame = { ai_walk,3, NULL };
	static mmove_t move = { walk12, walk12, &frame, ogre_walk13};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk13(gentity_t *self) {
	static mframe_t frame = { ai_walk,3, NULL };
	static mmove_t move = { walk13, walk13, &frame, ogre_walk14};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk14(gentity_t *self) {
	static mframe_t frame = { ai_walk,3, NULL };
	static mmove_t move = { walk14, walk14, &frame, ogre_walk15};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk15(gentity_t *self) {
	static mframe_t frame = { ai_walk,3, NULL };
	static mmove_t move = { walk15, walk15, &frame, ogre_walk16};
	self->monsterinfo.currentmove = &move;
}
void ogre_walk16(gentity_t *self) {
	static mframe_t frame = { ai_walk,4, NULL };
	static mmove_t move = { walk16, walk16, &frame, ogre_walk1};
	self->monsterinfo.currentmove = &move;
}
void ogre_run1(gentity_t *self) {
	static mframe_t frame = { ai_run,9, NULL };
	static mmove_t move = { run1, run1, &frame, ogre_run2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_run,run1,run8);

if (random() < 0.2)
	sound (self, CHAN_VOICE, "ogre/ogidle2.wav", 1, ATTN_IDLE);
}
void ogre_run2(gentity_t *self) {
	static mframe_t frame = { ai_run,12, NULL };
	static mmove_t move = { run2, run2, &frame, ogre_run3};
	self->monsterinfo.currentmove = &move;
}
void ogre_run3(gentity_t *self) {
	static mframe_t frame = { ai_run,8, NULL };
	static mmove_t move = { run3, run3, &frame, ogre_run4};
	self->monsterinfo.currentmove = &move;
}
void ogre_run4(gentity_t *self) {
	static mframe_t frame = { ai_run,22, NULL };
	static mmove_t move = { run4, run4, &frame, ogre_run5};
	self->monsterinfo.currentmove = &move;
}
void ogre_run5(gentity_t *self) {
	static mframe_t frame = { ai_run,16, NULL };
	static mmove_t move = { run5, run5, &frame, ogre_run6};
	self->monsterinfo.currentmove = &move;
}
void ogre_run6(gentity_t *self) {
	static mframe_t frame = { ai_run,4, NULL };
	static mmove_t move = { run6, run6, &frame, ogre_run7};
	self->monsterinfo.currentmove = &move;
}
void ogre_run7(gentity_t *self) {
	static mframe_t frame = { ai_run,13, NULL };
	static mmove_t move = { run7, run7, &frame, ogre_run8};
	self->monsterinfo.currentmove = &move;
}
void ogre_run8(gentity_t *self) {
	static mframe_t frame = { ai_run,24, NULL };
	static mmove_t move = { run8, run8, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
void ogre_swing1(gentity_t *self) {
	static mframe_t frame = { ai_charge,11, NULL };
	static mmove_t move = { swing1, swing1, &frame, ogre_swing2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_swing,swing1,swing14);

sound (self, CHAN_WEAPON, "ogre/ogsawatk.wav", 1, ATTN_NORM);
}
void ogre_swing2(gentity_t *self) {
	static mframe_t frame = { ai_charge,1, NULL };
	static mmove_t move = { swing2, swing2, &frame, ogre_swing3};
	self->monsterinfo.currentmove = &move;
}
void ogre_swing3(gentity_t *self) {
	static mframe_t frame = { ai_charge,4, NULL };
	static mmove_t move = { swing3, swing3, &frame, ogre_swing4};
	self->monsterinfo.currentmove = &move;
}
void ogre_swing4(gentity_t *self) {
	static mframe_t frame = { ai_charge,13, NULL };
	static mmove_t move = { swing4, swing4, &frame, ogre_swing5};
	self->monsterinfo.currentmove = &move;
}
void ogre_swing5(gentity_t *self) {
	static mframe_t frame = { ai_charge,9, NULL };
	static mmove_t move = { swing5, swing5, &frame, ogre_swing6};
	self->monsterinfo.currentmove = &move;
 OrgeChainsaw(self, 0);self->r.currentAngles[1] = self->r.currentAngles[1] + random()*25;}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_swing6(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { swing6, swing6, &frame, ogre_swing7};
	self->monsterinfo.currentmove = &move;
OrgeChainsaw(self, 200);self->r.currentAngles[1] = self->r.currentAngles[1] + random()* 25;}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_swing7(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { swing7, swing7, &frame, ogre_swing8};
	self->monsterinfo.currentmove = &move;
OrgeChainsaw(self, 0);self->r.currentAngles[1] = self->r.currentAngles[1] + random()* 25;}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_swing8(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { swing8, swing8, &frame, ogre_swing9};
	self->monsterinfo.currentmove = &move;
OrgeChainsaw(self, 0);self->r.currentAngles[1] = self->r.currentAngles[1] + random()* 25;}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_swing9(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { swing9, swing9, &frame, ogre_swing10};
	self->monsterinfo.currentmove = &move;
OrgeChainsaw(self, 0);self->r.currentAngles[1] = self->r.currentAngles[1] + random()* 25;}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_swing10(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { swing10, swing10, &frame, ogre_swing11};
	self->monsterinfo.currentmove = &move;
OrgeChainsaw(self, -200);self->r.currentAngles[1] = self->r.currentAngles[1] + random()* 25;}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_swing11(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { swing11, swing11, &frame, ogre_swing12};
	self->monsterinfo.currentmove = &move;
OrgeChainsaw(self, 0);self->r.currentAngles[1] = self->r.currentAngles[1] + random()* 25;}
void ogre_swing12(gentity_t *self) {
	static mframe_t frame = { ai_charge,3, NULL };
	static mmove_t move = { swing12, swing12, &frame, ogre_swing13};
	self->monsterinfo.currentmove = &move;
}
void ogre_swing13(gentity_t *self) {
	static mframe_t frame = { ai_charge,8, NULL };
	static mmove_t move = { swing13, swing13, &frame, ogre_swing14};
	self->monsterinfo.currentmove = &move;
}
void ogre_swing14(gentity_t *self) {
	static mframe_t frame = { ai_charge,9, NULL };
	static mmove_t move = { swing14, swing14, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
void ogre_smash1(gentity_t *self) {
	static mframe_t frame = { ai_charge,6, NULL };
	static mmove_t move = { smash1, smash1, &frame, ogre_smash2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_smash,smash1,smash14);

sound (self, CHAN_WEAPON, "ogre/ogsawatk.wav", 1, ATTN_NORM);
}
void ogre_smash2(gentity_t *self) {
	static mframe_t frame = { ai_charge,0, NULL };
	static mmove_t move = { smash2, smash2, &frame, ogre_smash3};
	self->monsterinfo.currentmove = &move;
}
void ogre_smash3(gentity_t *self) {
	static mframe_t frame = { ai_charge,0, NULL };
	static mmove_t move = { smash3, smash3, &frame, ogre_smash4};
	self->monsterinfo.currentmove = &move;
}
void ogre_smash4(gentity_t *self) {
	static mframe_t frame = { ai_charge,1, NULL };
	static mmove_t move = { smash4, smash4, &frame, ogre_smash5};
	self->monsterinfo.currentmove = &move;
}
void ogre_smash5(gentity_t *self) {
	static mframe_t frame = { ai_charge,4, NULL };
	static mmove_t move = { smash5, smash5, &frame, ogre_smash6};
	self->monsterinfo.currentmove = &move;
}
void ogre_smash6(gentity_t *self) {
	static mframe_t frame = { ai_charge,4, NULL };
	static mmove_t move = { smash6, smash6, &frame, ogre_smash7};
	self->monsterinfo.currentmove = &move;
 OrgeChainsaw(self, 0);}
void ogre_smash7(gentity_t *self) {
	static mframe_t frame = { ai_charge,4, NULL };
	static mmove_t move = { smash7, smash7, &frame, ogre_smash8};
	self->monsterinfo.currentmove = &move;
 OrgeChainsaw(self, 0);}
void ogre_smash8(gentity_t *self) {
	static mframe_t frame = { ai_charge,10, NULL };
	static mmove_t move = { smash8, smash8, &frame, ogre_smash9};
	self->monsterinfo.currentmove = &move;
 OrgeChainsaw(self, 0);}
void ogre_smash9(gentity_t *self) {
	static mframe_t frame = { ai_charge,13, NULL };
	static mmove_t move = { smash9, smash9, &frame, ogre_smash10};
	self->monsterinfo.currentmove = &move;
 OrgeChainsaw(self, 0);}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_smash10(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { smash10, smash10, &frame, ogre_smash11};
	self->monsterinfo.currentmove = &move;
OrgeChainsaw(self, 1);}
void ogre_smash11(gentity_t *self) {
	static mframe_t frame = { ai_charge,2, NULL };
	static mmove_t move = { smash11, smash11, &frame, ogre_smash12};
	self->monsterinfo.currentmove = &move;
 OrgeChainsaw(self, 0);
self->nextthink = self->nextthink + random()*0.2;}
void ogre_smash12(gentity_t *self) {
	static mframe_t frame = { ai_charge,0, NULL };
	static mmove_t move = { smash12, smash12, &frame, ogre_smash13};
	self->monsterinfo.currentmove = &move;
}
void ogre_smash13(gentity_t *self) {
	static mframe_t frame = { ai_charge,4, NULL };
	static mmove_t move = { smash13, smash13, &frame, ogre_smash14};
	self->monsterinfo.currentmove = &move;
}
void ogre_smash14(gentity_t *self) {
	static mframe_t frame = { ai_charge,12, NULL };
	static mmove_t move = { smash14, smash14, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
void ogre_nail1(gentity_t *self) {
	static mframe_t frame = { ai_face,0, NULL };
	static mmove_t move = { shoot1, shoot1, &frame, ogre_nail2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_shoot,shoot1,shoot6);
}
void ogre_nail2(gentity_t *self) {
	static mframe_t frame = { ai_face,0, NULL };
	static mmove_t move = { shoot2, shoot2, &frame, ogre_nail3};
	self->monsterinfo.currentmove = &move;
}
void ogre_nail3(gentity_t *self) {
	static mframe_t frame = { ai_face,0, NULL };
	static mmove_t move = { shoot2, shoot2, &frame, ogre_nail4};
	self->monsterinfo.currentmove = &move;
}
void ogre_nail4(gentity_t *self) {
	static mframe_t frame = { ai_face,0, NULL };
	static mmove_t move = { shoot3, shoot3, &frame, ogre_nail5};
	self->monsterinfo.currentmove = &move;
OgreFireGrenade(self);}
void ogre_nail5(gentity_t *self) {
	static mframe_t frame = { ai_face,0, NULL };
	static mmove_t move = { shoot4, shoot4, &frame, ogre_nail6};
	self->monsterinfo.currentmove = &move;
}
void ogre_nail6(gentity_t *self) {
	static mframe_t frame = { ai_face,0, NULL };
	static mmove_t move = { shoot5, shoot5, &frame, ogre_nail7};
	self->monsterinfo.currentmove = &move;
}
void ogre_nail7(gentity_t *self) {
	static mframe_t frame = { ai_face,0, NULL };
	static mmove_t move = { shoot6, shoot6, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_pain1(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { pain1, pain1, &frame, ogre_pain2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_pain,pain1,pain5);
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_pain2(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { pain2, pain2, &frame, ogre_pain3};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_pain3(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { pain3, pain3, &frame, ogre_pain4};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_pain4(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { pain4, pain4, &frame, ogre_pain5};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_pain5(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { pain5, pain5, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painb1(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painb1, painb1, &frame, ogre_painb2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_painb,painb1,painb3);
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painb2(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painb2, painb2, &frame, ogre_painb3};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painb3(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painb3, painb3, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painc1(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painc1, painc1, &frame, ogre_painc2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_painc,painc1,painc6);
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painc2(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painc2, painc2, &frame, ogre_painc3};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painc3(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painc3, painc3, &frame, ogre_painc4};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painc4(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painc4, painc4, &frame, ogre_painc5};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painc5(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painc5, painc5, &frame, ogre_painc6};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_painc6(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { painc6, painc6, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind1(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind1, paind1, &frame, ogre_paind2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_paind,paind1,paind16);
}
void ogre_paind2(gentity_t *self) {
	static mframe_t frame = { ai_pain,10, NULL };
	static mmove_t move = { paind2, paind2, &frame, ogre_paind3};
	self->monsterinfo.currentmove = &move;
}
void ogre_paind3(gentity_t *self) {
	static mframe_t frame = { ai_pain,9, NULL };
	static mmove_t move = { paind3, paind3, &frame, ogre_paind4};
	self->monsterinfo.currentmove = &move;
}
void ogre_paind4(gentity_t *self) {
	static mframe_t frame = { ai_pain,4, NULL };
	static mmove_t move = { paind4, paind4, &frame, ogre_paind5};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind5(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind5, paind5, &frame, ogre_paind6};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind6(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind6, paind6, &frame, ogre_paind7};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind7(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind7, paind7, &frame, ogre_paind8};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind8(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind8, paind8, &frame, ogre_paind9};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind9(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind9, paind9, &frame, ogre_paind10};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind10(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind10, paind10, &frame, ogre_paind11};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind11(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind11, paind11, &frame, ogre_paind12};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind12(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind12, paind12, &frame, ogre_paind13};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind13(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind13, paind13, &frame, ogre_paind14};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind14(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind14, paind14, &frame, ogre_paind15};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind15(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind15, paind15, &frame, ogre_paind16};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paind16(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paind16, paind16, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine1(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine1, paine1, &frame, ogre_paine2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_paine,paine1,paine15);
}
void ogre_paine2(gentity_t *self) {
	static mframe_t frame = { ai_pain,10, NULL };
	static mmove_t move = { paine2, paine2, &frame, ogre_paine3};
	self->monsterinfo.currentmove = &move;
}
void ogre_paine3(gentity_t *self) {
	static mframe_t frame = { ai_pain,9, NULL };
	static mmove_t move = { paine3, paine3, &frame, ogre_paine4};
	self->monsterinfo.currentmove = &move;
}
void ogre_paine4(gentity_t *self) {
	static mframe_t frame = { ai_pain,4, NULL };
	static mmove_t move = { paine4, paine4, &frame, ogre_paine5};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine5(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine5, paine5, &frame, ogre_paine6};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine6(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine6, paine6, &frame, ogre_paine7};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine7(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine7, paine7, &frame, ogre_paine8};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine8(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine8, paine8, &frame, ogre_paine9};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine9(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine9, paine9, &frame, ogre_paine10};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine10(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine10, paine10, &frame, ogre_paine11};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine11(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine11, paine11, &frame, ogre_paine12};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine12(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine12, paine12, &frame, ogre_paine13};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine13(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine13, paine13, &frame, ogre_paine14};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine14(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine14, paine14, &frame, ogre_paine15};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_paine15(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { paine15, paine15, &frame, ogre_run1};
	self->monsterinfo.currentmove = &move;
}
void ogre_pain(gentity_t *self) {

	 float	r;


	if (self->pain_finished > level.time)
		return;

	sound (self, CHAN_VOICE, "ogre/ogpain1.wav", 1, ATTN_NORM);		

	r = random();
	
	if (r < 0.25)
	{
		ogre_pain1(self);
		self->pain_finished = level.time + 1;
	}
	else if (r < 0.5)
	{
		ogre_painb1(self);
		self->pain_finished = level.time + 1;
	}
	else if (r < 0.75)
	{
		ogre_painc1(self);
		self->pain_finished = level.time + 1;
	}
	else if (r < 0.88)
	{
		ogre_paind1(self);
		self->pain_finished = level.time + 2;
	}
	else
	{
		ogre_paine1(self);
		self->pain_finished = level.time + 2;
	}
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die1(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death1, death1, &frame, ogre_die2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_death,death1,death14);
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die2(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death2, death2, &frame, ogre_die3};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die3(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death3, death3, &frame, ogre_die4};
	self->monsterinfo.currentmove = &move;
	self->r.contents = 0;
	trap_LinkEntity(self);


}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die4(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death4, death4, &frame, ogre_die5};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die5(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death5, death5, &frame, ogre_die6};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die6(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death6, death6, &frame, ogre_die7};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die7(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death7, death7, &frame, ogre_die8};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die8(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death8, death8, &frame, ogre_die9};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die9(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death9, death9, &frame, ogre_die10};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die10(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death10, death10, &frame, ogre_die11};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die11(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death11, death11, &frame, ogre_die12};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die12(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death12, death12, &frame, ogre_die13};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die13(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death13, death13, &frame, ogre_die14};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_die14(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { death14, death14, &frame, ogre_die14};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_bdie1(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { bdeath1, bdeath1, &frame, ogre_bdie2};
	self->monsterinfo.currentmove = &move;
// Anim Start function
G_SendAnimUpdate(self, anim_event_bdeath,bdeath1,bdeath10);
}
void ogre_bdie2(gentity_t *self) {
	static mframe_t frame = { ai_move,5, NULL };
	static mmove_t move = { bdeath2, bdeath2, &frame, ogre_bdie3};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_bdie3(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { bdeath3, bdeath3, &frame, ogre_bdie4};
	self->monsterinfo.currentmove = &move;
	self->r.contents = 0;
	trap_LinkEntity(self);


}
void ogre_bdie4(gentity_t *self) {
	static mframe_t frame = { ai_move,1, NULL };
	static mmove_t move = { bdeath4, bdeath4, &frame, ogre_bdie5};
	self->monsterinfo.currentmove = &move;
}
void ogre_bdie5(gentity_t *self) {
	static mframe_t frame = { ai_move,3, NULL };
	static mmove_t move = { bdeath5, bdeath5, &frame, ogre_bdie6};
	self->monsterinfo.currentmove = &move;
}
void ogre_bdie6(gentity_t *self) {
	static mframe_t frame = { ai_move,7, NULL };
	static mmove_t move = { bdeath6, bdeath6, &frame, ogre_bdie7};
	self->monsterinfo.currentmove = &move;
}
void ogre_bdie7(gentity_t *self) {
	static mframe_t frame = { ai_move,25, NULL };
	static mmove_t move = { bdeath7, bdeath7, &frame, ogre_bdie8};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_bdie8(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { bdeath8, bdeath8, &frame, ogre_bdie9};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_bdie9(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { bdeath9, bdeath9, &frame, ogre_bdie10};
	self->monsterinfo.currentmove = &move;
}
// WARNING: No AI state change specified, defaulting to ai_stand
void ogre_bdie10(gentity_t *self) {
	static mframe_t frame = { ai_stand,0, NULL };
	static mmove_t move = { bdeath10, bdeath10, &frame, ogre_bdie10};
	self->monsterinfo.currentmove = &move;
}
void ogre_die(gentity_t *self) {


	if (self->health < -80)
	{
		sound (self, CHAN_VOICE, "player/udeath.wav", 1, ATTN_NORM);
		SpawnGib(self);
		self->isGibbed = qtrue;
		return;
	}

	sound (self, CHAN_VOICE, "ogre/ogdth.wav", 1, ATTN_NORM);
	
	if (random() < 0.5)
		ogre_die1(self);
	else
		ogre_bdie1(self);
}
void ogre_melee(gentity_t *self) {

	if (random() > 0.5)
		ogre_smash1(self);
	else
		ogre_swing1(self);
}
void monster_ogre(gentity_t *self) {

	precache_model ("models/monsters/ogre.md3");
	precache_model ("progs/h_ogre.mdl");
	precache_model ("progs/grenade.mdl");

	precache_sound ("ogre/ogdrag.wav");
	precache_sound ("ogre/ogdth.wav");
	precache_sound ("ogre/ogidle.wav");
	precache_sound ("ogre/ogidle2.wav");
	precache_sound ("ogre/ogpain1.wav");
	precache_sound ("ogre/ogsawatk.wav");
	precache_sound ("ogre/ogwake.wav");

		self->r.contents = CONTENTS_SOLID;
	trap_LinkEntity(self);

	self->movetype = MOVETYPE_STEP;

	setmodel (self, "models/monsters/ogre.md3");

	setsize (self, VEC_HULL2_MIN, VEC_HULL2_MAX);
	self->health = 200;

	self->monsterinfo.stand = ogre_stand1;
	self->monsterinfo.walk = ogre_walk1;
	self->monsterinfo.run = ogre_run1;
	self->monsterinfo.die = ogre_die;
	self->monsterinfo.melee = ogre_melee;
	self->monsterinfo.attack = ogre_nail1;
	self->monsterinfo.pain = ogre_pain;
	
	walkmonster_start(self);
}
void monster_ogre_marksman(gentity_t *self) {

	monster_ogre(self);
}
