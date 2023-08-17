#include <stdio.h>
#include "chorus.hpp"

START_NAMESPACE_DISTRHO

   /**
      Plugin class constructor.
      You must set all parameter values to their defaults, matching the value in initParameter().
    */
Chorus::Chorus()
    : Plugin(PARAM_COUNT, 0, 0),
      delayLine1(getSampleRate(), 0.1),
      delayLine2(getSampleRate(), 0.1),
      delayLine3(getSampleRate(), 0.1),
      delayLine4(getSampleRate(), 0.1),
      lfo1(getSampleRate(), 2.0f, 0.0f, Oscillator::Waveform::SINE),
      lfo2(getSampleRate(), 2.0f, 0.0f,Oscillator::Waveform::SINE),
      lfo3(getSampleRate(), 2.0f, 0.0f,Oscillator::Waveform::SINE),
      lfo4(getSampleRate(), 2.0f, 0.0f,Oscillator::Waveform::SINE),
      testTone(getSampleRate(), 500.0f, 0.0f, 0.0f, Oscillator::Waveform::SINE),
      distortion(getSampleRate())
      {
    /**
      Initialize all our parameters to their defaults.
      In this example all parameters have 0 as default, so we can simply zero them.
    */
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------

/**
  Initialize the parameter @a index.
  This function will be called once, shortly after the plugin is created.
*/
void Chorus::initParameter(uint32_t index, Parameter& parameter)
{
    if (index >= PARAM_COUNT) { return; }

    struct ParamProps
    {
        bool automatable, boolean, integer, logarithmic, output, trigger;
        float min, max, def;
        const char* name;
        const char* symbol;
        const char* unit;
    };

    const auto setParamProps = [](auto& param, ParamProps props)
    {
        if(props.automatable){ param.hints |= kParameterIsAutomatable;}
        if(props.boolean){param.hints |= kParameterIsBoolean;}
        if(props.integer){param.hints |= kParameterIsInteger;}
        if(props.logarithmic){param.hints |= kParameterIsLogarithmic;}
        if(props.output){param.hints |= kParameterIsOutput;}
        if(props.trigger){param.hints |= kParameterIsTrigger | kParameterIsBoolean;}
        param.ranges.min = props.min;
        param.ranges.max = props.max;
        param.ranges.def = props.def;
        param.name = props.name;
        param.symbol = props.symbol;
        param.unit = props.unit;
    };

    switch (index)
    {
        // PARAMS
        case PARAM_PREGAIN:
            setParamProps(parameter, { .automatable=true, .min=0.1f, .max=2.0f, .def=1.0f, .name="Pre-Gain", .symbol="pregain" });
            break;
        case PARAM_DRIVE:
            setParamProps(parameter, { .automatable=true, .min=1.0f, .max=30.0f, .def=0.5f, .name="Drive", .symbol="drive" });
            break;
        case PARAM_DRYWET:
            setParamProps(parameter, { .automatable=true, .min=0.0f, .max=1.0f, .def=0.5f, .name="Dry/Wet", .symbol="drywet" });
            break;
        case PARAM_RATE:
            setParamProps(parameter, { .automatable=true, .min=0.1f, .max=20.0f, .def=2.0f, .name="Rate", .symbol="rate" });
            lfo1.setFrequency(rate);
            lfo2.setFrequency(rate * 0.5f);
            lfo3.setFrequency(rate * 0.25f);
            lfo4.setFrequency(rate * 0.125f);
            break;
        case PARAM_DEPTH:
            setParamProps(parameter, { .automatable=true, .min=0.0f, .max=1.0f, .def=1.0f, .name="Depth", .symbol="depth" });
            break;
        default:
            break;
    }
}

// -------------------------------------------------------------------
// Internal data
// -------------------------------------------------------------------

/**
  Get the current value of a parameter.
  The host may call this function from any context, including realtime processing.
*/
float Chorus::getParameterValue(uint32_t index) const
{
    switch (index)
    {
        // PARAMS
        case PARAM_DRYWET:
            return dryWet;
        case PARAM_RATE:
            return rate;
        case PARAM_DEPTH:
            return depth;
        case PARAM_PREGAIN:
            return preGain;
        case PARAM_DRIVE:
            return drive;
        default:
            return 0;
    }
}

/**
  Change a parameter value.
  The host may call this function from any context, including realtime processing.
  When a parameter is marked as automable, you must ensure no non-realtime
  operations are performed.
*/
void Chorus::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
    // PARAMS
    case PARAM_PREGAIN:
        preGain = value;
        distortion.setPreGain(preGain);
        break;
    case PARAM_DRIVE:
        drive = value;
        distortion.setDrive(drive);
        break;
    case PARAM_DRYWET:
        dryWet = value;
        break;
    case PARAM_RATE:
        rate = value;
        lfo1.setFrequency(rate);
        lfo2.setFrequency(rate * 0.5f);
        lfo3.setFrequency(rate * 0.25f);
        lfo4.setFrequency(rate * 0.125f);
        break;
    case PARAM_DEPTH:
        depth = value;
        lfo1.setAmplitude(depth);
        lfo2.setAmplitude(depth * 0.85f);
        lfo3.setAmplitude(depth * 0.7f);
        lfo4.setAmplitude(depth * 0.5f);
        break;
    default:
        break;
    }
}

// -------------------------------------------------------------------
// methods
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// Process

void Chorus::activate()
{
    // plugin is activated
}

void Chorus::deactivate()
{
    // plugin is deactivated
}

/**
  Run/process function for plugins with audio input.
*/
void Chorus::run(const float** inputs, float** outputs, uint32_t nframes)
{
    const float* const input = inputs[0];
          float* output      = outputs[0];
          float* output2     = outputs[1];  // stereo

    // run
    for (uint32_t currentFrame = 0; currentFrame < nframes; ++currentFrame)
    {
        // write
        delayLine1.write(distortion.process(input[currentFrame]));
        delayLine2.write(distortion.process(input[currentFrame]));
        delayLine3.write(distortion.process(input[currentFrame]));
        delayLine4.write(distortion.process(input[currentFrame]));

        // process
        delayLine1.setDistanceReadWriteHead(lfo1.getSample() + 1.0f);
        delayLine2.setDistanceReadWriteHead(lfo2.getSample() + 1.0f);
        delayLine3.setDistanceReadWriteHead(lfo3.getSample() + 1.0f);
        delayLine4.setDistanceReadWriteHead(lfo4.getSample() + 1.0f);

        // output
        output[currentFrame]  = 0.5f * ((1-dryWet) * distortion.process(input[currentFrame])
                              + (delayLine1.readWithInterpolation() + delayLine2.readWithInterpolation()) * dryWet);
        output2[currentFrame] = 0.5f * ((1-dryWet) * distortion.process(input[currentFrame])
                              + (delayLine3.readWithInterpolation() + delayLine4.readWithInterpolation()) * dryWet);

        // tick
        lfo1.tick();
        lfo2.tick();
        lfo3.tick();
        lfo4.tick();
        testTone.tick();
        delayLine1.tick();
        delayLine2.tick();
        delayLine3.tick();
        delayLine4.tick();
    }
}

// -------------------------------------------------------------------
// callbacks

/**
    Optional callback to inform the plugin about a sample rate change.
    This function will only be called when the plugin is deactivated.
*/
void Chorus::sampleRateChanged(double newSampleRate)
{
    (void)newSampleRate;
    delayLine1.setSampleRate(newSampleRate);
    delayLine2.setSampleRate(newSampleRate);
    delayLine3.setSampleRate(newSampleRate);
    delayLine4.setSampleRate(newSampleRate);
    lfo1.setSampleRate(newSampleRate);
    lfo2.setSampleRate(newSampleRate);
    lfo3.setSampleRate(newSampleRate);
    lfo4.setSampleRate(newSampleRate);

}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new Chorus();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO