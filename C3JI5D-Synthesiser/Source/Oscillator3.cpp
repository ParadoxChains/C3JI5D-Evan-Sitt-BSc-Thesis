#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator3.h"

Oscillator3::Oscillator3(JuceSynthFrameworkAudioProcessor& p) :
    processor(p)
{
    setSize(200, 200);

    osc3Menu.addItemList(processor.tree.getParameter("wavetype3")->getAllValueStrings(), 1);

    osc3Menu.setJustificationType(Justification::centred);
    addAndMakeVisible(&osc3Menu);

    waveTypeSelection_oscillator03 = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype3", osc3Menu);

    Blendslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Blendslider.setRange(0.0f, 1.0f);
    Blendslider.setValue(0.5f);
    Blendslider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&Blendslider);

    blendVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "blend2", Blendslider);
}

Oscillator3::~Oscillator3()
{
}

void Oscillator3::paint(Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(Colours::powderblue);
    g.setColour(Colours::slategrey);
    g.drawText("Subtractive Oscillator", titleArea, Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(Colours::palevioletred);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator3::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    osc3Menu.setBounds(area.removeFromTop(20));

    int sliderWidth = 25;
    int sliderHeight = 175;

    Blendslider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
