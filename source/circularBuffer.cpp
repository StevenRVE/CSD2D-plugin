//
// Created by steve on 3-8-2023.
//

#include "circularBuffer.hpp"

CircularBuffer::CircularBuffer(double sampleRate, float size) :
sampleRate(sampleRate),
bufferSize(sampleRate * size),
distanceReadWriteHead(1000)
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
    std::cout << "Incrementing..." << "\n";
    readHead++;
    wrapHead(readHead);
}

void CircularBuffer::incrementWriteHead()
{
    writeHead++;
    wrapHead(writeHead);
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

float CircularBuffer::readWithInterpolation() {

    float value = (read() * alpha) + (previousValue * alpha);

    return value;
}

void CircularBuffer::setSampleRate(double sampleRate)
{
    this->sampleRate = sampleRate;
    setDistanceReadWriteHead(distanceReadWriteHead);
}

void CircularBuffer::setBufferSize(float size)
{
    bufferSize = size;
    releaseBuffer();
    allocateBuffer();
}

void CircularBuffer::setDistanceReadWriteHead(float distanceInMilliseconds)
{
    if (distanceInMilliseconds >= bufferSize)
    {
        distanceReadWriteHead = bufferSize - 1;
    }

    distanceReadWriteHead = floor(distanceInMilliseconds * (sampleRate / 1000)); // convert milliseconds to samples
    std::cout << "distanceReadWriteHead: " << distanceReadWriteHead << "\n";
    readHead = writeHead - distanceReadWriteHead + bufferSize;
    wrapHead(readHead);
}

uint32_t CircularBuffer::getDistanceReadWriteHead() const
{
    return distanceReadWriteHead;
}

