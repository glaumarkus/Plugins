
#include "BaseProcessor.h"
#include "BaseEditor.h"


//==============================================================================
BaseEditor::BaseEditor(BaseAudioProcessor* p)
    : AudioProcessorEditor(p), audioProcessor(p)
{}

BaseEditor::~BaseEditor()
{}

