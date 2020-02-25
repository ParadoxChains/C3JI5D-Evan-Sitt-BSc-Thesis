#pragma once
#include "math.h"
/*
The oscillator class will provide values for writing out to the audio buffer.
*/
class oscillator
{
public:
	oscillator();
	void resetPhase(double newPhase);
	void resetPhase();
	double sine(double frequency);
	double square(double frequency);
	double saw(double frequency);
	double triangle(double frequency);

protected:

private:
	double frequency;
	double phase;
	double outputValue;
	double sampleRate;
	int waveTableSize;
};