#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class Oscillator3 : public Component
{
public:
    Oscillator3(JuceSynthFrameworkAudioProcessor&);
    ~Oscillator3();

    void paint(Graphics&) override;
    void resized() override;

private:
    ComboBox osc3Menu;
    Slider Blendslider;

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveTypeSelection_oscillator03;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal;

    JuceSynthFrameworkAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscillator3)
};
