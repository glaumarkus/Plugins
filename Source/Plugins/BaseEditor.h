#pragma once

#include <JuceHeader.h>
#include "BaseProcessor.h"

//==============================================================================
/**
*/
class BaseEditor : public juce::AudioProcessorEditor
{
public:

    BaseEditor(BaseAudioProcessor*);
    ~BaseEditor() override;

    //==============================================================================
    virtual void paint(juce::Graphics&) override = 0;
    virtual void resized() override = 0;

private:

    juce::ScopedPointer<BaseAudioProcessor> audioProcessor;
    //BaseAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BaseEditor)
};

