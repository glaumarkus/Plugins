
#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class BaseAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    BaseAudioProcessor();
    ~BaseAudioProcessor() override;

    //==============================================================================

    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif


    //==============================================================================
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;


    // abstracts to be defined
    virtual juce::AudioProcessorEditor* createEditor() override = 0;
    virtual void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override = 0;
    virtual void prepareToPlay(double sampleRate, int samplesPerBlock) override = 0;

    juce::AudioProcessorValueTreeState& getState() { return *_state; }

private:

    juce::ScopedPointer<juce::AudioProcessorValueTreeState> _state;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BaseAudioProcessor)
};
