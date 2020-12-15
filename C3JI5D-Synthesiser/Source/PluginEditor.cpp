#include "PluginProcessor.h"
#include "PluginEditor.h"

JuceSynthFrameworkAudioProcessorEditor::JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGui(p), osc2Gui(p), osc3Gui(p), lfoGui(p), envGui(p), filterGui(p), frontGui(p), delayGui(p)
{
    setSize(1400, 200);

    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&osc2Gui);
    addAndMakeVisible(&osc3Gui);
    addAndMakeVisible(&lfoGui);
    addAndMakeVisible(&envGui);
    addAndMakeVisible(&filterGui);
    addAndMakeVisible(&frontGui);

}

JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor()
{
}

void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void JuceSynthFrameworkAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    osc2Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    osc3Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    lfoGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    frontGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

}


