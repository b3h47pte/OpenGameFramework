#include "gtest-common.h"
#include "WConfigFile.h"


class WConfigFileTest: public testing::Test {
	void SetUp() {
		section = "TestSection";
		section2 = "TestSection2";
		key1 = "TestKey1";
		key2 = "TestKey2";
	}
protected:
	WConfigFile file;
	std::string section;
	std::string section2;
	std::string key1;
	std::string key2;
};

TEST_F(WConfigFileTest, IntData) {
	int i = 5;
	file.SetIntData(section, key1, i);
	EXPECT_EQ(file.GetIntData(section, key1), i);
	EXPECT_EQ(file.GetIntData(section, key2), 0);
}

TEST_F(WConfigFileTest, FloatData) {
	float i = 5.f;
	file.SetFloatData(section, key1, i);
	EXPECT_EQ(file.GetFloatData(section, key1), i);
	EXPECT_EQ(file.GetFloatData(section, key2), 0.f);
}

TEST_F(WConfigFileTest, StrData) {
	std::string orig = "data";
	const char* i = orig.c_str();
	file.SetStrData(section, key1, i, strlen(i));
	const char* ret = file.GetStrData(section, key1);

	std::string t1(i);
	std::string t2(ret);
	EXPECT_EQ(t1, t2);
}
