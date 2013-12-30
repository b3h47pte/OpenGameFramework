#include "gtest-common.h"
#include "WorldObject.h"

class WorldObjectTest: public testing::Test {
	void SetUp() {
	}

	void TearDown() {
	}

protected:
	WorldObject obj;
};

// Assumptions about World axis.
TEST_F(WorldObjectTest, WorldAxis) {
	EXPECT_EQ(obj.GetWorldUp(), glm::vec4(0.f, 1.f, 0.f, 0.f));
	EXPECT_EQ(obj.GetWorldForward(), glm::vec4(0.f, 0.f, -1.f, 0.f));
	EXPECT_EQ(obj.GetWorldRight(), glm::vec4(1.f, 0.f, 0.f, 0.f));
}
