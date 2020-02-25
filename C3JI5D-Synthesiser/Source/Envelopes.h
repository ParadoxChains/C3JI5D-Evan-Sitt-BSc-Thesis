#pragma once
#include "math.h"
class envelope {


public:
	envelope();
	double ar(double input, double attack = 1, double release = 0.9, long holdtime = 1, int trigger = 0);
	double adsr(double input, double attack = 1, double decay = 0.99, double sustain = 0.125, double release = 0.9, long holdtime = 1, int trigger = 0);
	double adsr(double input, int trigger);
	double input;
	double output;
	double attack;
	double decay;
	double sustain;
	double release;
	double amplitude;
	void setAttack(double attackMS);
	void setRelease(double releaseMS);
	void setDecay(double decayMS);
	void setSustain(double sustainL);
	int trigger;
	long holdtime = 1;
	long holdcount;
	int attackphase, decayphase, sustainphase, holdphase, releasephase;
	double sampleRate;
};