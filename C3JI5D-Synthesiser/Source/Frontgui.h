#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class Frontgui    : public Component
{
public:
    Frontgui(JuceSynthFrameworkAudioProcessor&);
    ~Frontgui();
    
    void paint (Graphics&) override;
    void resized() override;
    
    
private:
    Slider mastergainSlider;
    Slider pbupSlider;
    Slider pbdownSlider;
    
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mastergainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbupVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbdownVal;
    

    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Frontgui)
};
