/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "BaseProcessor.h"
#include "BaseEditor.h"


auto valueToDB = [](float x) {return juce::String(x) + " dB"; };
auto valueToMS = [](float x) {return juce::String(x) + " ms"; };

//==============================================================================
BaseAudioProcessor::BaseAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::mono(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    _state(nullptr)
#else
    :
_state(nullptr),
_threshold(-48.0f), _ratio(15.0f), _attack(23.0f), _release(20.0f)

#endif
{
    _state = new juce::AudioProcessorValueTreeState(*this, nullptr);
}

BaseAudioProcessor::~BaseAudioProcessor()
{
}

//==============================================================================
const juce::String BaseAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BaseAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool BaseAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool BaseAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double BaseAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BaseAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BaseAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BaseAudioProcessor::setCurrentProgram(int index)
{}

const juce::String BaseAudioProcessor::getProgramName(int index)
{
    return {};
}

void BaseAudioProcessor::changeProgramName(int index, const juce::String& newName)
{}


void BaseAudioProcessor::releaseResources()
{}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BaseAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

//==============================================================================
bool BaseAudioProcessor::hasEditor() const
{
    return true;
}


//==============================================================================
void BaseAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{}

void BaseAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return nullptr;
}
