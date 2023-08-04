//
// Created by steve on 4-8-2023.
//

#ifndef SVE_CHORUS_OSCILLATOR_HPP
#define SVE_CHORUS_OSCILLATOR_HPP

#include <cmath>

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

    Oscillator(double sampleRate, double frequency = 1.0, Waveform waveform = SINE);
    ~Oscillator();

    // setters and getters

    void setSampleRate(double sampleRate);
    void setFrequency(double frequency);
    void setPhase(double phase);
    void setWaveform(Waveform waveform);
    void setAmplitude(double amplitude);

    double getNextSample();

private:
    double sampleRate{44100.0};
    double frequency{500.0};
    double phase{0.0};
    Waveform waveform{SINE};
    double amplitude{1.0};

    double generateSine();
    double generateTriangle();
    double generateSawtooth();
    double generateSquare();
    double generateInverseSawtooth();
};

#endif //SVE_CHORUS_OSCILLATOR_HPP
