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

}

void CircularBuffer::releaseBuffer()
{

}

void CircularBuffer::incrementReadHead()
{

}

void CircularBuffer::incrementWriteHead()
{

}

void CircularBuffer::wrapHead(uint32_t& head) const
{

}

void CircularBuffer::tick()
{

}

void CircularBuffer::write(float value)
{
    writeHead++;
    if(writeHead >= bufferSize)
    {
        writeHead = 0;
    }
}

float CircularBuffer::read()
{
    readHead++;
    if(readHead >= bufferSize)
    {
        readHead = 0;
    }
}

void CircularBuffer::setBufferSize(uint32_t size)
{

}

void CircularBuffer::setDistanceReadWriteHead(uint32_t distance)
{

}

uint32_t CircularBuffer::getDistanceReadWriteHead() const
{

}