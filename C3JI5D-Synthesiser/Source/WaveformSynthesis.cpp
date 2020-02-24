#include "WaveformSynthesis.h"

oscillator::oscillator()
{
	phase = 0.0;
}

void oscillator::resetPhase(double newPhase)
{
	phase = newPhase;
}

void oscillator::resetPhase()
{
	phase = 0.0;
}

double oscillator::sine(double frequency)
{
	double remainder;
	double a, b, c, d, a1, a2, a3;
	phase += 512. / (maxiSettings::sampleRate / (frequency));
	if (phase >= 511) phase -= 512;
	remainder = phase - floor(phase);

	if (phase == 0) {
		a = sineBuffer[(long)512];
		b = sineBuffer[(long)phase];
		c = sineBuffer[(long)phase + 1];
		d = sineBuffer[(long)phase + 2];

	}
	else {
		a = sineBuffer[(long)phase - 1];
		b = sineBuffer[(long)phase];
		c = sineBuffer[(long)phase + 1];
		d = sineBuffer[(long)phase + 2];

	}

	a1 = 0.5f * (c - a);
	a2 = a - 2.5 * b + 2.f * c - 0.5f * d;
	a3 = 0.5f * (d - a) + 1.5f * (b - c);
	output = double(((a3 * remainder + a2) * remainder + a1) * remainder + b);
	return(output);
}