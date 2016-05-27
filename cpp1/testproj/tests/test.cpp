#include <addition.h>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(add, twoValues)
{
	int x = 4;
	int y = 5;
	EXPECT_EQ(9, add(x,y));
}

TEST(add, twoNegValues)
{
	int x = -2;
	int y = -4;
	EXPECT_EQ(-6, add(x,y));
}
