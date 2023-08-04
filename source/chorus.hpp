#ifndef _H_CHORUS_
#define _H_CHORUS_

// framework
#include "DistrhoPlugin.hpp"

// classes
#include "circularBuffer.hpp"
#include "oscillator.hpp"

// libs
#include <cstdint>
#include <iostream>

// constants
#define EXAMPLE         1

START_NAMESPACE_DISTRHO

/**
  Your plugin class that subclasses the base DPF Plugin one.
*/
class Chorus : public Plugin
{
public:
    // TODO: add pre-delay as parameter (in samples)
    enum Parameters {
        PARAM_GAIN,
        PARAM_RATE,
        PARAM_DEPTH,
        PARAM_COUNT
    };

    /**
      Plugin class constructor.
      You must set all parameter values to their defaults, matching the value in initParameter().
    */
    Chorus();

protected:
    // -------------------------------------------------------------------
    // Information

    /**
      Get the plugin label.
      This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
    */
    const char* getLabel() const noexcept override { return "chorus"; }

    /**
      Get an extensive comment/description about the plugin.
      Optional, returns nothing by default.
    */
    const char* getDescription() const override { return "sve-chorus"; }

    /**
      Get the plugin author/maker.
    */
    const char* getMaker() const noexcept override { return "SvE plugins"; }

    /**
      Get the plugin license (a single line of text or a URL).
      For commercial plugins this should return some short copyright information.
    */
    const char* getLicense() const noexcept override { return "ISC"; }

    /**
      Get the plugin version, in hexadecimal.
      @see d_version()
    */
    uint32_t getVersion() const noexcept override { return d_version(0, 0, 0); }

    /**
      Get the plugin unique Id.
      This value is used by LADSPA, DSSI and VST plugin formats.
      @see d_cconst()
    */
    int64_t getUniqueId() const noexcept override { return d_cconst('S', 'v', 'E', 'C'); }

    // -------------------------------------------------------------------
    // Init

    /**
      Initialize the parameter @ index.
      This function will be called once, shortly after the plugin is created.
    */
    void initParameter(uint32_t index, Parameter& parameter) override;

    // -------------------------------------------------------------------
    // Internal data

    /**
      Get the current value of a parameter.
      The host may call this function from any context, including realtime processing.
    */
    float getParameterValue(uint32_t index) const override;

    /**
      Change a parameter value.
      The host may call this function from any context, including realtime processing.
      When a parameter is marked as automable, you must ensure no non-realtime
      operations are performed.
    */
    void setParameterValue(uint32_t index, float value) override;

    // -------------------------------------------------------------------
    // methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Process

    void activate() override;

    void deactivate() override;

    /**
      Run/process function for plugins with Audio input.
    */
    void run(const float** inputs, float** outputs, uint32_t nframes) override;

    // -------------------------------------------------------------------
    // callbacks

    /**
        Optional callback to inform the plugin about a sample rate change.
        This function will only be called when the plugin is deactivated.
    */
    void sampleRateChanged(double newSampleRate) override;

private:
    // variables
    float gain{1.0f};
    float rate{500.0f};
    float depth{1.0f};
    float preDelay{10.0f};

    // objects
    CircularBuffer delayLine;
    Oscillator lfo;

    /**
        Set our plugin class as non-copyable and add a leak detector just in case.
    */
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Chorus)
};

END_NAMESPACE_DISTRHO

#endif // _H_CHORUS_