#include "light.h"
#include "tuple.h"
#include "color.h"
#include "comparinator.h"
#include "pch.h"

class LightTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(LightTest, CanaryTest)
{
    EXPECT_EQ(1,1);
}

TEST_F(LightTest, PointSourceCtor)
{
    Color c = Color(1,1,1);
    Point p = Point(0,0,0);
    PointSource ps = PointSource(p,c);
    EXPECT_TRUE(ce.checkTuple(c,ps.mbrIntensity));
    EXPECT_TRUE(ce.checkTuple(p,ps.mbrPosition));
}