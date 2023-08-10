//
// Created by steve on 10-8-2023.
//

#include "arctangentDistortion.hpp"

ArctangentDistortion::ArctangentDistortion(double sampleRate) {

}

ArctangentDistortion::~ArctangentDistortion() {

}

float ArctangentDistortion::process(float input) {
//    float x = input;
//    float y = x * gain;
//    float absY = fabs(y);
//    float signY = y / absY;
//    float outY = (absY < threshold) ? y : (signY * ((absY - threshold) / (1.0f - threshold)));
//    float output = (mix * outY) + ((1.0f - mix) * x);
//    return output;

    float y = 0.5f * M_PI * atanf(threshold * input * gain);
    return y;

}

void ArctangentDistortion::setGain(float gain) {
    this->gain = gain;
}

void ArctangentDistortion::setThreshold(float threshold) {
    this->threshold = threshold;
}

void ArctangentDistortion::setMix(float mix) {
    this->mix = mix;
}

void ArctangentDistortion::setSampleRate(double sampleRate) {
    this->sampleRate = sampleRate;
}

