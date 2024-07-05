#include <iostream>

#include "FlashMemoryDevice.h"
#include "DeviceDriver.h"

using namespace std;

class App
{
public:
	App(DeviceDriver* dd)
	{
		this->dev = dd;
	}
	void ReadAndPrint(int startAddr, int endAddr)
	{
		for (int addr = startAddr; addr < endAddr; ++addr) {
			cout << dev->read(addr) << endl;
		}
	}
	void WriteAll(int value)
	{
		for (int addr = 0; addr < 0x05; ++addr) {
			dev->write(addr, value);
		}
	}
private:
	DeviceDriver *dev;
};