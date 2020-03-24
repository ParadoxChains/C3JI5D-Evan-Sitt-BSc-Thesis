#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

Oscillator::Oscillator(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);

    oscMenu.addItemList(processor.tree.getParameter("wavetype")->getAllValueStrings(), 1);

    oscMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&oscMenu);
    
    waveTypeSelection_oscillator01 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype", oscMenu);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::powderblue);
    g.setColour(Colours::slategrey);
    g.drawText("Main Oscillator", titleArea, Justification::centredTop);
    
    juce::Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(Colours::palevioletred);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));
}
