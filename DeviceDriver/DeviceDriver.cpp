#include <stdexcept>

#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int tmp = 0, ret = 0;

    tmp = ret = (int)(m_hardware->read(address));

    for (int i = 0; i < 4; ++i) {
        ret = (int)(m_hardware->read(address));
        if (tmp == ret) continue;
        throw DeviceDriverException("ReadFailException");
    }

    return ret;
}

void DeviceDriver::write(long address, int data)
{
    int ret = (int)(m_hardware->read(address));

    if (ret != 0xFF) {
        throw DeviceDriverException("WriteFailException");
    }

    m_hardware->write(address, (unsigned char)data);
}