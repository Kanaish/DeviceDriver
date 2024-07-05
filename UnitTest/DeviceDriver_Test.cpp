#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

TEST(DeviceDriverTest, 읽기_5회_시도_테스트) {
	FlashMock mk;
	DeviceDriver dd(&mk);

	EXPECT_CALL(mk, read(0x00))
		.Times(5);

	dd.read(0x00);
}

TEST(DeviceDriverTest, 읽기_실패_테스트) {
	FlashMock mk;
	DeviceDriver dd(&mk);

	EXPECT_CALL(mk, read(0x00))
		.WillOnce(Return(0x10))
		.WillRepeatedly(Return(0x11));

	EXPECT_THROW(dd.read(0x00), DeviceDriverException);
}