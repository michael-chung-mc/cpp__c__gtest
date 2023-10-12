#include "color.h"
#include "comparinator.h"
#include "pch.h"

class ColorTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(ColorTest, CanaryTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
};

TEST_F(ColorTest, InitColor) {
	//Scenario: Colors are(red, green, blue) tuples
	//Given c ← color(-0.5, 0.4, 1.7)
	//Then c.red = -0.5
	//And c.green = 0.4
	//And c.blue = 1.7
	Color c = Color(-0.5, 0.4, 1.7);
	EXPECT_EQ(c.mbrRed, -.5);
	EXPECT_EQ(c.mbrGreen, .4);
	EXPECT_EQ(c.mbrBlue, 1.7);
};

TEST_F(ColorTest, AddColors) {
	//Scenario: Adding colors
	//Given c1 ← color(0.9, 0.6, 0.75)
	//And c2 ← color(0.7, 0.1, 0.25)
	//Then c1 + c2 = color(1.6, 0.7, 1.0)
	Color c1 = Color(0.9, 0.6, 0.75);
	Color c2 = Color(0.7, 0.1, 0.25);
	Color c12 = c1 + c2;
	Color c3 = Color(1.6, 0.7, 1.0);
	EXPECT_TRUE(c3.checkEqual(c12));
};


TEST_F(ColorTest, SubtractColors) {
	//Scenario : Subtracting colors
	//Given c1 ← color(0.9, 0.6, 0.75)
	//And c2 ← color(0.7, 0.1, 0.25)
	//Then c1 - c2 = color(0.2, 0.5, 0.5)
	Color c1 = Color(0.9, 0.6, 0.75);
	Color c2 = Color(0.7, 0.1, 0.25);
	Color c12 = c1 - c2;
	Color c3 = Color(0.2, 0.5, 0.5);
	EXPECT_TRUE(c3.checkEqual(c12));
};


TEST_F(ColorTest, MultiplyColor) {
	//Scenario : Multiplying a color by a scalar
	//Given c ← color(0.2, 0.3, 0.4)
	//Then c * 2 = color(0.4, 0.6, 0.8)
	Color c1 = Color(0.2, 0.3, 0.4);
	Color c2 = Color(0.4, 0.6, 0.8);
	Color c3 = c1 * 2;
	EXPECT_TRUE(c3.checkEqual(c2));
};


TEST_F(ColorTest, HadamardProduct) {
	//Scenario: Multiplying colors
	//Given c1 ← color(1, 0.2, 0.4)
	//And c2 ← color(0.9, 1, 0.1)
	//Then c1* c2 = color(0.9, 0.2, 0.04)
	Color c1 = Color(1, 0.2, 0.4);
	Color c2 = Color(0.9, 1, 0.1);
	Color c12 = c1 * c2;
	Color c3 = Color(0.9, 0.2, 0.04);
	EXPECT_TRUE(c3.checkEqual(c12));
};