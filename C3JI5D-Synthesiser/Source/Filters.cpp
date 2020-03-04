#include "Filters.h"
#include "math.h"

void filter::setSampleRate(int newSampleRate)
{
	sampleRate = newSampleRate;
}

double filter::lopass(double sample, double cutoff)
{
	output = outputs[0] + cutoff * (sample - outputs[0]);
	outputs[0] = output;
	return(output);
}


double filter::hipass(double sample, double cutoff)
{
	output = sample - (outputs[0] + cutoff * (sample - outputs[0]));
	outputs[0] = output;
	return(output);
}

double filter::lores(double sample, double newCutoff, double resonance)
{
	cutoff = newCutoff;
	if (cutoff < 10) cutoff = 10;
	if (cutoff > (sampleRate)) cutoff = (sampleRate);
	if (resonance < 1.) resonance = 1.;
	z = cos(twoPi * cutoff / sampleRate);
	c = 2 - 2 * z;
	double r = (sqrt(2.0) * sqrt(-pow((z - 1.0), 3.0)) + resonance * (z - 1)) / (resonance * (z - 1));
	x = x + (sample - y) * c;
	y = y + x;
	x = x * r;
	output = y;
	return(output);
}


double filter::hires(double sample, double newCutoff, double resonance)
{
	cutoff = newCutoff;
	if (cutoff < 10) cutoff = 10;
	if (cutoff > (sampleRate)) cutoff = (sampleRate);
	if (resonance < 1.) resonance = 1.;
	z = cos(twoPi * cutoff / sampleRate);
	c = 2 - 2 * z;
	double r = (sqrt(2.0) * sqrt(-pow((z - 1.0), 3.0)) + resonance * (z - 1)) / (resonance * (z - 1));
	x = x + (sample - y) * c;
	y = y + x;
	x = x * r;
	output = sample - y;
	return(output);
}


double filter::bandpass(double sample, double newCutoff, double resonance)
{
	cutoff = newCutoff;
	if (cutoff > (sampleRate * 0.5)) cutoff = (sampleRate * 0.5);
	if (resonance >= 1.) resonance = 0.999999;
	z = cos(twoPi * cutoff / sampleRate);
	inputs[0] = (1 - resonance) * (sqrt(resonance * (resonance - 4.0 * pow(z, 2.0) + 2.0) + 1));
	inputs[1] = 2 * z * resonance;
	inputs[2] = pow((resonance * -1), 2);

	output = inputs[0] * sample + inputs[1] * outputs[1] + inputs[2] * outputs[2];
	outputs[2] = outputs[1];
	outputs[1] = output;
	return(output);
}