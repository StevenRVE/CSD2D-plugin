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
    void setGain(float gain);
    void setThreshold(float threshold);
    void setMix(float mix);
    void setSampleRate(double sampleRate);

private:
    float gain{1.0f};
    float threshold{0.5f};
    float mix{0.5f};
    double sampleRate{44100};
};


#endif //SVE_CHORUS_ARCTANGENTDISTORTION_HPP
