#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class LFO : public Component
{
public:
    LFO(JuceSynthFrameworkAudioProcessor&);
    ~LFO();

    void paint(Graphics&) override;
    void resized() override;

private:
    Slider lfoFreq;
    Slider lfoBlend;

    ComboBox lfoSwitch;

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> lfoSwitchVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoFreqVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoBlendVal;

    JuceSynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO)
};
