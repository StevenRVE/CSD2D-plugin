//
// Created by steve on 10-8-2023.
// DistrhoUI code based on FalkTX's 3BandEQ plugin:
// https://github.com/DISTRHO/DPF-Plugins/blob/master/plugins/3BandEQ/DistrhoUI3BandEQ.cpp
//

#include "chorus.hpp"
#include "chorusUI.hpp"

START_NAMESPACE_DISTRHO

namespace Art = SvEArtworkChorus;

    ChorusUI::ChorusUI()
    : UI(Art::backpanelWidth, Art::backpanelHeight, true),
      imgBackpanel(Art::backpanelData, Art::backpanelWidth, Art::backpanelHeight,
                   kImageFormatBGRA)
{
    // knobs
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight, kImageFormatBGRA);

    // knob Pre-Gain
    knobPreGain = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    knobPreGain->setId(Chorus::PARAM_PREGAIN);
    knobPreGain->setAbsolutePos(63, 113);
    knobPreGain->setRange(0.1f, 2.0f);
    knobPreGain->setDefault(0.5f);
    knobPreGain->setRotationAngle(180);
    knobPreGain->setCallback(this);

    // knob Drive
    knobDrive = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    knobDrive->setId(Chorus::PARAM_DRIVE);
    knobDrive->setAbsolutePos(163, 113);
    knobDrive->setRange(0.1f, 10.0f);
    knobDrive->setDefault(0.5f);
    knobDrive->setRotationAngle(180);
    knobDrive->setCallback(this);

    // knob Dry/Wet
    knobDryWet = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    knobDryWet->setId(Chorus::PARAM_DRYWET);
    knobDryWet->setAbsolutePos(263, 113);
    knobDryWet->setRange(0.0f, 1.0f);
    knobDryWet->setDefault(0.5f);
    knobDryWet->setRotationAngle(180);
    knobDryWet->setCallback(this);

    // knob Rate
    knobRate = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    knobRate->setId(Chorus::PARAM_RATE);
    knobRate->setAbsolutePos(113, 263);
    knobRate->setRange(0.1f, 20.0f);
    knobRate->setDefault(1.0f);
    knobRate->setRotationAngle(180);
    knobRate->setCallback(this);

    // knob Depth
    knobDepth = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    knobDepth->setId(Chorus::PARAM_DEPTH);
    knobDepth->setAbsolutePos(213, 263);
    knobDepth->setRange(0.0f, 1.0f);
    knobDepth->setDefault(1.0f);
    knobDepth->setRotationAngle(180);
    knobDepth->setCallback(this);
}

// -----------------------------------------------------------------------
// DSP Callbacks

void ChorusUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
        // PARAMS
        case Chorus::PARAM_PREGAIN:
            knobPreGain->setValue(value);
            break;
        case Chorus::PARAM_DRIVE:
            knobDrive->setValue(value);
            break;
        case Chorus::PARAM_DRYWET:
            knobDryWet->setValue(value);
            break;
        case Chorus::PARAM_RATE:
            knobRate->setValue(value);
            break;
        case Chorus::PARAM_DEPTH:
            knobDepth->setValue(value);
            break;
        default:
            break;
    }
}

// -----------------------------------------------------------------------
// Widgets Callbacks

void ChorusUI::imageKnobDragStarted(ImageKnob* knob)
{
    editParameter(knob->getId(), true);
}

void ChorusUI::imageKnobDragFinished(ImageKnob* knob)
{
    editParameter(knob->getId(), false);
}

void ChorusUI::imageKnobValueChanged(ImageKnob* knob, float value)
{
    setParameterValue(knob->getId(), value);
}

void ChorusUI::onDisplay() {
    const GraphicsContext& context(getGraphicsContext());

    imgBackpanel.draw(context);
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new ChorusUI();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO