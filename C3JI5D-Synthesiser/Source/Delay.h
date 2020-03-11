#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class Delay : public Component
{
public:
    Delay(JuceSynthFrameworkAudioProcessor&);
    ~Delay();

    void paint(Graphics&) override;
    void resized() override;

private:
    Slider delayTime;
    Slider delayFeedback;
    Slider delaySpeed;
    Slider delayDepth;

    ComboBox delayMenu;

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> delayTypeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayTimeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayFeedbackVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delaySpeedVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayDepthVal;

    JuceSynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Delay)
};
