#include "SynthVoice.h"


void SynthVoice::setSampleRates(int sampleRate)
{
    envelope01.setSampleRate(sampleRate);
    filter01.setSampleRate(sampleRate);

}

void SynthVoice::setPitchBend(int pitchWheelPos)
{
    if (pitchWheelPos > 8192)
    {
        pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
    }
    else
    {
        pitchBend = float(8192 - pitchWheelPos) / -8192;
    }
}

float SynthVoice::pitchBendCents()
{
    if (pitchBend >= 0.0f)
    {
        return pitchBend * pitchBendUpSemitones * 100;
    }
    else
    {
        return pitchBend * pitchBendDownSemitones * 100;
    }
}


void SynthVoice::getOscType(float selection)
{
    waveTypeSelection_oscillator01 = selection;

}

void SynthVoice::getOsc2Type(float selection)
{

    waveTypeSelection_oscillator02 = selection;
}

void SynthVoice::getOsc3Type(float selection)
{

    waveTypeSelection_oscillator03 = selection;
}


double SynthVoice::setOscType()

{
    double osc1sample;
    double osc2sample;
    double osc3sample;
    double osc1mix;
    double osc2mix;
    double osc3mix;

    switch (waveTypeSelection_oscillator01)
    {
    case 0:
        osc1sample = oscillator01.square(frequency);
        break;
    case 1:
        osc1sample = oscillator01.saw(frequency);
        break;
    case 2:
        osc1sample = oscillator01.triangle(frequency);
        break;
    default:
        osc1sample = oscillator01.sine(frequency);
        break;
    }

    switch (waveTypeSelection_oscillator02)
    {
    case 0:
        osc2sample = oscillator02.square(frequency / 2.0);
        break;
    case 1:
        osc2sample = oscillator02.saw(frequency / 2.0);
        break;
    case 2:
        osc2sample = oscillator02.triangle(frequency / 2.0);
        break;
    default:
        osc2sample = oscillator02.sine(frequency / 2.0);
        break;
    }

    switch (waveTypeSelection_oscillator03)
    {
    case 0:
        osc3sample = oscillator03.square(frequency / 2.0);
        break;
    case 1:
        osc3sample = oscillator03.saw(frequency / 2.0);
        break;
    case 2:
        osc3sample = oscillator03.triangle(frequency / 2.0);
        break;
    default:
        osc3sample = oscillator03.sine(frequency / 2.0);
        break;
    }
    osc1mix = (1.0 - mixLevel_oscillator02) * osc1sample;
    osc2mix = mixLevel_oscillator02 * osc2sample;
    osc3mix = mixLevel_oscillator03 * osc3sample;
    return osc1mix + osc2mix - osc3mix;
}

void SynthVoice::getLFOParams(int newLfoSwitch, float newLfoFreq, float newLfoBlend)
{
    lfoSwitchSelection01 = newLfoSwitch;
    lfoFrequency01 = newLfoFreq;
    lfoMixLevel01 = newLfoBlend;
}

double SynthVoice::setLFO(double sample)
{
    double lfoMix;
    double sampleMix;
    double newSample;
    switch (lfoSwitchSelection01)
    {
    case 0:
        sampleMix = sample * (1 - lfoMixLevel01);
        lfoMix = sample * lfo01.sine(lfoFrequency01) * lfoMixLevel01;
        newSample = sampleMix + lfoMix;
        break;
    case 1:
        newSample = sample;
        break;
    default:
        newSample = 0.0;
        break;
    }
    return newSample;
}

void SynthVoice::getEnvelopeParams(float attack, float decay, float sustain, float release)
{
    envelope01.setAttack(attack);
    envelope01.setDecay(decay);
    envelope01.setSustain(sustain);
    envelope01.setRelease(release);
}

double SynthVoice::setEnvelope(double sample)
{
    return envelope01.adsr(sample, envelope01.trigger);
}

void SynthVoice::getWillsParams(float mGain, float blend, float blend2, float pbup, float pbdn)
{
    masterGain = mGain;
    mixLevel_oscillator02 = blend;
    mixLevel_oscillator03 = blend2;
    pitchBendUpSemitones = pbup;
    pitchBendDownSemitones = pbdn;
}

void SynthVoice::getFilterParams(float filterType, float filterCutoff, float filterRes)
{
    filterChoice = filterType;
    cutoff = filterCutoff;
    resonance = filterRes;
}

double SynthVoice::setFilter(double sample)
{

    switch (filterChoice)
    {
    case 0:
        return filter01.lowPassResonance(sample, cutoff, resonance);
    case 1:
        return filter01.highPassResonance(sample, cutoff, resonance);
    case 2:
        return filter01.bandPass(sample, cutoff, resonance);
    default:
        return sample;
        break;
    }

    //return sample;
}

void SynthVoice::getDelayParams(float delayType, float dTime, float dFeedback, float dSpeed, float dDepth)
{
    delayChoice = delayType;
    delayTime = dTime;
    delayFeedback = dFeedback;
    delaySpeed = dSpeed;
    delayDepth = dDepth;
}

double SynthVoice::setDelay(double sample)
{
    getDelayParams(0, 0.25, 0.1, 0.1, 0.1);
    switch (delayChoice)
    {
    case 0:
        return delay01.dl(sample, delayTime, delayFeedback);
    case 1:
        return flanger01.flange(sample, delayTime, delayFeedback, delaySpeed, delayDepth);
    default:
        return sample;
        break;
    }
}

double SynthVoice::giveSample()
{
    return masterGain * setDelay(setDelay(setFilter(setEnvelope(setLFO(setOscType())))));
}
