#include "ray.h"
#include "comparinator.h"
#include "tuple.h"
#include "pch.h"

class RayTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(RayTest, CanaryTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
};

TEST_F(RayTest, RayCtor) {
	Point p = Point(1, 2, 3);
	Vector d = Vector(4, 5, 6);
	Ray r = Ray(p, d);
	EXPECT_TRUE(ce.checkTuple(r.mbrOrigin,p));
	EXPECT_TRUE(ce.checkTuple(r.mbrDirection,d));
};

TEST_F(RayTest, RayPositionAfterTime) {
	Point p = Point(2, 3, 4);
	Vector d = Vector(1, 0, 0);
	Ray r = Ray(p, d);
	Point pos0 = r.getPosition(0);
	Point expos0 = Point(2, 3, 4);
	Point pos1 = r.getPosition(1);
	Point expos1 = Point(3, 3, 4);
	Point posn1 = r.getPosition(-1);
	Point exposn1 = Point(1, 3, 4);
	Point pos2p5 = r.getPosition(2.5);
	Point expos2p5 = Point(4.5, 3, 4);
	EXPECT_TRUE(ce.checkTuple(pos0,expos0));
	EXPECT_TRUE(ce.checkTuple(pos1, expos1));
	EXPECT_TRUE(ce.checkTuple(posn1, exposn1));
	EXPECT_TRUE(ce.checkTuple(pos2p5, expos2p5));
};

TEST_F(RayTest, RayTranslation) {
	Point p = Point(1, 2, 3);
	Vector d = Vector(0, 1, 0);
	Ray r = Ray(p, d);
	TranslationMatrix m = TranslationMatrix(3, 4, 5);
	Point expectedP = Point(4, 6, 8);
	Vector expectedV = Vector(0,1,0);
	Ray t = r.transform(m);
	EXPECT_TRUE(ce.checkTuple(t.mbrOrigin, expectedP));
	EXPECT_TRUE(ce.checkTuple(t.mbrDirection, expectedV));
	EXPECT_TRUE(ce.checkTuple(r.mbrOrigin, p));
	EXPECT_TRUE(ce.checkTuple(r.mbrDirection, d));
};

TEST_F(RayTest, RayScaling) {
	Point p = Point(1, 2, 3);
	Vector d = Vector(0, 1, 0);
	Ray r = Ray(p, d);
	ScalingMatrix m = ScalingMatrix(2, 3, 4);
	Point expectedP = Point(2, 6, 12);
	Vector expectedV = Vector(0,3,0);
	Ray t = r.transform(m);
	EXPECT_TRUE(ce.checkTuple(t.mbrOrigin, expectedP));
	EXPECT_TRUE(ce.checkTuple(t.mbrDirection, expectedV));
	EXPECT_TRUE(ce.checkTuple(r.mbrOrigin, p));
	EXPECT_TRUE(ce.checkTuple(r.mbrDirection, d));
};