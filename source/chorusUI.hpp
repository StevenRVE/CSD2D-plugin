//
// Created by steve on 10-8-2023.
// DistrhoUI code based on https://github.com/DISTRHO/DPF-Plugins/blob/master/plugins/3BandEQ/DistrhoUI3BandEQ.hpp
//

#ifndef SVE_CHORUS_UI_HPP
#define SVE_CHORUS_UI_HPP

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"

#include "SvEArtworkChorus.hpp"

START_NAMESPACE_DISTRHO

class ChorusUI : public UI,
                 public ImageKnob::Callback
{
public:
    ChorusUI();

protected:
    // DSP Callbacks
    void parameterChanged(uint32_t index, float value) override;

    // Widget Callbacks
    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;

    void onDisplay() override;

private:
    Image imgBackpanel;

    ScopedPointer<ImageKnob> knobDryWet, knobRate, knobDepth, knobPreGain, knobDrive;
};

END_NAMESPACE_DISTRHO

#endif //SVE_CHORUS_UI_HPP
