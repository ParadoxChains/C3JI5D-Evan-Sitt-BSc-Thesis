#include "../JuceLibraryCode/JuceHeader.h"
#include "FM.h"

FM::FM(JuceSynthFrameworkAudioProcessor& p) :
    processor(p)
{
    setSize(200, 200);

    fmSwitch.addItemList(processor.tree.getParameter("fmSwitch")->getAllValueStrings(), 1);

    fmSwitch.setJustificationType(Justification::centred);
    addAndMakeVisible(&fmSwitch);

    fmSwitchVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "fmSwitch", fmSwitch);

    fmRate.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmRate.setRange(1.0, 110.0);
    fmRate.setSkewFactorFromMidPoint(20.0);
    fmRate.setValue(1.0);
    fmRate.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&fmRate);
    fmRateVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "fmRate", fmRate);


    fmExtent.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmExtent.setRange(0.0f, 1.0f);
    fmExtent.setValue(0.5f);
    fmExtent.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&fmExtent);

    fmExtentVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "fmExtent", fmExtent);
}

FM::~FM()
{
}

void FM::paint(Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(Colours::powderblue);
    g.setColour(Colours::slategrey);
    g.drawText("Frequency Modulator", titleArea, Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(Colours::palevioletred);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void FM::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    fmSwitch.setBounds(area.removeFromTop(20));
    fmRate.setBounds(30, 100, 70, 70);
    fmExtent.setBounds(100, 100, 70, 70);
}
