#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator2.h"

Oscillator2::Oscillator2(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    osc2Menu.addItemList(processor.tree.getParameter("wavetype2")->getAllValueStrings(), 1);

    osc2Menu.setJustificationType(Justification::centred);
    addAndMakeVisible(&osc2Menu);
    
    waveTypeSelection_oscillator02 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype2", osc2Menu);
    
    Blendslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Blendslider.setRange(0.0f, 1.0f);
    Blendslider.setValue(0.5f);
    Blendslider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&Blendslider);
    
    blendVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "blend", Blendslider);
}

Oscillator2::~Oscillator2()
{
}

void Oscillator2::paint (Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::powderblue);
    g.setColour(Colours::slategrey);
    g.drawText("Oscillator Two", titleArea, Justification::centredTop);
    
    juce::Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(Colours::palevioletred);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator2::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    osc2Menu.setBounds(area.removeFromTop(20));
    
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    Blendslider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
