#include "comparinator.h"
#include "tuple.h"
#include "pch.h"

class ComparinatorTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(ComparinatorTest, Canary) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(ComparinatorTest, TestFloatingPointEqual) {
	double z = 0;
	double zz = 0.0000000;
	double o = 0.0001;
	double t = 0.0002;
	EXPECT_TRUE(ce.checkFloat(z,zz));
	EXPECT_TRUE(ce.checkFloat(o,o));
	EXPECT_FALSE(ce.checkFloat(t,o));
}

TEST_F(ComparinatorTest, TestTuplesEqual) {
	EXPECT_TRUE(ce.checkTuple(Tuple(4.3, -4.2, 3.1, 1.0), Tuple(4.3, -4.2, 3.1, 1.0)));
	EXPECT_FALSE(ce.checkTuple(Tuple(4.3, -4.2, 3.1, 1.0), Tuple(4.3, -4.2, 3.0, 1.0)));
}