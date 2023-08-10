//
// Created by steve on 10-8-2023.
//

#include "arctangentDistortion.hpp"

ArctangentDistortion::ArctangentDistortion(double sampleRate) {

}

ArctangentDistortion::~ArctangentDistortion() {

}

float ArctangentDistortion::process(float input) {
    float y = 0.5f * M_PI * atanf(drive * input * preGain);
    return y;

}

void ArctangentDistortion::setPreGain(float preGain) {
    this->preGain = preGain;
}

void ArctangentDistortion::setDrive(float drive) {
    this->drive = drive;
}

void ArctangentDistortion::setMix(float mix) {
    this->mix = mix;
}

void ArctangentDistortion::setSampleRate(double sampleRate) {
    this->sampleRate = sampleRate;
}

