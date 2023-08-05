//
// Created by steve on 3-8-2023.
//

#ifndef SVE_CHORUS_CIRCULARBUFFER_H
#define SVE_CHORUS_CIRCULARBUFFER_H

#include <cstdint>
#include <iostream>

class CircularBuffer {
public:
    // constructor and destructor
    CircularBuffer(double sampleRate, uint32_t size);
    ~CircularBuffer();

    // methods
    void allocateBuffer();

    void releaseBuffer();

    void incrementReadHead();

    void incrementWriteHead();

    void wrapHead(uint32_t& head) const;

    void tick();

    void write(float value);

    float read();

    float readWithInterpolation();

    // setters and getters

    void setSampleRate(double sampleRate);

    void setBufferSize(uint32_t size);

    void setDistanceReadWriteHead(uint32_t distanceInMilliseconds);

    uint32_t getDistanceReadWriteHead() const;

private:
    // variables
    double sampleRate = 44100;
    float* buffer = nullptr;
    uint32_t bufferSize;
    uint32_t readHead = 0;
    uint32_t writeHead = 0;
    uint32_t distanceReadWriteHead = 0;
    float previousValue = 0.0f;
    float aplha = 0.5f;
};


#endif //SVE_CHORUS_CIRCULARBUFFER_H
