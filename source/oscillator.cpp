//
// Created by steve on 4-8-2023.
//

#include "oscillator.hpp"

Oscillator::Oscillator(double sampleRate, float frequency, Waveform waveform) :
frequency(frequency),
waveform(waveform)
{

}

Oscillator::~Oscillator()
{

}

void Oscillator::setSampleRate(double sampleRate)
{
    this->sampleRate = sampleRate;
}

void Oscillator::setFrequency(float frequency)
{
    this->frequency = frequency;
}

void Oscillator::setPhase(float phase)
{
    this->phase = phase;
}

void Oscillator::setWaveform(Waveform waveform)
{
    this->waveform = waveform;
}

void Oscillator::setAmplitude(float amplitude)
{
    this->amplitude = amplitude;
}

void Oscillator::tick()
{
    switch (waveform) {
        case SINE:
            calculateNextSineSample();
        case TRIANGLE:
            calculateNextTriangleSample();
        case SAWTOOTH:
            calculateNextSawtoothSample();
        case SQUARE:
            calculateNextSquareSample();
        case INVERSE_SAWTOOTH:
            calculateNextInverseSawtoothSample();
    }
}

float Oscillator::getSample()
{
    return sample;
}

void Oscillator::calculateNextSineSample()
{
    static const double phaseIncrement = TWOPI * frequency / 44100.0;

    double value = sin(phase);
    phase += phaseIncrement;

    if (phase > TWOPI) {
        phase -= TWOPI;
    }

    sample = value;
}

// TODO: implement amplitude variable in other waveforms
// TODO: improve formulas for other waveforms
void Oscillator::calculateNextTriangleSample()
{
    double value = 0.0;
    if (phase < M_PI) {
        value = -1.0 + 2.0 * phase / M_PI;
    } else {
        value = 3.0 - 2.0 * phase / M_PI;
    }
    phase += TWOPI * frequency / 44100.0;
    if (phase > TWOPI) {
        phase -= TWOPI;
    }
    sample = value;
}

void Oscillator::calculateNextSawtoothSample()
{
    double value = -1.0 + 2.0 * phase / (TWOPI);
    phase += TWOPI * frequency / 44100.0;
    if (phase > TWOPI) {
        phase -= TWOPI;
    }
    sample = value;
}

void Oscillator::calculateNextSquareSample()
{
    double value = 0.0;
    if (phase < M_PI) {
        value = 1.0;
    } else {
        value = -1.0;
    }
    phase += TWOPI * frequency / 44100.0;
    if (phase > TWOPI) {
        phase -= TWOPI;
    }
    sample = value;
}

void Oscillator::calculateNextInverseSawtoothSample()
{
    double value = 1.0 - 2.0 * phase / (TWOPI);
    phase += TWOPI * frequency / 44100.0;
    if (phase > TWOPI) {
        phase -= TWOPI;
    }
    sample = value;
}
