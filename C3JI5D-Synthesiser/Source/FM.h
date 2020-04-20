#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class FM : public Component
{
public:
    FM(JuceSynthFrameworkAudioProcessor&);
    ~FM();

    void paint(Graphics&) override;
    void resized() override;

private:
    Slider fmRate;
    Slider fmExtent;

    ComboBox fmSwitch;

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> fmSwitchVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> fmRateVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> fmExtentVal;

    JuceSynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FM)
};
