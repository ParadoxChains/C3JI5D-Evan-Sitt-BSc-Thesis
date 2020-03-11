#pragma once
#include "math.h";
#include <cstdlib>;
#include <stdint.h>;
#include <string.h>;
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

