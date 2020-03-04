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
	double lopass(double sample, double cutoff);
	double hipass(double sample, double cutoff);
	double lores(double sample, double newCutoff, double resonance);
	double hires(double sample, double newCutoff, double resonance);
	double bandpass(double sample, double newCutoff, double resonance);
};