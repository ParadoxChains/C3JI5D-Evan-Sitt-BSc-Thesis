#pragma once
#include "math.h";
#include "WaveformSynthesis.h";
#include "Filters.h";

class delay_chain {
	double frequency;
	int phase;
	double phaseStart;
	double phaseEnd;
	double output;
	double memory[88200];

public:
	delay_chain();
	double dl(double input, int size, double feedback);
	double dl(double input, int size, double feedback, int position);


};

class fractional_delay {
	static const int delaySize = 88200;
	double memory[delaySize];
	int writePointer = 0;
	int readPointer = 0;

public:
	fractional_delay(void);
	double dl(double sig, double delayTime, double feedback);
};


class flanger {
public:
    double flange(const double input, const unsigned int delay, const double feedback, const double speed, const double depth);
    delay_chain dl;
    oscillator lfo;

};

inline double flanger::flange(const double input, const unsigned int delay, const double feedback, const double speed, const double depth)
{
    double output;
    double lfoVal = lfo.triangle(speed);
    output = dl.dl(input, delay + (lfoVal * depth * delay) + 1, feedback);
    double normalise = (1 - fabs(output));
    output *= normalise;
    return (output + input) / 2.0;
}

class chorus {
public:
    double chorus(const double input, const unsigned int delay, const double feedback, const double speed, const double depth);
    delay_chain delay01, delay02;
    oscillator lfo;
    filter lowPassFilter;

};

inline double chorus::chorus(const double input, const unsigned int delay, const double feedback, const double speed, const double depth)
{
    double output1, output2;
    double lfoVal = lfo.noise();
    lfoVal = lowPassFilter.lowPassResonance(lfoVal, speed, 1.0) * 2.0;
    output1 = delay01.dl(input, delay + (lfoVal * depth * delay) + 1, feedback);
    output2 = delay02.dl(input, (delay + (lfoVal * depth * delay * 1.02) + 1) * 0.98, feedback * 0.99);
    output1 *= (1.0 - fabs(output1));
    output2 *= (1.0 - fabs(output2));
    return (output1 + output2 + input) / 3.0;
}
