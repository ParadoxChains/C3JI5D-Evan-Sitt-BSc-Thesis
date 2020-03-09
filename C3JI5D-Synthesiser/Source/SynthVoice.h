#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "WaveformSynthesis.h"
#include "Envelopes.h"
#include "Filters.h"
#include "Delays.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast <SynthSound*>(sound) != nullptr;
    }
    
    void setSampleRates(int sampleRate)
    {
        envelope01.setSampleRate(sampleRate);
        filter01.setSampleRate(sampleRate);

    }

    void setPitchBend(int pitchWheelPos)
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

    float pitchBendCents()
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

    static double noteHz(int midiNoteNumber, double centsOffset)
    {
        double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        hertz *= std::pow(2.0, centsOffset / 1200);
        return hertz;
    }

    void getOscType(float selection)
    {
        waveTypeSelection_oscillator01 = selection;
        
    }
    
    void getOsc2Type(float selection)
    {
        
        waveTypeSelection_oscillator02 = selection;
    }
   
    double setOscType ()
    
    {
        double sample1, sample2;
        
        switch (waveTypeSelection_oscillator01)
        {
            case 0:
                sample1 = oscillator01.square(frequency);
                break;
            case 1:
                sample1 = oscillator01.saw(frequency);
                break;
            case 2:
                sample1 = oscillator01.triangle(frequency);
                break;
            default:
                sample1 = oscillator01.sine(frequency);
                break;
        }
        
        switch (waveTypeSelection_oscillator02)
        {
            case 0:
                sample2 = oscillator02.square(frequency / 2.0);
                break;
            case 1:
                sample2 = oscillator02.saw(frequency / 2.0);
                break;
            case 2:
                sample2 = oscillator02.triangle(frequency / 2.0);
                break;
            default:
                sample2 = oscillator02.sine(frequency / 2.0);
                break;
        }
        
        return ((1.0 - mixLevel_oscillator02) * sample1) + (mixLevel_oscillator02 * sample2);
    }
    
    void getEnvelopeParams(float attack, float decay, float sustain, float release)
    {
        envelope01.setAttack(attack);
        envelope01.setDecay(decay);
        envelope01.setSustain(sustain);
        envelope01.setRelease(release);
    }
    
    double setEnvelope(double sample)
    {
        return envelope01.adsr(sample, envelope01.trigger);
    }
    
    void getWillsParams(float mGain, float blend, float pbup, float pbdn)
    {
        masterGain = mGain;
        mixLevel_oscillator02 = blend;
        pitchBendUpSemitones = pbup;
        pitchBendDownSemitones = pbdn;
    }
    
    void getFilterParams(float filterType, float filterCutoff, float filterRes)
    {
        filterChoice = filterType;
        cutoff = filterCutoff;
        resonance = filterRes;
    }

    double setFilter(double sample)
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

    void getDelayParams(float delayType, float dTime, float dFeedback, float dSpeed, float dDepth)
    {
        delayChoice = delayType;
        delayTime = dTime;
        delayFeedback = dFeedback;
        delaySpeed = dSpeed;
        delayDepth = dDepth;
    }

    double setDelay(double sample)
    {
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

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        noteNumber = midiNoteNumber;
        envelope01.trigger = 1;
        setPitchBend(currentPitchWheelPosition);
        frequency = noteHz(noteNumber, pitchBendCents());
        level = velocity;
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        envelope01.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        setPitchBend(newPitchWheelValue);
        frequency = noteHz(noteNumber, pitchBendCents());
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }

    double giveSample()
    {
        return masterGain * /*setDelay(*/setFilter(setEnvelope(setOscType()))/*)*/;
    }
    
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override
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
    
private:
    double level;
    double frequency;
    int waveTypeSelection_oscillator01, waveTypeSelection_oscillator02;

    float masterGain;
    float mixLevel_oscillator02;

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
    
    oscillator oscillator01, oscillator02;
    envelope envelope01;
    filter filter01;
    delay_chain delay01;
    flanger flanger01;
};
