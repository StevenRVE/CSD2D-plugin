//
// Created by steve on 4-8-2023.
//

#ifndef SVE_CHORUS_OSCILLATOR_HPP
#define SVE_CHORUS_OSCILLATOR_HPP

#include <cmath>

#define TWOPI 6.283185307179586476925286766559f

// Might do these later
// TODO: change implementation to use a lookup table, change implementation to use tick() method
// TODO: add more waveforms

class Oscillator {
public:
    enum Waveform{
        SINE,
        TRIANGLE,
        SQUARE,
        SAWTOOTH,
        INVERSE_SAWTOOTH
    };

    // constructor and destructor

    Oscillator(double sampleRate, float frequency, float baseFrequency, float phase, Waveform waveform = SINE);
    ~Oscillator();

    // setters and getters

    void setSampleRate(double sampleRate);
    void setFrequency(float frequency);
    void setWaveform(Waveform waveform);
    void setAmplitude(float value);

    // methods

    void tick();
    float getSample();

private:
    double sampleRate = 44100.0;
    float frequency{1.0f};
    float baseFrequency{1.0f};
    Waveform waveform{SINE};
    float amplitude{1.0f};
    float sample{0.0f};
    float phase{0.0f};

    void calculateNextSineSample();

};

#endif //SVE_CHORUS_OSCILLATOR_HPP
