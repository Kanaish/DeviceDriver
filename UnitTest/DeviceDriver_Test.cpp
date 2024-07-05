#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../DeviceDriver/DeviceDriver.cpp"

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

TEST(TestCaseName, TestName) {
	FlashMock mk;
	DeviceDriver dd(&mk);

	EXPECT_CALL(mk, read(0x00))
		.Times(5);

	dd.read(0x00);
}