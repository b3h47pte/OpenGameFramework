#include "gtest-common.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include "WFile.h"


class WFileTest: public testing::Test {
	void SetUp() {
		std::ofstream newFile;
		newFile.open("test.txt");
		newFile << "Hello\nThere\nHowdy\nNeehao";
		newFile.close();

		// text.txt contents:
		//	Hello
		//	There
		//	Howdy
		//	Neehao
		std::string str = "test.txt";
		file = new WFile(str);
	}

	void TearDown() {
		std::string filename = "test.txt";
		remove(filename.c_str());
		delete file;
	}
protected:
	WFile* file;
};

TEST_F(WFileTest, ReadAllTextData) {
	std::vector<std::string> lineData;
	file->ReadAllTextData(lineData);
	EXPECT_EQ(lineData.size(), 4);
	EXPECT_EQ(lineData[0], "Hello");
	EXPECT_EQ(lineData[1], "There");
	EXPECT_EQ(lineData[2], "Howdy");
	EXPECT_EQ(lineData[3], "Neehao");
}

TEST_F(WFileTest, ReadAllBinaryDataNull) {
	int len = 0;
	char* data = file->ReadAllBinaryDataNull(len);
	EXPECT_EQ(data[len], '\0');
}
