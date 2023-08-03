//
// Created by steve on 3-8-2023.
//

#include "circularBuffer.hpp"

CircularBuffer::CircularBuffer(double sampleRate, uint32_t size)
sampleRate(sampleRate),
bufferSize(sampleRate * size)
{
    std::cout << "CircularBuffer constructor" << "\n";
    allocateBuffer();
}

CircularBuffer::~CircularBuffer()
{
    std::cout << "CircularBuffer destructor" << "\n";
    releaseBuffer();
}

void CircularBuffer::allocateBuffer()
{
    std::cout << "Allocating buffer..." << "\n";
    buffer = new float[bufferSize]();
    std::fill_n(buffer, bufferSize, 0.0f);
}

void CircularBuffer::releaseBuffer()
{
    std::cout << "Releasing buffer...\n";
    delete[] buffer;
}

void CircularBuffer::incrementReadHead()
{
    writeHead++;
    wrap(writeHead);
}

void CircularBuffer::incrementWriteHead()
{
    readHead++;
    wrap(writeHead);
}

void CircularBuffer::wrapHead(uint32_t& head) const
{
    if(head >= bufferSize)
    {
        head -= bufferSize;
    }
}

void CircularBuffer::tick()
{
    incrementWriteHead();
    incrementReadHead();
}

void CircularBuffer::write(float value)
{
    buffer[writeHead] = value;
}

float CircularBuffer::read()
{
    return buffer[readHead];
}

void CircularBuffer::setBufferSize(uint32_t size)
{
    bufferSize = size;
    releaseBuffer();
    allocateBuffer();
}

void CircularBuffer::setDistanceReadWriteHead(uint32_t distanceInSamples
{
    if (distanceInSamples >= bufferSize)
    {
        distanceReadWriteHead = bufferSize - 1;
    }
    else
    {
        distanceReadWriteHead = distanceInSamples;
    }
}

uint32_t CircularBuffer::getDistanceReadWriteHead() const
{
    return distanceReadWriteHead;
}