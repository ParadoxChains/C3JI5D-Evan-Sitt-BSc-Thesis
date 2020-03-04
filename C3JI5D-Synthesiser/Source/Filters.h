#pragma once

class filter
{
private:
	double gain;
	double input;
	double output;
	double inputs[10];
	double outputs[10];
	double newCutoff;
	double x;
	double y;
	double z;
	double c;
	double twoPi;
	int sampleRate;
public:
	filter() :x(0.0), y(0.0), z(0.0), c(0.0), twoPi(6.28318530718), sampleRate(48000){};
	void setSampleRate(int newSampleRate);
	double cutoff;
	double resonance;
	double lowPass(double sample, double cutoff);
	double highPass(double sample, double cutoff);
	double lowPassResonance(double sample, double newCutoff, double resonance);
	double highPassResonance(double sample, double newCutoff, double resonance);
	double bandPass(double sample, double newCutoff, double resonance);
};