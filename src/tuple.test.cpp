#include "tuple.h"
#include "comparinator.h"
#include "pch.h"

class TupleTest : public ::testing::Test {
protected:
	Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override { 
		ce = Comparinator();
	}
	//void TearDown() override { }
};

TEST_F(TupleTest, CanaryTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
};

TEST_F(TupleTest, TupleWOneIsPoint)
{
	Tuple a = Tuple(4.3, -4.2, 3.1, 1.0);
	EXPECT_EQ(a.mbrX, 4.3);
	EXPECT_EQ(a.mbrY, -4.2);
	EXPECT_EQ(a.mbrZ, 3.1);
	EXPECT_EQ(a.mbrW, 1.0);
	Point ap = Point(4.3, -4.2, 3.1);
	EXPECT_EQ(a.mbrX, ap.mbrX);
	EXPECT_EQ(a.mbrY, ap.mbrY);
	EXPECT_EQ(a.mbrZ, ap.mbrZ);
	EXPECT_EQ(a.mbrW, ap.mbrW);
	Vector av = Vector(4.3, -4.2, 3.1);
	EXPECT_EQ(a.mbrX, av.mbrX);
	EXPECT_EQ(a.mbrY, av.mbrY);
	EXPECT_EQ(a.mbrZ, av.mbrZ);
	EXPECT_NE(a.mbrW, av.mbrW);
};

TEST_F(TupleTest, TupleWZeroIsVector)
{
	Tuple a = Tuple(4.3, -4.2, 3.1, 0.0);
	EXPECT_EQ(a.mbrX, 4.3);
	EXPECT_EQ(a.mbrY, -4.2);
	EXPECT_EQ(a.mbrZ, 3.1);
	EXPECT_EQ(a.mbrW, 0.0);
	Point ap = Point(4.3, -4.2, 3.1);
	EXPECT_EQ(a.mbrX, ap.mbrX);
	EXPECT_EQ(a.mbrY, ap.mbrY);
	EXPECT_EQ(a.mbrZ, ap.mbrZ);
	EXPECT_NE(a.mbrW, ap.mbrW);
	Vector av = Vector(4.3, -4.2, 3.1);
	EXPECT_EQ(a.mbrX, av.mbrX);
	EXPECT_EQ(a.mbrY, av.mbrY);
	EXPECT_EQ(a.mbrZ, av.mbrZ);
	EXPECT_EQ(a.mbrW, av.mbrW);
};

TEST_F(TupleTest, TuplePlusTupleEqualsTuple)
{
	//Scenario: Adding two Tuple
	//Given a1 ← tuple(3, -2, 5, 1)
	//And a2 ← tuple(-2, 3, 1, 0)
	//Then a1 + a2 = tuple(1, 1, 6, 1)
	Tuple a = Tuple(3, -2, 5, 1);
	Tuple b = Tuple(-2, 3, 1, 0);
	Tuple c = Tuple(1, 1, 6, 1);
	Tuple result = a + b;
	EXPECT_TRUE(ce.checkTuple(c, result));
	a.add(b);
	EXPECT_TRUE(ce.checkTuple(a,c));
};

TEST_F(TupleTest, TupleMinusTupleEqualsTuple)
{
	//Scenario: Subtracting two Tuple
	//Given p1 ← tuple(3, 2, 1, 1)
	//And p2 ← tuple(5, 6, 7, 1)
	//Then p1 - p2 = tuple(-2, -4, -6, 0)
	Tuple a = Tuple(3, 2, 1, 1);
	Tuple b = Tuple(5, 6, 7, 1);
	Tuple c = Tuple(-2, -4, -6, 0);
	Tuple result = a.subtract(b);
	EXPECT_TRUE(ce.checkTuple(c, result));
};

TEST_F(TupleTest, PointMinusVectorEqualsPoint)
{
	//Scenario: Subtracting two points
	//Given p1 ← tuple(3, 2, 1, 1)
	//And p2 ← tuple(5, 6, 7, 1)
	//Then p1 - p2 = tuple(-2, -4, -6, 0)
	Point a = Point(3, 2, 1);
	Vector b = Vector(5, 6, 7);
	Point c = Point(-2, -4, -6);
	Point result = a.subtract(b);
	EXPECT_TRUE(ce.checkTuple(c, result));
};

TEST_F(TupleTest, VectorMinusVectorEqualsVector)
{
	//Scenario: Subtracting two vectors
	//Given v1 ← vector(3, 2, 1)
	//And v2 ← vector(5, 6, 7)
	//Then v1 - v2 = vector(-2, -4, -6)
	Vector a = Vector(3, 2, 1);
	Vector b = Vector(5, 6, 7);
	Vector c = Vector(-2, -4, -6);
	Vector result = a.subtract(b);
	EXPECT_TRUE(ce.checkTuple(c, result));
};

TEST_F(TupleTest, ZeroMinusVectorEqualsNegatedVector)
{
	//Scenario: Subtracting a vector from the zero vector
	//Given zero ← vector(0, 0, 0)
	//And v ← vector(1, -2, 3)
	//Then zero - v = vector(-1, 2, -3)
	Vector a = Vector(0, 0, 0);
	Vector b = Vector(1, -2, 3);
	Vector c = Vector(-1, 2, -3);
	Vector result = a.subtract(b);
	EXPECT_TRUE(ce.checkTuple(c, result));
};

TEST_F(TupleTest, NegateTupleMethod)
{
	//Scenario: Negating a tuple
	//Given a ← tuple(1, -2, 3, -4)
	//Then - a = tuple(-1, 2, -3, 4)
	Tuple a = Tuple(1, -2, 3, -4);
	Tuple an = a.negate();
	Tuple c = Tuple(-1, 2, -3, 4);
	EXPECT_TRUE(ce.checkTuple(an, c));
}

TEST_F(TupleTest, NegateZeroTuple)
{
	Tuple a = Tuple(0,0,0,0);
	Tuple an = -a;
	Tuple c = Tuple(0,0,0,0);
	EXPECT_TRUE(ce.checkTuple(an, c));
}

TEST_F(TupleTest, NegateTupleOperator)
{
	//Scenario: Negating a tuple
	//Given a ← tuple(1, -2, 3, -4)
	//Then - a = tuple(-1, 2, -3, 4)
	Tuple a = Tuple(1, -2, 3, -4);
	Tuple an = -a;
	Tuple c = Tuple(-1, 2, -3, 4);
	EXPECT_TRUE(ce.checkTuple(an, c));
}

TEST_F(TupleTest, NegateVectorOperator)
{
	Vector a = Vector(1, -2, 3);
	Vector an = -a;
	Vector c = Vector(-1, 2, -3);
	EXPECT_TRUE(ce.checkTuple(an, c));
}

TEST_F(TupleTest, ScaleTuple)
{
	// Scenario: Multiplying a tuple by a scalar
	// Given a ← tuple(1, -2, 3, -4)
	// Then a * 3.5 = tuple(3.5, -7, 10.5, -14)
	Tuple a = Tuple (1, -2, 3, -4);
	Tuple b = a * 3.5;
	Tuple c = Tuple(3.5, -7, 10.5, -14);
	EXPECT_TRUE(ce.checkTuple(b, c));
	EXPECT_TRUE(ce.checkTuple(b, c));
}

TEST_F(TupleTest, ShrinkTuple)
{
	// Scenario: Multiplying a tuple by a fraction
	// Given a ← tuple(1, -2, 3, -4)
	// Then a * 0.5 = tuple(0.5, -1, 1.5, -2)
	Tuple a = Tuple(1, -2, 3, -4);
	Tuple b = a * 0.5;
	Tuple c = Tuple(0.5, -1, 1.5, -2);
	EXPECT_TRUE(ce.checkTuple(b, c));
}

TEST_F(TupleTest, DivideTuple)
{
	// Scenario: Dividing a tuple by a scalar
	// Given a ← tuple(1, -2, 3, -4)
	// Then a / 2 = tuple(0.5, -1, 1.5, -2)
	Tuple a = Tuple(1, -2, 3, -4);
	Tuple b = a / 2;
	Tuple c = Tuple(0.5, -1, 1.5, -2);
	EXPECT_TRUE(ce.checkTuple(b, c));
}

TEST_F(TupleTest, TupleMagnitudeUnit)
{
	//Scenario: Computing the magnitude of vector(1, 0, 0)
	//Given v ← vector(1, 0, 0)
	//Then magnitude(v) = 1
	//Scenario : Computing the magnitude of vector(0, 1, 0)
	//Given v ← vector(0, 1, 0)
	//Then magnitude(v) = 1
	//Scenario : Computing the magnitude of vector(0, 0, 1)
	//Given v ← vector(0, 0, 1)
	//Then magnitude(v) = 1
	Vector a = Vector(1, 0, 0);
	EXPECT_EQ(a.magnitude(), 1);
	Vector b = Vector(0, 1, 0);
	EXPECT_EQ(b.magnitude(), 1);
	Vector c = Vector(0, 0, 1);
	EXPECT_EQ(c.magnitude(), 1);
}

TEST_F(TupleTest, TupleMagnitude)
{
	//Scenario : Computing the magnitude of vector(1, 2, 3)
	//Given v ← vector(1, 2, 3)
	//Then magnitude(v) = √14
	Vector a = Vector(1, 2, 3);
	float mag = sqrt(14);
	EXPECT_TRUE(ce.checkFloat(a.magnitude(), mag));
	//Scenario : Computing the magnitude of vector(-1, -2, -3)
	//Given v ← vector(-1, -2, -3)
	//Then magnitude(v) = √14
	Vector b = Vector(-1, -2, -3);
	EXPECT_TRUE(ce.checkFloat(b.magnitude(), mag));
}

TEST_F(TupleTest, TupleNormalized)
{
	//Scenario: Normalizing vector(4, 0, 0) gives(1, 0, 0)
	//Given v ← vector(4, 0, 0)
	//Then normalize(v) = vector(1, 0, 0)
	Vector unit = Vector(1, 0, 0);
	Vector a = Vector(4, 0, 0);
	Vector norm = a.normalize();
	EXPECT_TRUE(ce.checkTuple(unit, norm));
	//Scenario : Normalizing vector(1, 2, 3)
	//Given v ← vector(1, 2, 3)
	//Then normalize(v) = approximately vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14))
	unit = Vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14));
	a = Vector(1, 2, 3);
	norm = a.normalize();
	EXPECT_TRUE(ce.checkTuple(unit, norm));
	//Scenario: The magnitude of a normalized vector
	//Given v ← vector(1, 2, 3)
	//When norm ← normalize(v)
	//Then magnitude(norm) = 1
	int magnitude = norm.magnitude();
	EXPECT_EQ(magnitude, 1);
}

TEST_F(TupleTest, TupleDotProduct)
{
	//Scenario: The dot product of two tuples
	//Given a ← vector(1, 2, 3)
	//And b ← vector(2, 3, 4)
	//Then dot(a, b) = 20
	Vector a = Vector(1, 2, 3);
	Vector b = Vector(2, 3, 4);
	int dot = a.dot(b);
	EXPECT_EQ(dot, 20);
}

TEST_F(TupleTest, TupleCrossProduct)
{
	//Scenario: The cross product of two vectors
	//Given a ← vector(1, 2, 3)
	//And b ← vector(2, 3, 4)
	//Then cross(a, b) = vector(-1, 2, -1)
	//And cross(b, a) = vector(1, -2, 1)
	Vector a = Vector(1, 2, 3);
	Vector b = Vector(2, 3, 4);
	Vector ab = a.cross(b);
	Vector c = Vector(-1, 2, -1);
	EXPECT_TRUE(ce.checkTuple(ab, c));
	Vector ba = b.cross(a);
	c = Vector(1, -2, 1);
	EXPECT_TRUE(ce.checkTuple(ba, c));
}

TEST_F(TupleTest, TupleReflect)
{
	Vector v = Vector(1, -1, 0);
	Vector n = Vector(0, 1, 0);
	Vector r = v.reflect(n);
	Vector expectedR = Vector(1,1,0);
	EXPECT_TRUE(ce.checkTuple(r, expectedR));
}

TEST_F(TupleTest, TupleReflectAngled)
{
	Vector v = Vector(0, -1, 0);
	Vector n = Vector(sqrt(2)/2, sqrt(2)/2, 0);
	Vector r = v.reflect(n);
	Vector expectedR = Vector(1,0,0);
	EXPECT_TRUE(ce.checkTuple(r, expectedR));
}