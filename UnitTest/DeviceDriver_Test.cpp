#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

TEST(DeviceDriverTest, �б�_5ȸ_�õ�_�׽�Ʈ) {
	FlashMock mk;
	DeviceDriver dd(&mk);

	EXPECT_CALL(mk, read(0x00))
		.Times(5);

	dd.read(0x00);
}

TEST(DeviceDriverTest, �б�_����_�׽�Ʈ) {
	FlashMock mk;
	DeviceDriver dd(&mk);

	EXPECT_CALL(mk, read(0x00))
		.WillOnce(Return(0x10))
		.WillRepeatedly(Return(0x11));

	EXPECT_THROW(dd.read(0x00), DeviceDriverException);
}