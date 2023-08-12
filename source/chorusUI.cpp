//
// Created by steve on 10-8-2023.
// DistrhoUI code based on https://github.com/DISTRHO/DPF-Plugins/blob/master/plugins/3BandEQ/DistrhoUI3BandEQ.cpp
//

#include "chorus.hpp"
#include "chorusUI.hpp"

START_NAMESPACE_DISTRHO

namespace Art = SvEArtworkChorus;

    ChorusUI::ChorusUI()
    : UI(Art::backpanelWidth, Art::backpanelHeight, true),
      imgBackpanel(Art::backpanelData, Art::backpanelWidth, Art::backpanelHeight,
                   kImageFormatBGR)
{
    // knobs
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight, kImageFormatBGR);

    // knob Pre-Gain
    knobPreGain = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    knobPreGain->setId(Chorus::PARAM_PREGAIN);
    knobPreGain->setAbsolutePos(63, 113);
    knobPreGain->setRange(0.1f, 2.0f);
    knobPreGain->setDefault(0.5f);
    knobPreGain->setCallback(this);

    // knob Drive
    knobPreGain = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    knobPreGain->setId(Chorus::PARAM_DRIVE);
    knobPreGain->setAbsolutePos(163, 113);
    knobPreGain->setRange(0.1f, 10.0f);
    knobPreGain->setDefault(0.5f);
    knobPreGain->setCallback(this);
    // knob Dry/Wet

    // knob Rate

    // knob Depth


}

END_NAMESPACE_DISTRHO