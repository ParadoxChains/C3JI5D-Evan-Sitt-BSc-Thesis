#include "../JuceLibraryCode/JuceHeader.h"
#include "Delay.h"

Delay::Delay(JuceSynthFrameworkAudioProcessor& p) :
    processor(p)
{
    setSize(200, 200);

    delayMenu.addItemList(processor.tree.getParameter("delayType")->getAllValueStrings(), 1);

    delayMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&delayMenu);

    delayTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "delayType", delayMenu);

    delayTime.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTime.setRange(1, 5);
    delayTime.setValue(1);
    delayTime.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&delayTime);
    delayTimeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "delayTime", delayTime);

    delayFeedback.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayFeedback.setRange(1, 5);
    delayFeedback.setValue(1);
    delayFeedback.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&delayFeedback);
    delayFeedbackVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "delayFeedback", delayFeedback);

    delaySpeed.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delaySpeed.setRange(20.0, 10000.0);
    delaySpeed.setValue(400.0);
    delaySpeed.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&delaySpeed);
    delaySpeedVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "delaySpeed", delaySpeed);
    delaySpeed.setSkewFactorFromMidPoint(1000.0);

    delayDepth.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayDepth.setRange(1, 5);
    delayDepth.setValue(1);
    delayDepth.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&delayDepth);
    delayDepthVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "delayDepth", delayDepth);


}

Delay::~Delay()
{
}

void Delay::paint(Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(Colours::powderblue);
    g.setColour(Colours::slategrey);
    g.drawText("Delay", titleArea, Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 300, 150);

    g.setColour(Colours::palevioletred);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Delay::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    delayMenu.setBounds(area.removeFromTop(20));
    delayTime.setBounds(30, 100, 70, 70);
    delayFeedback.setBounds(100, 100, 70, 70);
    delaySpeed.setBounds(170, 100, 70, 70);
    delayDepth.setBounds(240, 100, 70, 70);
}
