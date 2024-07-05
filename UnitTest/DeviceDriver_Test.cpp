#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/App.cpp"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

TEST(DeviceDriverTest, �б�_5ȸ_�õ�_�׽�Ʈ) {
	FlashMock mk;
	DeviceDriver dd{ &mk };

	EXPECT_CALL(mk, read)
		.Times(5);

	dd.read(0x00);
}

TEST(DeviceDriverTest, �б�_����_�׽�Ʈ) {
	FlashMock mk;
	DeviceDriver dd{ &mk };

	EXPECT_CALL(mk, read)
		.WillOnce(Return(0x10))
		.WillRepeatedly(Return(0x11));

	EXPECT_THROW(dd.read(0x00), std::exception);
}

TEST(DeviceDriverTest, ����_�׽�Ʈ) {
	FlashMock mk;
	DeviceDriver dd{ &mk };

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mk, write(0x00, 0x11));

	EXPECT_NO_THROW(dd.write(0x00, 0x11));
}

TEST(DeviceDriverTest, ����_����_�׽�Ʈ) {
	FlashMock mk;
	DeviceDriver dd{ &mk };

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0x22));

	EXPECT_THROW(dd.write(0x00, 0x11), std::exception);
}

TEST(DeviceDriverTest, App_�б�_�׽�Ʈ) {
	FlashMock mk;
	DeviceDriver dd{ &mk };
	App* app = new App(&dd);

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0x22));

	EXPECT_NO_THROW(app->ReadAndPrint(0x0, 0x5));
}

TEST(DeviceDriverTest, App_����_�׽�Ʈ) {
	FlashMock mk;
	DeviceDriver dd{ &mk };
	App* app = new App(&dd);

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0xFF));

	EXPECT_NO_THROW(app->WriteAll(0x88));
}