#include "../JuceLibraryCode/JuceHeader.h"
#include "Frontgui.h"

Frontgui::Frontgui(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    mastergainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mastergainSlider.setRange(0.0f, 1.0f);
    mastergainSlider.setValue(1.0f);
    mastergainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mastergainSlider);
    
    pbupSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pbupSlider.setRange(0, 12, 1);
    pbupSlider.setValue(12);
    pbupSlider.setTextBoxStyle(Slider::TextBoxRight, true, 35, 25);
    addAndMakeVisible(&pbupSlider);
    
    pbdownSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pbdownSlider.setRange(0, 12, 1);
    pbdownSlider.setValue(12);
    pbdownSlider.setTextBoxStyle(Slider::TextBoxRight, true, 35, 25);
    addAndMakeVisible(&pbdownSlider);
    
    mastergainVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "mastergain", mastergainSlider);
    pbupVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "pbup", pbupSlider);
    pbdownVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "pbdown", pbdownSlider);
}

Frontgui::~Frontgui()
{
}

void Frontgui::paint (Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::powderblue);
    g.setColour(Colours::slategrey);
    g.drawText("Main", titleArea, Justification::centredTop);
    
    g.drawText ("Master", 53, 40, 40, 20, Justification::centredLeft);
    g.drawText ("PB Up/Down", 53, 90, 90, 20, Justification::centredLeft);
    
    
    
    juce::Rectangle<float> area (25, 25, 150, 150);
    
    g.setColour(Colours::palevioletred);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Frontgui::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderWidth = 25;
    int sliderHeight = 25;
    
    mastergainSlider.setBounds (45, 20, 120, 100 );
    pbdownSlider.setBounds (area.removeFromBottom(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    pbupSlider.setBounds (area.removeFromBottom(sliderHeight).removeFromTop(sliderWidth).withTrimmedTop(10));
    
}
