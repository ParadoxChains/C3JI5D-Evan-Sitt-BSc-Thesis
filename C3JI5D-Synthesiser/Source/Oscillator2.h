#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class Oscillator2    : public Component
{
public:
    Oscillator2(JuceSynthFrameworkAudioProcessor&);
    ~Oscillator2();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    ComboBox osc2Menu;
    Slider Blendslider;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveTypeSelection_oscillator02;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal;
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator2)
};
