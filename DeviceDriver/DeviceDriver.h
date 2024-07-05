#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriverException : public std::exception
{
public:
    explicit DeviceDriverException(char const* _Message) : exception(_Message)
    {
    }
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice *hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice *m_hardware;
};