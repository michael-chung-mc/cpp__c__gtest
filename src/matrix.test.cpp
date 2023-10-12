#include "matrix.h"
#include "comparinator.h"
#include "tuple.h"
#include "pch.h"

class MatrixTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

class TransformationTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(MatrixTest, CanaryTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
};

TEST_F(MatrixTest, Matrix4x4ctor)
{
	double a = 1;
	double b = 2;
	double c = 3;
	double d = 4;
	double e = 5.5;
	double f = 6.5;
	double g = 7.5;
	double h = 8.5;
	double i = 9;
	double j = 10;
	double k = 11;
	double l = 12;
	double m = 13.5;
	double n = 14.5;
	double o = 15.5;
	double p = 16.5;
	Matrix mx = Matrix(4,4);
	mx.setRC(0, 0, 1);
	mx.setRC(0, 1, 2);
	mx.setRC(0, 2, 3);
	mx.setRC(0, 3, 4);
	mx.setRC(1, 0, 5.5);
	mx.setRC(1, 1, 6.5);
	mx.setRC(1, 2, 7.5);
	mx.setRC(1, 3, 8.5);
	mx.setRC(2, 0, 9);
	mx.setRC(2, 1, 10);
	mx.setRC(2, 2, 11);
	mx.setRC(2, 3, 12);
	mx.setRC(3, 0, 13.5);
	mx.setRC(3, 1, 14.5);
	mx.setRC(3, 2, 15.5);
	mx.setRC(3, 3, 16.5);
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 0), a));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 1), b));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 2), c));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 3), d));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 0), e));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 1), f));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 2), g));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 3), h));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(2, 0), i));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(2, 1), j));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(2, 2), k));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(2, 3), l));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(3, 0), m));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(3, 1), n));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(3, 2), o));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(3, 3), p));
	double arr[16] = { 1,2,3,4,5.5,6.5,7.5,8.5,9,10,11,12,13.5,14.5,15.5,16.5 };
	Matrix mx2 = Matrix(4, 4, arr);
	EXPECT_TRUE(mx.checkEqual(mx2));
};

TEST_F(MatrixTest, Matrix2x2ctor)
{
	double a = -3;
	double b = 5;
	double c = 1;
	double d = -2;
	Matrix mx = Matrix(2, 2);
	mx.setRC(0, 0, a);
	mx.setRC(0, 1, b);
	mx.setRC(1, 0, c);
	mx.setRC(1, 1, d);
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 0), a));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 1), b));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 0), c));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 1), d));
	double arr[4] = { -3,5,1,-2 };
	Matrix mx2 = Matrix(2, 2, arr);
	EXPECT_TRUE(mx.checkEqual(mx2));
};

TEST_F(MatrixTest, Matrix3x3ctor)
{
	double a = -3;
	double b = 5;
	double c = 1;
	double d = -2;
	double e = 0;
	double f = -7;
	Matrix mx = Matrix(3, 3);
	mx.setRC(0, 0, -3);
	mx.setRC(0, 1, 5);
	mx.setRC(0, 2, 0);
	mx.setRC(1, 0, 1);
	mx.setRC(1, 1, -2);
	mx.setRC(1, 2, -7);
	mx.setRC(2, 0, 0);
	mx.setRC(2, 1, 1);
	mx.setRC(2, 2, 1);
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 0), a));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 1), b));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(0, 2), e));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 0), c));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 1), d));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(1, 2), f));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(2, 0), e));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(2, 1), c));
	EXPECT_TRUE(ce.checkFloat(mx.getRC(2, 2), c));
	double arr[9] = { -3,5,0,1,-2,-7,0,1,1 };
	Matrix mx2 = Matrix(3, 3, arr);
	EXPECT_TRUE(mx.checkEqual(mx2));
};

TEST_F(MatrixTest, MatrixComparison4x4to4x4True)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, 1);
	mx1.setRC(0, 1, 2);
	mx1.setRC(0, 2, 3);
	mx1.setRC(0, 3, 4);
	mx1.setRC(1, 0, 5);
	mx1.setRC(1, 1, 6);
	mx1.setRC(1, 2, 7);
	mx1.setRC(1, 3, 8);
	mx1.setRC(2, 0, 9);
	mx1.setRC(2, 1, 8);
	mx1.setRC(2, 2, 7);
	mx1.setRC(2, 3, 6);
	mx1.setRC(3, 0, 5);
	mx1.setRC(3, 1, 4);
	mx1.setRC(3, 2, 3);
	mx1.setRC(3, 3, 2);
	Matrix mx2 = Matrix(4, 4);
	mx2.setRC(0, 0, 1);
	mx2.setRC(0, 1, 2);
	mx2.setRC(0, 2, 3);
	mx2.setRC(0, 3, 4);
	mx2.setRC(1, 0, 5);
	mx2.setRC(1, 1, 6);
	mx2.setRC(1, 2, 7);
	mx2.setRC(1, 3, 8);
	mx2.setRC(2, 0, 9);
	mx2.setRC(2, 1, 8);
	mx2.setRC(2, 2, 7);
	mx2.setRC(2, 3, 6);
	mx2.setRC(3, 0, 5);
	mx2.setRC(3, 1, 4);
	mx2.setRC(3, 2, 3);
	mx2.setRC(3, 3, 2);
	EXPECT_TRUE((mx1 == mx2));
};

TEST_F(MatrixTest, MatrixComparison4x4to4x4False)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, 1);
	mx1.setRC(0, 1, 2);
	mx1.setRC(0, 2, 3);
	mx1.setRC(0, 3, 4);
	mx1.setRC(1, 0, 5);
	mx1.setRC(1, 1, 6);
	mx1.setRC(1, 2, 7);
	mx1.setRC(1, 3, 8);
	mx1.setRC(2, 0, 9);
	mx1.setRC(2, 1, 8);
	mx1.setRC(2, 2, 7);
	mx1.setRC(2, 3, 6);
	mx1.setRC(3, 0, 5);
	mx1.setRC(3, 1, 4);
	mx1.setRC(3, 2, 3);
	mx1.setRC(3, 3, 2);
	Matrix mx2 = Matrix(4, 4);
	mx2.setRC(0, 0, 1);
	mx2.setRC(0, 1, 2);
	mx2.setRC(0, 2, 3);
	mx2.setRC(0, 3, 4);
	mx2.setRC(1, 0, 5);
	mx2.setRC(1, 1, 6);
	mx2.setRC(1, 2, 7);
	mx2.setRC(1, 3, 8);
	mx2.setRC(2, 0, 9);
	mx2.setRC(2, 1, 8);
	mx2.setRC(2, 2, 7);
	mx2.setRC(2, 3, 6);
	mx2.setRC(3, 0, 5);
	mx2.setRC(3, 1, 4);
	mx2.setRC(3, 2, 3);
	mx2.setRC(3, 3, 1);
	EXPECT_FALSE((mx1 == mx2));
};

TEST_F(MatrixTest, MatrixMultiplication4x4to4x4)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, 1);
	mx1.setRC(0, 1, 2);
	mx1.setRC(0, 2, 3);
	mx1.setRC(0, 3, 4);
	mx1.setRC(1, 0, 5);
	mx1.setRC(1, 1, 6);
	mx1.setRC(1, 2, 7);
	mx1.setRC(1, 3, 8);
	mx1.setRC(2, 0, 9);
	mx1.setRC(2, 1, 8);
	mx1.setRC(2, 2, 7);
	mx1.setRC(2, 3, 6);
	mx1.setRC(3, 0, 5);
	mx1.setRC(3, 1, 4);
	mx1.setRC(3, 2, 3);
	mx1.setRC(3, 3, 2);
	Matrix mx2 = Matrix(4, 4);
	mx2.setRC(0, 0, -2);
	mx2.setRC(0, 1, 1);
	mx2.setRC(0, 2, 2);
	mx2.setRC(0, 3, 3);
	mx2.setRC(1, 0, 3);
	mx2.setRC(1, 1, 2);
	mx2.setRC(1, 2, 1);
	mx2.setRC(1, 3, -1);
	mx2.setRC(2, 0, 4);
	mx2.setRC(2, 1, 3);
	mx2.setRC(2, 2, 6);
	mx2.setRC(2, 3, 5);
	mx2.setRC(3, 0, 1);
	mx2.setRC(3, 1, 2);
	mx2.setRC(3, 2, 7);
	mx2.setRC(3, 3, 8);
	// Matrix* res = mx1 * mx2;
	Matrix res = mx1 * mx2;
	Matrix mx3 = Matrix(4, 4);
	mx3.setRC(0, 0, 20);
	mx3.setRC(0, 1, 22);
	mx3.setRC(0, 2, 50);
	mx3.setRC(0, 3, 48);
	mx3.setRC(1, 0, 44);
	mx3.setRC(1, 1, 54);
	mx3.setRC(1, 2, 114);
	mx3.setRC(1, 3, 108);
	mx3.setRC(2, 0, 40);
	mx3.setRC(2, 1, 58);
	mx3.setRC(2, 2, 110);
	mx3.setRC(2, 3, 102);
	mx3.setRC(3, 0, 16);
	mx3.setRC(3, 1, 26);
	mx3.setRC(3, 2, 46);
	mx3.setRC(3, 3, 42);
	EXPECT_TRUE(mx3.checkEqual(res));
	// EXPECT_TRUE(mx3.checkEqual(*res));
};


TEST_F(MatrixTest, MatrixMultiplicationTuple)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, 1);
	mx1.setRC(0, 1, 2);
	mx1.setRC(0, 2, 3);
	mx1.setRC(0, 3, 4);
	mx1.setRC(1, 0, 2);
	mx1.setRC(1, 1, 4);
	mx1.setRC(1, 2, 4);
	mx1.setRC(1, 3, 2);
	mx1.setRC(2, 0, 8);
	mx1.setRC(2, 1, 6);
	mx1.setRC(2, 2, 4);
	mx1.setRC(2, 3, 1);
	mx1.setRC(3, 0, 0);
	mx1.setRC(3, 1, 0);
	mx1.setRC(3, 2, 0);
	mx1.setRC(3, 3, 1);
	Tuple tup1 = Tuple(1, 2, 3, 1);
	Tuple res = mx1 * tup1;
	Tuple tup2 = Tuple(18, 24, 33, 1);
	EXPECT_TRUE(ce.checkTuple(res,tup2));
};

TEST_F(MatrixTest, IdentityMatrixMultiplication)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, 1);
	mx1.setRC(0, 1, 2);
	mx1.setRC(0, 2, 3);
	mx1.setRC(0, 3, 4);
	mx1.setRC(1, 0, 2);
	mx1.setRC(1, 1, 4);
	mx1.setRC(1, 2, 4);
	mx1.setRC(1, 3, 2);
	mx1.setRC(2, 0, 8);
	mx1.setRC(2, 1, 6);
	mx1.setRC(2, 2, 4);
	mx1.setRC(2, 3, 1);
	mx1.setRC(3, 0, 0);
	mx1.setRC(3, 1, 0);
	mx1.setRC(3, 2, 0);
	mx1.setRC(3, 3, 1);
	IdentityMatrix im = IdentityMatrix(4, 4);
	// Matrix* res = mx1 * im;
	// EXPECT_TRUE(mx1.checkEqual(*res));
	Matrix res = mx1 * im;
	EXPECT_TRUE(mx1.checkEqual(res));
};


TEST_F(MatrixTest, TransposeMatrix)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, 0);
	mx1.setRC(0, 1, 9);
	mx1.setRC(0, 2, 3);
	mx1.setRC(0, 3, 0);
	mx1.setRC(1, 0, 9);
	mx1.setRC(1, 1, 8);
	mx1.setRC(1, 2, 0);
	mx1.setRC(1, 3, 8);
	mx1.setRC(2, 0, 1);
	mx1.setRC(2, 1, 8);
	mx1.setRC(2, 2, 5);
	mx1.setRC(2, 3, 3);
	mx1.setRC(3, 0, 0);
	mx1.setRC(3, 1, 0);
	mx1.setRC(3, 2, 5);
	mx1.setRC(3, 3, 8);
	// Matrix* res = mx1.transpose();
	Matrix res = mx1.transpose();
	Matrix mx2 = Matrix(4, 4);
	mx2.setRC(0, 0, 0);
	mx2.setRC(0, 1, 9);
	mx2.setRC(0, 2, 1);
	mx2.setRC(0, 3, 0);
	mx2.setRC(1, 0, 9);
	mx2.setRC(1, 1, 8);
	mx2.setRC(1, 2, 8);
	mx2.setRC(1, 3, 0);
	mx2.setRC(2, 0, 3);
	mx2.setRC(2, 1, 0);
	mx2.setRC(2, 2, 5);
	mx2.setRC(2, 3, 5);
	mx2.setRC(3, 0, 0);
	mx2.setRC(3, 1, 8);
	mx2.setRC(3, 2, 3);
	mx2.setRC(3, 3, 8);
	// EXPECT_TRUE(mx2.checkEqual(*res));
	EXPECT_TRUE(mx2.checkEqual(res));
};

TEST_F(MatrixTest, TransposeIdentityMatrix)
{
	IdentityMatrix im = IdentityMatrix(4, 4);
	// Matrix* res = im.transpose();
	// EXPECT_TRUE(im.checkEqual(*res));
	Matrix res = im.transpose();
	EXPECT_TRUE(im.checkEqual(res));
};

TEST_F(MatrixTest, MatrixDeterminant)
{
	Matrix mx1 = Matrix(2, 2);
	mx1.setRC(0, 0, 1);
	mx1.setRC(0, 1, 5);
	mx1.setRC(1, 0, -3);
	mx1.setRC(1, 1, 2);
	double res = mx1.determinant();
	int expected = 17;
	EXPECT_TRUE(ce.checkFloat(res, expected));
};

TEST_F(MatrixTest, MatrixSub3x3)
{
	Matrix mx1 = Matrix(3, 3);
	mx1.setRC(0, 0, 1);
	mx1.setRC(0, 1, 5);
	mx1.setRC(0, 2, 0);
	mx1.setRC(1, 0, -3);
	mx1.setRC(1, 1, 2);
	mx1.setRC(1, 2, 7);
	mx1.setRC(2, 0, 0);
	mx1.setRC(2, 1, 6);
	mx1.setRC(2, 2, -3);
	// Matrix* res = mx1.submatrix(0,2);
	Matrix res = mx1.submatrix(0,2);
	Matrix mx2 = Matrix(2, 2);
	mx2.setRC(0, 0, -3);
	mx2.setRC(0, 1, 2);
	mx2.setRC(1, 0, 0);
	mx2.setRC(1, 1, 6);
	// EXPECT_TRUE(mx2.checkEqual(*res));
	EXPECT_TRUE(mx2.checkEqual(res));
};

TEST_F(MatrixTest, MatrixSub4x4)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, -6);
	mx1.setRC(0, 1, 1);
	mx1.setRC(0, 2, 1);
	mx1.setRC(0, 3, 6);
	mx1.setRC(1, 0, -8);
	mx1.setRC(1, 1, 5);
	mx1.setRC(1, 2, 8);
	mx1.setRC(1, 3, 6);
	mx1.setRC(2, 0, -1);
	mx1.setRC(2, 1, 0);
	mx1.setRC(2, 2, 8);
	mx1.setRC(2, 3, 2);
	mx1.setRC(3, 0, -7);
	mx1.setRC(3, 1, 1);
	mx1.setRC(3, 2, -1);
	mx1.setRC(3, 3, 1);
	// Matrix* res = mx1.submatrix(2, 1);
	Matrix res = mx1.submatrix(2, 1);
	Matrix mx2 = Matrix(3, 3);
	mx2.setRC(0, 0, -6);
	mx2.setRC(0, 1, 1);
	mx2.setRC(0, 2, 6);
	mx2.setRC(1, 0, -8);
	mx2.setRC(1, 1, 8);
	mx2.setRC(1, 2, 6);
	mx2.setRC(2, 0, -7);
	mx2.setRC(2, 1, -1);
	mx2.setRC(2, 2, 1);
	// EXPECT_TRUE(mx2.checkEqual(*res));
	EXPECT_TRUE(mx2.checkEqual(res));
};

TEST_F(MatrixTest, MatrixMinor)
{

	Matrix mx1 = Matrix(3, 3);
	mx1.setRC(0, 0, 3);
	mx1.setRC(0, 1, 5);
	mx1.setRC(0, 2, 0);
	mx1.setRC(1, 0, 2);
	mx1.setRC(1, 1, -1);
	mx1.setRC(1, 2, -7);
	mx1.setRC(2, 0, 6);
	mx1.setRC(2, 1, -1);
	mx1.setRC(2, 2, 5);
	double res = mx1.minor(1, 0);
	int expected = 25;
	EXPECT_EQ(res, expected);
};

TEST_F(MatrixTest, MatrixCofactor)
{
	Matrix mx1 = Matrix(3, 3);
	mx1.setRC(0, 0, 3);
	mx1.setRC(0, 1, 5);
	mx1.setRC(0, 2, 0);
	mx1.setRC(1, 0, 2);
	mx1.setRC(1, 1, -1);
	mx1.setRC(1, 2, -7);
	mx1.setRC(2, 0, 6);
	mx1.setRC(2, 1, -1);
	mx1.setRC(2, 2, 5);
	double m1 = mx1.cofactor(0, 0);
	int even = -12;
	EXPECT_EQ(m1, even);
	double m2 = mx1.cofactor(1, 0);
	int odd = -25;
	EXPECT_EQ(m2, odd);
};

TEST_F(MatrixTest, MatrixDeteriminant3x3)
{
	Matrix mx1 = Matrix(3, 3);
	mx1.setRC(0, 0, 1);
	mx1.setRC(0, 1, 2);
	mx1.setRC(0, 2, 6);
	mx1.setRC(1, 0, -5);
	mx1.setRC(1, 1, 8);
	mx1.setRC(1, 2, -4);
	mx1.setRC(2, 0, 2);
	mx1.setRC(2, 1, 6);
	mx1.setRC(2, 2, 4);
	double m1d = mx1.determinant();
	int expected = -196;
	EXPECT_EQ(m1d, expected);
};

TEST_F(MatrixTest, MatrixDeteriminant4x4)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, -2);
	mx1.setRC(0, 1, -8);
	mx1.setRC(0, 2, 3);
	mx1.setRC(0, 3, 5);
	mx1.setRC(1, 0, -3);
	mx1.setRC(1, 1, 1);
	mx1.setRC(1, 2, 7);
	mx1.setRC(1, 3, 3);
	mx1.setRC(2, 0, 1);
	mx1.setRC(2, 1, 2);
	mx1.setRC(2, 2, -9);
	mx1.setRC(2, 3, 6);
	mx1.setRC(3, 0, -6);
	mx1.setRC(3, 1, 7);
	mx1.setRC(3, 2, 7);
	mx1.setRC(3, 3, -9);
	double m1d = mx1.determinant();
	int expected = -4071;
	EXPECT_EQ(m1d, expected);
};

TEST_F(MatrixTest, MatrixInvertibility)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, 6);
	mx1.setRC(0, 1, 4);
	mx1.setRC(0, 2, 4);
	mx1.setRC(0, 3, 4);
	mx1.setRC(1, 0, 5);
	mx1.setRC(1, 1, 5);
	mx1.setRC(1, 2, 7);
	mx1.setRC(1, 3, 6);
	mx1.setRC(2, 0, 4);
	mx1.setRC(2, 1, -9);
	mx1.setRC(2, 2, 3);
	mx1.setRC(2, 3, -7);
	mx1.setRC(3, 0, 9);
	mx1.setRC(3, 1, 1);
	mx1.setRC(3, 2, 7);
	mx1.setRC(3, 3, -6);
	EXPECT_TRUE(mx1.checkInvertible());
	Matrix mx2 = Matrix(4, 4);
	mx2.setRC(0, 0, -4);
	mx2.setRC(0, 1, 2);
	mx2.setRC(0, 2, -2);
	mx2.setRC(0, 3, -3);
	mx2.setRC(1, 0, 9);
	mx2.setRC(1, 1, 6);
	mx2.setRC(1, 2, 2);
	mx2.setRC(1, 3, 6);
	mx2.setRC(2, 0, 0);
	mx2.setRC(2, 1, -5);
	mx2.setRC(2, 2, 1);
	mx2.setRC(2, 3, -5);
	mx2.setRC(3, 0, 0);
	mx2.setRC(3, 1, 0);
	mx2.setRC(3, 2, 0);
	mx2.setRC(3, 3, 0);
	EXPECT_FALSE(mx2.checkInvertible());
};

TEST_F(MatrixTest, MatrixInverse4x4)
{
	Matrix mx1 = Matrix(4, 4);
	mx1.setRC(0, 0, -5);
	mx1.setRC(0, 1, 2);
	mx1.setRC(0, 2, 6);
	mx1.setRC(0, 3, -8);
	mx1.setRC(1, 0, 1);
	mx1.setRC(1, 1, -5);
	mx1.setRC(1, 2, 1);
	mx1.setRC(1, 3, 8);
	mx1.setRC(2, 0, 7);
	mx1.setRC(2, 1, 7);
	mx1.setRC(2, 2, -6);
	mx1.setRC(2, 3, -7);
	mx1.setRC(3, 0, 1);
	mx1.setRC(3, 1, -3);
	mx1.setRC(3, 2, 7);
	mx1.setRC(3, 3, 4);
	// Matrix* imx1 = mx1.invert();
	Matrix imx1 = mx1.getInverse();
	Matrix mx2 = Matrix(4, 4);
	mx2.setRC(0, 0, 0.21805);
	mx2.setRC(0, 1, 0.45113);
	mx2.setRC(0, 2, 0.24060);
	mx2.setRC(0, 3, -0.04511);
	mx2.setRC(1, 0, -0.80827);
	mx2.setRC(1, 1, -1.45677);
	mx2.setRC(1, 2, -0.44361);
	mx2.setRC(1, 3, 0.52068);
	mx2.setRC(2, 0, -0.07895);
	mx2.setRC(2, 1, -0.22368);
	mx2.setRC(2, 2, -0.05263);
	mx2.setRC(2, 3, 0.19737);
	mx2.setRC(3, 0, -0.52256);
	mx2.setRC(3, 1, -0.81391);
	mx2.setRC(3, 2, -0.30075);
	mx2.setRC(3, 3, 0.30639);
	// EXPECT_TRUE(mx2.checkEqual(*imx1));
	EXPECT_TRUE(mx2.checkEqual(imx1));
	double mx3arr[16] = { 8,-5,9,2,7,5,6,1,-6,0,9,6,-3,0,-9,-4 };
	Matrix mx3 = Matrix(4, 4, mx3arr);
	double mx3iarr[16] = { -0.15385 , -0.15385 , -0.28205 , -0.53846 , -0.07692 , 0.12308 , 0.02564 , 0.03077 , 0.35897 , 0.35897 , 0.43590 , 0.92308 , -0.69231 , -0.69231 , -0.76923 , -1.92308 };
	Matrix mx3i = Matrix(4, 4, mx3iarr);
	// Matrix* imx3 = mx3.invert();
	Matrix imx3 = mx3.getInverse();
	// EXPECT_TRUE(mx3i.checkEqual(*imx3));
	EXPECT_TRUE(mx3i.checkEqual(imx3));
	double mx4arr[16] = { 9,3,0,9,-5,-2,-6,-3,-4,9,6,4,-7,6,6,2 };
	Matrix mx4 = Matrix(4, 4, mx4arr);
	double mx4iarr[16] = { -0.04074 , -0.07778 , 0.14444 , -0.22222 , -0.07778 , 0.03333 , 0.36667 , -0.33333 , -0.02901 , -0.14630 , -0.10926 , 0.12963 , 0.17778 , 0.06667 , -0.26667 , 0.33333 };
	Matrix mx4i = Matrix(4, 4, mx4iarr);
	// Matrix* imx4 = mx4.invert();
	// EXPECT_TRUE(mx4i.checkEqual(*imx4));
	Matrix imx4 = mx4.getInverse();
	EXPECT_TRUE(mx4i.checkEqual(imx4));
};

TEST_F(MatrixTest, MatrixProductByInverse4x4)
{
	double mx1arr[16] = { 3,-9,7,3,3,-8,2,-9,-4,4,4,1,-6,5,-1,1 };
	Matrix mx1 = Matrix(4, 4, mx1arr);
	double mx2arr[16] = { 8,2,2,2,3,-1,7,0,7,0,5,4,6,-2,-5 };
	Matrix mx2 = Matrix(4, 4, mx2arr);
	// Matrix* mx21 = mx1 * mx2;
	// Matrix* imx2 = mx2.invert();
	// Matrix* mx21imx2 = (*mx21) * (*imx2);
	// EXPECT_TRUE(mx1.checkEqual(*mx21imx2));
	Matrix mx21 = mx1 * mx2;
	Matrix imx2 = mx2.getInverse();
	Matrix mx21imx2 = mx21 * imx2;
	EXPECT_TRUE(mx1.checkEqual(mx21imx2));
};

TEST_F(TransformationTest, CanaryTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
};

TEST_F(TransformationTest, TransformationTranslationMatrixMove)
{
	TranslationMatrix tm = TranslationMatrix(5, -3,2);
	Point p = Point(-3, 4, 5);
	Point res = tm * p;
	Point expected = Point(2, 1, 7);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationInverseTranslationMatrixReverseMove)
{
	TranslationMatrix tm = TranslationMatrix(5, -3, 2);
	// Matrix* itm = tm.invert();
	Matrix itm = tm.getInverse();
	Point p = Point(-3, 4, 5);
	// Point res = (*itm) * p;
	Point res = itm * p;
	Point expected = Point(-8, 7, 3);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationTranslationMatrixVectorNoEffect)
{
	TranslationMatrix tm = TranslationMatrix(5, -3, 2);
	Vector v = Vector(-3, 4, 5);
	Vector res = tm * v;
	Vector expected = Vector(-3, 4, 5);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationScalingMatrixPoint)
{
	ScalingMatrix sm = ScalingMatrix(2, 3, 4);
	Point p = Point(-4, 6, 8);
	Point res = sm * p;
	Point expected = Point(-8, 18, 32);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationScalingMatrixVector)
{
	ScalingMatrix sm = ScalingMatrix(2, 3, 4);
	Vector p = Vector(-4, 6, 8);
	Vector res = sm * p;
	Vector expected = Vector(-8, 18, 32);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationScalingMatrixInverseVector)
{
	ScalingMatrix sm = ScalingMatrix(2, 3, 4);
	// Matrix* im = sm.invert();
	Matrix im = sm.getInverse();
	Vector p = Vector(-4, 6, 8);
	// Vector res = (*im) * p;
	Vector res = im * p;
	Vector expected = Vector(-2, 2, 2);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationScalingMatrixReflection)
{
	ScalingMatrix rm = ScalingMatrix(-1, 1, 1);
	Point p = Point(2, 3, 4);
	Point res = rm * p;
	Point expected = Point(-2, 3, 4);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationRotationMatrixX)
{
	Point p = Point(0, 1, 0);
	XRotationMatrix xrm90 = XRotationMatrix(getPI()/4);
	Point res90 = xrm90 * p;
	Point expected90 = Point(0,sqrt(2)/2, sqrt(2)/2);
	EXPECT_TRUE(ce.checkTuple(res90, expected90));
	XRotationMatrix xrm180 = XRotationMatrix(getPI() / 2);
	Point res180 = xrm180 * p;
	Point expected180 = Point(0, 0, 1);
	EXPECT_TRUE(ce.checkTuple(res180, expected180));
};

TEST_F(TransformationTest, TransformationRotationMatrixXInverse)
{
	Point p = Point(0, 1, 0);
	XRotationMatrix xrm90 = XRotationMatrix(getPI() / 4);
	// Matrix* ixrm90 = xrm90.invert();
	Matrix ixrm90 = xrm90.getInverse();
	// Point res = (*ixrm90) * p;
	Point res = ixrm90 * p;
	Point expected = Point(0, sqrt(2) / 2, -sqrt(2) / 2);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationRotationMatrixY)
{
	Point p = Point(0, 0, 1);
	YRotationMatrix yrm90 = YRotationMatrix(getPI() / 4);
	Point res90 = yrm90 * p;
	Point expected90 = Point(sqrt(2) / 2, 0, sqrt(2) / 2);
	EXPECT_TRUE(ce.checkTuple(res90, expected90));
	YRotationMatrix yrm180 = YRotationMatrix(getPI() / 2);
	Point res180 = yrm180 * p;
	Point expected180 = Point(1, 0, 0);
	EXPECT_TRUE(ce.checkTuple(res180, expected180));
};

TEST_F(TransformationTest, TransformationRotationMatrixZ)
{
	Point p = Point(0, 1, 0);
	ZRotationMatrix zrm90 = ZRotationMatrix(getPI() / 4);
	Point res90 = zrm90 * p;
	Point expected90 = Point(-sqrt(2) / 2, sqrt(2) / 2, 0);
	EXPECT_TRUE(ce.checkTuple(res90, expected90));
	ZRotationMatrix zrm180 = ZRotationMatrix(getPI() / 2);
	Point res180 = zrm180 * p;
	Point expected180 = Point(-1, 0, 0);
	EXPECT_TRUE(ce.checkTuple(res180, expected180));
};

TEST_F(TransformationTest, TransformationShearingXToY)
{
	ShearingMatrix sm = ShearingMatrix(1, 0, 0, 0, 0, 0);
	Point p = Point(2, 3, 4);
	Point res = sm * p;
	Point expected = Point(5, 3, 4);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationShearingXToZ)
{
	ShearingMatrix sm = ShearingMatrix(0, 1, 0, 0, 0, 0);
	Point p = Point(2, 3, 4);
	Point res = sm * p;
	Point expected = Point(6, 3, 4);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationShearingYToX)
{
	ShearingMatrix sm = ShearingMatrix(0, 0, 1, 0, 0, 0);
	Point p = Point(2, 3, 4);
	Point res = sm * p;
	Point expected = Point(2, 5, 4);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationShearingYToZ)
{
	ShearingMatrix sm = ShearingMatrix(0, 0, 0, 1, 0, 0);
	Point p = Point(2, 3, 4);
	Point res = sm * p;
	Point expected = Point(2, 7, 4);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationShearingZToX)
{
	ShearingMatrix sm = ShearingMatrix(0, 0, 0, 0, 1, 0);
	Point p = Point(2, 3, 4);
	Point res = sm * p;
	Point expected = Point(2, 3, 6);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, TransformationShearingZToY)
{
	ShearingMatrix sm = ShearingMatrix(0, 0, 0, 0, 0, 1);
	Point p = Point(2, 3, 4);
	Point res = sm * p;
	Point expected = Point(2, 3, 7);
	EXPECT_TRUE(ce.checkTuple(res, expected));
};

TEST_F(TransformationTest, ChainingTransformationInSequence)
{
	Point p = Point(1, 0, 1);
	XRotationMatrix xrm = XRotationMatrix(getPI() / 2);
	ScalingMatrix sm = ScalingMatrix(5, 5, 5);
	TranslationMatrix tm = TranslationMatrix(10, 5, 7);
	Point rotated = xrm * p;
	Point rotatedExpected = Point(1, -1, 0);
	EXPECT_TRUE(ce.checkTuple(rotated, rotatedExpected));
	Point scaled = sm * rotated;
	Point scaledExpected = Point(5,-5,0);
	EXPECT_TRUE(ce.checkTuple(scaled, scaledExpected));
	Point translated = tm * scaled;
	Point translatedExpected = Point(15, 0, 7);
	EXPECT_TRUE(ce.checkTuple(translated, translatedExpected));
};

TEST_F(TransformationTest, ChainingTransformationAppliedInReverseOrder)
{
	Point p = Point(1, 0, 1);
	XRotationMatrix xrm = XRotationMatrix(getPI() / 2);
	ScalingMatrix sm = ScalingMatrix(5, 5, 5);
	TranslationMatrix tm = TranslationMatrix(10, 5, 7);
	// Matrix* tsrm = *(tm * sm) * xrm;
	Matrix tsrm = tm * sm * xrm;
	// Point transformed = (*tsrm) * p;
	Point transformed = tsrm * p;
	Point expected = Point(15, 0, 7);
	EXPECT_TRUE(ce.checkTuple(transformed, expected));
	// Matrix tsrmc = *(*(*(*(Matrix(4, 4).identity())).translate(10, 5, 7)).scale(5, 5, 5)).rotateX(getPI() / 2);
	Matrix tsrmc = Matrix(4, 4).identity().translate(10, 5, 7).scale(5, 5, 5).rotateX(getPI() / 2);
	EXPECT_TRUE(tsrm.checkEqual(tsrmc));
	Point transformedc = tsrmc * p;
	EXPECT_TRUE(ce.checkTuple(transformedc, expected));
};

TEST_F(TransformationTest, ViewTransformDefault)
{
	Point from = Point(0,0,0);
	Point to = Point(0,0,-1);
	Vector up = Vector(0,1,0);
	ViewMatrix view = ViewMatrix(from, to, up);
	IdentityMatrix im = IdentityMatrix(4,4);
	EXPECT_TRUE(view.checkEqual(im));
};

TEST_F(TransformationTest, ViewTransformDefaultReverse)
{
	Point from = Point(0,0,0);
	Point to = Point(0,0,1);
	Vector up = Vector(0,1,0);
	ViewMatrix view = ViewMatrix(from, to, up);
	ScalingMatrix sm = ScalingMatrix(-1,1,-1);
	EXPECT_TRUE(view.checkEqual(sm));
};

TEST_F(TransformationTest, ViewTransformMovesWorldNotEye)
{
	Point from = Point(0,0,8);
	Point to = Point(0,0,0);
	Vector up = Vector(0,1,0);
	ViewMatrix view = ViewMatrix(from, to, up);
	TranslationMatrix sm = TranslationMatrix(0,0,-8);
	EXPECT_TRUE(view.checkEqual(sm));
};

TEST_F(TransformationTest, ViewTransformAngledView)
{
	Point from = Point(1,3,2);
	Point to = Point(4,-2,8);
	Vector up = Vector(1,1,0);
	ViewMatrix view = ViewMatrix(from, to, up);
	double arr[] = {-0.50709, 0.50709, 0.67612, -2.36643, 0.76772, 0.60609, 0.12122, -2.82843, -0.35857, 0.59761, -0.71714, 0, 0, 0, 0, 1 };
	Matrix sm = Matrix(4, 4, arr);
	EXPECT_TRUE(view.checkEqual(sm));
};