//
// Created by steve on 10-8-2023.
//

#ifndef SVE_CHORUS_ARCTANGENTDISTORTION_HPP
#define SVE_CHORUS_ARCTANGENTDISTORTION_HPP

#include <cmath>

class ArctangentDistortion{
public:
    ArctangentDistortion(double sampleRate);
    ~ArctangentDistortion();
    float process(float input);
    void setPreGain(float preGain);
    void setDrive(float newDrive);
    void setSampleRate(double sampleRate);

private:
    float preGain{1.0f};
    float drive{0.5f};
    float previousDrive{0.5f};
    float alpha{0.3f};
    double sampleRate{44100};
};

#endif //SVE_CHORUS_ARCTANGENTDISTORTION_HPP
