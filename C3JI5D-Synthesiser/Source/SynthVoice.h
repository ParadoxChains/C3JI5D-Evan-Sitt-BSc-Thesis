#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "WaveformSynthesis.h"
#include "Envelopes.h"
#include "Filters.h"
#include "Delays.h"


class SynthVoice : public SynthesiserVoice
{
private:
    double level;
    double frequency;
    int waveTypeSelection_oscillator01;

    int waveTypeSelection_oscillator02;
    float mixLevel_oscillator02;

    int waveTypeSelection_oscillator03;
    float mixLevel_oscillator03;

    int lfoSwitchSelection01;
    float lfoFrequency01;
    float lfoMixLevel01;

    float masterGain;

    int noteNumber;
    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;

    int filterChoice;
    float cutoff;
    float resonance;

    int delayChoice;
    float delayTime;
    float delayFeedback;
    float delaySpeed;
    float delayDepth;

    oscillator oscillator01;
    oscillator oscillator02;
    oscillator oscillator03;
    oscillator lfo01;
    envelope envelope01;
    filter filter01;
    delay_chain delay01;
    flanger flanger01;

public:
    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast <SynthSound*>(sound) != nullptr;
    }

    void setSampleRates(int sampleRate);

    void setPitchBend(int pitchWheelPos);

    float pitchBendCents();

    static double noteHz(int midiNoteNumber, double centsOffset)
    {
        double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        hertz *= std::pow(2.0, centsOffset / 1200);
        return hertz;
    }

    void getOscType(float selection);

    void getOsc2Type(float selection);

    void getOsc3Type(float selection);

    double setOscType();

    void getLFOParams(int newLfoSwitch, float newLfoFreq, float newLfoBlend);

    double setLFO(double sample);

    void getEnvelopeParams(float attack, float decay, float sustain, float release);

    double setEnvelope(double sample);

    void getWillsParams(float mGain, float blend, float blend2, float pbup, float pbdn);

    void getFilterParams(float filterType, float filterCutoff, float filterRes);

    double setFilter(double sample);

    void getDelayParams(float delayType, float dTime, float dFeedback, float dSpeed, float dDepth);

    double setDelay(double sample);

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        noteNumber = midiNoteNumber;
        envelope01.trigger = 1;
        setPitchBend(currentPitchWheelPosition);
        frequency = noteHz(noteNumber, pitchBendCents());
        level = velocity;
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        envelope01.trigger = 0;
        allowTailOff = true;

        if (velocity == 0)
            clearCurrentNote();
    }

    void pitchWheelMoved(int newPitchWheelValue) override
    {
        setPitchBend(newPitchWheelValue);
        frequency = noteHz(noteNumber, pitchBendCents());
    }

    void controllerMoved(int controllerNumber, int newControllerValue) override
    {

    }

    double giveSample();

    void renderNextBlock(AudioBuffer <float>& outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, giveSample());
            }
            ++startSample;
        }
    }


};
