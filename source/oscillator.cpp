//
// Created by steve on 4-8-2023.
//

#include "oscillator.hpp"

Oscillator::Oscillator(double frequency, Waveform waveform) :
frequency(frequency),
waveform(waveform)
{

}

Oscillator::~Oscillator()
{

}

void Oscillator::setPhase(double phase)
{
    this->phase = phase;
}

void Oscillator::setFrequency(double frequency)
{
    this->frequency = frequency;
}

void Oscillator::setWaveform(Waveform waveform)
{
    this->waveform = waveform;
}

void Oscillator::setSampleRate(double sampleRate)
{
    this->sampleRate = sampleRate;
}

void Oscillator::setAmplitude(double amplitude)
{
    this->amplitude = amplitude;
}

double Oscillator::getNextSample()
{
    switch (waveform) {
        case SINE:
            return generateSine();
        case TRIANGLE:
            return generateTriangle();
        case SAWTOOTH:
            return generateSawtooth();
        case SQUARE:
            return generateSquare();
        case INVERSE_SAWTOOTH:
            return generateInverseSawtooth();
        default:
            return 0.0;
    }
}

double Oscillator::generateSine()
{
    double value = sin(phase);
    phase += 2.0 * M_PI * frequency / 44100.0;
    if (phase > 2.0 * M_PI) {
        phase -= 2.0 * M_PI;
    }
    return value;
}

double Oscillator::generateTriangle()
{
    double value = 0.0;
    if (phase < M_PI) {
        value = -1.0 + 2.0 * phase / M_PI;
    } else {
        value = 3.0 - 2.0 * phase / M_PI;
    }
    phase += 2.0 * M_PI * frequency / 44100.0;
    if (phase > 2.0 * M_PI) {
        phase -= 2.0 * M_PI;
    }
    return value;
}

double Oscillator::generateSawtooth()
{
    double value = -1.0 + 2.0 * phase / (2.0 * M_PI);
    phase += 2.0 * M_PI * frequency / 44100.0;
    if (phase > 2.0 * M_PI) {
        phase -= 2.0 * M_PI;
    }
    return value;
}

double Oscillator::generateSquare()
{
    double value = 0.0;
    if (phase < M_PI) {
        value = 1.0;
    } else {
        value = -1.0;
    }
    phase += 2.0 * M_PI * frequency / 44100.0;
    if (phase > 2.0 * M_PI) {
        phase -= 2.0 * M_PI;
    }
    return value;
}

double Oscillator::generateInverseSawtooth()
{
    double value = 1.0 - 2.0 * phase / (2.0 * M_PI);
    phase += 2.0 * M_PI * frequency / 44100.0;
    if (phase > 2.0 * M_PI) {
        phase -= 2.0 * M_PI;
    }
    return value;
}
