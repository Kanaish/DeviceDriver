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
	DeviceDriver dd{ &mk };

	EXPECT_CALL(mk, read)
		.Times(5);

	dd.read(0x00);
}

TEST(DeviceDriverTest, 읽기_실패_테스트) {
	FlashMock mk;
	DeviceDriver dd{ &mk };

	EXPECT_CALL(mk, read)
		.WillOnce(Return(0x10))
		.WillRepeatedly(Return(0x11));

	EXPECT_THROW(dd.read(0x00), std::exception);
}

TEST(DeviceDriverTest, 쓰기_테스트) {
	FlashMock mk;
	DeviceDriver dd{ &mk };

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mk, write(0x00, 0x11));

	EXPECT_NO_THROW(dd.write(0x00, 0x11));
}

TEST(DeviceDriverTest, 쓰기_실패_테스트) {
	FlashMock mk;
	DeviceDriver dd{ &mk };

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0x22));

	EXPECT_THROW(dd.write(0x00, 0x11), std::exception);
}