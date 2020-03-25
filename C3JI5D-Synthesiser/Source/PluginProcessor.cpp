#include "PluginProcessor.h"
#include "PluginEditor.h"


JuceSynthFrameworkAudioProcessor::JuceSynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
    , tree(*this, nullptr, "PARAMETERS",
        {   
            //Envelope parameters
            std::make_unique<AudioParameterFloat>("attack",
                                                  "Attack",
                                                  NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
            std::make_unique<AudioParameterFloat>("decay",
                                                  "Decay",
                                                  NormalisableRange<float>(1.0f, 2000.0f), 1.0f),
            std::make_unique<AudioParameterFloat>("sustain",
                                                  "Sustain",
                                                  NormalisableRange<float>(0.0f, 1.0f), 0.8f),
            std::make_unique<AudioParameterFloat>("release",
                                                  "Release",
                                                   NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
            //Main Oscillator Parameters
            std::make_unique<AudioParameterChoice>("wavetype",
                                             TRANS("Wave Type"),
                                       StringArray("Square", "Saw", "Triangle", "Sine"),
                                                  0),

            //Additive Oscillator Parameters
            std::make_unique<AudioParameterChoice>("wavetype2",
                                             TRANS("Wave Type 2"),
                                       StringArray("Square", "Saw", "Triangle"/*, "Sine"*/),
                                                  0),
            std::make_unique<AudioParameterFloat>("blend", "Osc2Blend", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
            
            //Subtractive Oscillator Parameters
            std::make_unique<AudioParameterChoice>("wavetype3",
                                             TRANS("Wave Type 3"),
                                       StringArray("Square", "Saw", "Triangle"/*, "Sine"*/),
                                                  0),
            std::make_unique<AudioParameterFloat>("blend2", "Osc3Blend", NormalisableRange<float>(0.0f, 1.0f), 0.5f),

            //LFO Parameters
            std::make_unique<AudioParameterChoice>("lfoSwitch",
                                             TRANS("LFO Switch"),
                                       StringArray("On","Off"),
                                                  1),
            std::make_unique<AudioParameterFloat>("lfoFreq",
                                                  "LFO Frequency",
                                                  NormalisableRange<float>(1.0f, 10000.0f),
                                                  400.0f),
            std::make_unique<AudioParameterFloat>("lfoBlend", "LFO Blend", NormalisableRange<float>(0.0f, 1.0f), 0.5f),

            //Filter Parameters
            std::make_unique<AudioParameterChoice>("filterType",
                                             TRANS("Filter Type"),
                                       StringArray("Low Pass","High Pass","Band Pass"),
                                                  0),
            std::make_unique<AudioParameterFloat>("filterCutoff", "FilterCutoff", NormalisableRange<float>(20.0f, 10000.0f), 400.0f),
            std::make_unique<AudioParameterFloat>("filterRes", "FilterRes", NormalisableRange<float>(1.0f, 5.0f), 1.0f),

            //Delay Parameters
            std::make_unique<AudioParameterChoice>("delayType",
                                            TRANS("Delay Type"),
                                      StringArray("Delay","Flanger"),
                                                 0),
            std::make_unique<AudioParameterFloat>("delayTime", "DelayTime", NormalisableRange<float>(1.0f, 5.0f), 1.0f),
            std::make_unique<AudioParameterFloat>("delayFeedback", "DelayFeedback", NormalisableRange<float>(1.0f, 5.0f), 1.0f),
            std::make_unique<AudioParameterFloat>("delaySpeed", "DelaySpeed", NormalisableRange<float>(20.0f, 10000.0f), 400.0f),
            std::make_unique<AudioParameterFloat>("delayDepth", "DelayDepth", NormalisableRange<float>(1.0f, 5.0f), 1.0f),


            std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", NormalisableRange<float>(0.0f, 1.0f), 0.7f),

            std::make_unique<AudioParameterFloat>("pbup", "PBup", NormalisableRange<float>(1.0f, 12.0f), 2.0f),
            std::make_unique<AudioParameterFloat>("pbdown", "PBdown", NormalisableRange<float>(1.0f, 12.0f), 2.0f),
        })
#endif
{
    mySynth.clearVoices();
    
    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

JuceSynthFrameworkAudioProcessor::~JuceSynthFrameworkAudioProcessor()
{
}

const String JuceSynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceSynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceSynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceSynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;
}

int JuceSynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceSynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceSynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceSynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void JuceSynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    stateVariableFilter.reset();
    stateVariableFilter.prepare(spec);
    updateFilter();
    
}

void JuceSynthFrameworkAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceSynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JuceSynthFrameworkAudioProcessor::updateFilter()
{

    
    int menuChoice = tree.getRawParameterValue("filterType")->load();
    int freq = tree.getRawParameterValue("filterCutoff")->load();
    int res = tree.getRawParameterValue("filterRes")->load();
    
    if (menuChoice == 0)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
    
    if (menuChoice == 1)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
    
    if (menuChoice == 2)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
    
}

void JuceSynthFrameworkAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->setSampleRates(48000);

            myVoice->getLFOParams(
                tree.getRawParameterValue("lfoSwitch")->load(),
                tree.getRawParameterValue("lfoFreq")->load(),
                tree.getRawParameterValue("lfoBlend")->load()
            );

            myVoice->getFilterParams(
                tree.getRawParameterValue("filterType")->load(),
                tree.getRawParameterValue("filterCutoff")->load(),
                tree.getRawParameterValue("filterRes")->load()
            );
            /*
            myVoice->getDelayParams(
                tree.getRawParameterValue("delayType")->load(),
                tree.getRawParameterValue("delayTime")->load(),
                tree.getRawParameterValue("delayFeedback")->load(),
                tree.getRawParameterValue("delaySpeed")->load(),
                tree.getRawParameterValue("delayDepth")->load()
            );
            */
            myVoice->getEnvelopeParams(
                tree.getRawParameterValue("attack")->load(),
                tree.getRawParameterValue("decay")->load(),
                tree.getRawParameterValue("sustain")->load(),
                tree.getRawParameterValue("release")->load()
            );
            
            myVoice->getOscType(tree.getRawParameterValue("wavetype")->load());
            myVoice->getOsc2Type(tree.getRawParameterValue("wavetype2")->load());
            myVoice->getOsc3Type(tree.getRawParameterValue("wavetype3")->load());
            
            
            myVoice->getWillsParams(
                tree.getRawParameterValue("mastergain")->load(),
                tree.getRawParameterValue("blend")->load(),
                tree.getRawParameterValue("blend2")->load(),
                tree.getRawParameterValue("pbup")->load(),
                tree.getRawParameterValue("pbdown")->load()
            );
        }
    }
    
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    updateFilter();
    dsp::AudioBlock<float> block (buffer);
    stateVariableFilter.process(dsp::ProcessContextReplacing<float> (block));
    
}

bool JuceSynthFrameworkAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* JuceSynthFrameworkAudioProcessor::createEditor()
{
    return new JuceSynthFrameworkAudioProcessorEditor (*this);
}

void JuceSynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{

}

void JuceSynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceSynthFrameworkAudioProcessor();
}
