#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO.h"

LFO::LFO(JuceSynthFrameworkAudioProcessor& p) :
    processor(p)
{
    setSize(200, 200);

    lfoSwitch.addItemList(processor.tree.getParameter("lfoSwitch")->getAllValueStrings(), 1);

    lfoSwitch.setJustificationType(Justification::centred);
    addAndMakeVisible(&lfoSwitch);

    lfoSwitchVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "lfoSwitch", lfoSwitch);

    lfoFreq.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoFreq.setRange(20.0, 10000.0);
    lfoFreq.setValue(400.0);
    lfoFreq.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&lfoFreq);
    lfoFreqVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoFreq", lfoFreq);
    lfoFreq.setSkewFactorFromMidPoint(1000.0);

    lfoBlend.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoBlend.setRange(0.0f, 1.0f);
    lfoBlend.setValue(0.5f);
    lfoBlend.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&lfoBlend);

    lfoBlendVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoBlend", lfoBlend);
}

LFO::~LFO()
{
}

void LFO::paint(Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(Colours::powderblue);
    g.setColour(Colours::slategrey);
    g.drawText("Low Frequency Oscillator", titleArea, Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(Colours::palevioletred);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void LFO::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    lfoSwitch.setBounds(area.removeFromTop(20));
    lfoFreq.setBounds(30, 100, 70, 70);
    lfoBlend.setBounds(100, 100, 70, 70);
}
