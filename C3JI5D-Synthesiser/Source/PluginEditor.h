#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Oscillator2.h"
#include "Oscillator3.h"
#include "LFO.h"
#include "Envelope.h"
#include "Filter.h"
#include "Frontgui.h"
#include "Delay.h"


class JuceSynthFrameworkAudioProcessorEditor  : public AudioProcessorEditor

{
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&);
    ~JuceSynthFrameworkAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    
    

private:
    JuceSynthFrameworkAudioProcessor& processor;
    
    Oscillator oscGui;
    Oscillator2 osc2Gui;
    Oscillator3 osc3Gui;
    Envelope envGui;
    Filter filterGui;
    Delay delayGui;
    Frontgui frontGui;
    LFO lfoGui;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessorEditor)
};
