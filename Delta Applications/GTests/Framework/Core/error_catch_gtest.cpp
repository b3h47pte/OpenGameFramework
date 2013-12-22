#include "gtest-common.h"
#include "ErrorCatch.h"

class BareErrorCatch: public ErrorCatch {
	virtual void DumpError(int i) const {}
};

class ErrorCatchTest: public testing::Test {
protected:
	BareErrorCatch err;
};

TEST_F(ErrorCatchTest, TestGetSetError) {
	int code = -1;
	EXPECT_FALSE(err.GetError(code));
	err.SetError(3);
	EXPECT_TRUE(err.GetError(code));
	EXPECT_EQ(code, 3);
}


