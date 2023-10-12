#include "form.h"
#include "comparinator.h"
#include "ray.h"
#include "pch.h"
#include "tuple.h"
#include "intersection.h"
#include "matrix.h"
#include "pattern.h"
#include "material.h"

class SphereTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(SphereTest, CanaryTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
};

TEST_F(SphereTest, EqualityTest) {
	Sphere s = Sphere();
	EXPECT_TRUE(s.checkEqual(s));
};

TEST_F(SphereTest, RayIntersectTwo) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	Intersections varXs = s.getIntersections(r);
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_EQ(xs[0].mbrTime, 4);
	// EXPECT_EQ(xs[1].mbrTime, 6);
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_EQ(varXs.mbrIntersections[0]->mbrTime, 4);
	EXPECT_EQ(varXs.mbrIntersections[1]->mbrTime, 6);
};

TEST_F(SphereTest, RayIntersectTangent) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	Intersections varXs = s.getIntersections(r);
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_EQ(xs[0].mbrTime, 5);
	// EXPECT_EQ(xs[1].mbrTime, 5);
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_EQ(varXs.mbrIntersections[0]->mbrTime, 5);
	EXPECT_EQ(varXs.mbrIntersections[1]->mbrTime, 5);
};

TEST_F(SphereTest, RayIntersectMiss) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	Intersections varXs = s.getIntersections(r);
	EXPECT_EQ(varXs.mbrIntersections.size(), 0);
};

TEST_F(SphereTest, RayIntersectWithinSphere) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_EQ(xs[0].mbrTime, -1);
	// EXPECT_EQ(xs[1].mbrTime, 1);
	Intersections varXs = s.getIntersections(r);
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_EQ(varXs.mbrIntersections[0]->mbrTime, -1);
	EXPECT_EQ(varXs.mbrIntersections[1]->mbrTime, 1);
};

TEST_F(SphereTest, RayIntersectBehindSphere) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_EQ(xs[0].mbrTime, -6);
	// EXPECT_EQ(xs[1].mbrTime, -4);
	Intersections varXs = s.getIntersections(r);
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_EQ(varXs.mbrIntersections[0]->mbrTime, -6);
	EXPECT_EQ(varXs.mbrIntersections[1]->mbrTime, -4);
};

TEST_F(SphereTest, RayIntersectSetsObject) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_TRUE(s.checkEqual(*xs[0].mbrObject.get()));
	// EXPECT_TRUE(s.checkEqual(*xs[1].mbrObject.get()));
	Intersections varXs = s.getIntersections(r);
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_TRUE(s.checkEqual(*(varXs.mbrIntersections[0]->mbrObject.get())));
	EXPECT_TRUE(s.checkEqual(*(varXs.mbrIntersections[1]->mbrObject.get())));
};

TEST_F(SphereTest, SphereDefaultTransformIsIdentity) {
	Sphere s = Sphere();
	IdentityMatrix m = IdentityMatrix(4, 4);
	EXPECT_TRUE(m.checkEqual(*s.mbrTransform));
};

TEST_F(SphereTest, SphereModifyTransform) {
	Sphere s = Sphere();
	TranslationMatrix m = TranslationMatrix(2, 3, 4);
	s.setTransform(m);
	EXPECT_TRUE(m.checkEqual(*s.mbrTransform));
};

TEST_F(SphereTest, SphereIdentityDoesNotModifyIntersections) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	ScalingMatrix m = ScalingMatrix(1, 1, 1);
	s.setTransform(m);
	EXPECT_TRUE(m.checkEqual(*s.mbrTransform));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_EQ(xs[0].mbrTime, 4);
	// EXPECT_EQ(xs[1].mbrTime, 6);
	Intersections varXs = s.getIntersections(r);
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_EQ(varXs.mbrIntersections[0]->mbrTime, 4);
	EXPECT_EQ(varXs.mbrIntersections[1]->mbrTime, 6);
};

TEST_F(SphereTest, SphereScaledModifiesIntersections) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	ScalingMatrix m = ScalingMatrix(2, 2, 2);
	s.setTransform(m);
	// EXPECT_TRUE(m.checkEqual(*s.mbrTransform));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_EQ(xs[0].mbrTime, 3);
	// EXPECT_EQ(xs[1].mbrTime, 7);
	// EXPECT_TRUE(ce.checkTuple(s.mbrObjectRay.mbrOrigin, Point(0,0,-2.5)));
	// EXPECT_TRUE(ce.checkTuple(s.mbrObjectRay.mbrDirection, Vector(0,0,0.5)));
	Intersections varXs = s.getIntersections(r);
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_EQ(varXs.mbrIntersections[0]->mbrTime, 3);
	EXPECT_EQ(varXs.mbrIntersections[1]->mbrTime, 7);
	EXPECT_TRUE(ce.checkTuple(s.mbrObjectRay.mbrOrigin, Point(0,0,-2.5)));
	EXPECT_TRUE(ce.checkTuple(s.mbrObjectRay.mbrDirection, Vector(0,0,0.5)));
};

TEST_F(SphereTest, SphereScaledTo5Intersections) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	ScalingMatrix m = ScalingMatrix(5, 5, 5);
	s.setTransform(Matrix(m));
	EXPECT_TRUE(m.checkEqual(*s.mbrTransform));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	Intersections varXs = s.getIntersections(r);
	double z = 0;
	double y = 10;
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_TRUE(ce.checkFloat(xs[0].mbrTime, z));
	// EXPECT_TRUE(ce.checkFloat(xs[1].mbrTime, y));
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_TRUE(ce.checkFloat(varXs.mbrIntersections[0]->mbrTime, z));
	EXPECT_TRUE(ce.checkFloat(varXs.mbrIntersections[1]->mbrTime, y));
};

TEST_F(SphereTest, SphereTranslatedToMiss) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	TranslationMatrix m = TranslationMatrix(5, 0, 0);
	s.setTransform(Matrix(m));
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	Intersections varXs = s.getIntersections(r);
	// EXPECT_EQ(xs.size(), 0);
	EXPECT_EQ(varXs.mbrIntersections.size(), 0);
	EXPECT_TRUE(ce.checkTuple(s.mbrObjectRay.mbrOrigin, Point(-5,0,-5)));
	EXPECT_TRUE(ce.checkTuple(s.mbrObjectRay.mbrDirection, Vector(0,0,1)));
};

TEST_F(SphereTest, SphereTranslatedAway) {
	Sphere s = Sphere();
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	TranslationMatrix m = TranslationMatrix(0, 0, 1);
	s.setTransform(Matrix(m));
	Intersections varXs = s.getIntersections(r);
	// std::vector<Intersection> xs = s.getIntersections(r).mbrIntersections;
	// EXPECT_EQ(xs.size(), 2);
	// EXPECT_EQ(xs[0].mbrTime, 5);
	// EXPECT_EQ(xs[1].mbrTime, 7);
	EXPECT_EQ(varXs.mbrIntersections.size(), 2);
	EXPECT_EQ(varXs.mbrIntersections[0]->mbrTime, 5);
	EXPECT_EQ(varXs.mbrIntersections[1]->mbrTime, 7);
};

TEST_F(SphereTest, SphereNormalX) {
	Sphere s = Sphere();
	Point p = Point(1,0,0);
	Vector normal = s.getNormal(p);
	Vector expectedV = Vector(1,0,0);
	EXPECT_TRUE(ce.checkTuple(normal,expectedV));
};

TEST_F(SphereTest, SphereNormalY) {
	Sphere s = Sphere();
	Point p = Point(0,1,0);
	Vector normal = s.getNormal(p);
	Vector expectedV = Vector(0,1,0);
	EXPECT_TRUE(ce.checkTuple(normal,expectedV));
};

TEST_F(SphereTest, SphereNormalZ) {
	Sphere s = Sphere();
	Point p = Point(0,0,1);
	Vector normal = s.getNormal(p);
	Vector expectedV = Vector(0,0,1);
	EXPECT_TRUE(ce.checkTuple(normal,expectedV));
};

TEST_F(SphereTest, SphereNormal) {
	Sphere s = Sphere();
	Point p = Point(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3);
	Vector normal = s.getNormal(p);
	Vector expectedV = Vector(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3);
	EXPECT_TRUE(ce.checkTuple(normal,expectedV));
};

TEST_F(SphereTest, SphereNormalNormalized) {
	Sphere s = Sphere();
	Point p = Point(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3);
	Vector normal = s.getNormal(p);
	Vector expectedV = normal.normalize();
	EXPECT_TRUE(ce.checkTuple(normal,expectedV));
};

TEST_F(SphereTest, SphereTranslatedNormalized) {
	Sphere s = Sphere();
	Matrix t = TranslationMatrix(0,1,0);
	s.setTransform(t);
	Point p = Point(0, 1.70711, -0.70711);
	Vector normal = s.getNormal(p);
	Vector expectedV = Vector(0, 0.70711, -0.70711);
	EXPECT_TRUE(ce.checkTuple(normal,expectedV));
};

TEST_F(SphereTest, SphereTransformedNormalized) {
	Sphere s = Sphere();
	// Matrix t = *(ScalingMatrix(1, 0.5, 1) * ZRotationMatrix(getPI()/5));
	Matrix t = ScalingMatrix(1, 0.5, 1) * ZRotationMatrix(getPI()/5);
	s.setTransform(t);
	Point p = Point(0,sqrt(2)/2,-sqrt(2)/2);
	Vector normal = s.getNormal(p);
	Vector expectedV = Vector(0,0.97014,-0.24254);
	EXPECT_TRUE(ce.checkTuple(normal,expectedV));
};

TEST_F(SphereTest, SphereMaterialCtor) {
	Sphere s = Sphere();
	Material m = Material();
	EXPECT_TRUE(m.checkEqual(*s.mbrMaterial));
};

TEST_F(SphereTest, SphereMaterialAssignment) {
	Sphere s = Sphere();
	Material m = Material();
	m.mbrAmbient = 1;
	s.setMaterial(m);
	EXPECT_TRUE(m.checkEqual(*s.mbrMaterial));
};

TEST_F(SphereTest, GlassSphereCtor) {
	SphereGlass varObj = SphereGlass();
	EXPECT_TRUE(varObj.mbrTransform->checkEqual(IdentityMatrix(4,4)));
	EXPECT_EQ(varObj.mbrMaterial->mbrTransparency, 1.0);
	EXPECT_EQ(varObj.mbrMaterial->mbrRefractiveIndex, 1.5);
};

class PlaneTest : public ::testing::Test {
protected:
    Comparinator varComp;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        varComp = Comparinator();
    }
	//void TearDown() override { }
};
TEST_F(PlaneTest, PlaneNormalSameEverywhere) {
	Plane varPlane = Plane();
	Vector varN1 = varPlane.getNormal(Point(0,0,0));
	Vector varN2 = varPlane.getNormal(Point(10,0,-10));
	Vector varN3 = varPlane.getNormal(Point(-5,0,150));
	EXPECT_TRUE(varComp.checkTuple(varN1,Vector(0,1,0)));
	EXPECT_TRUE(varComp.checkTuple(varN2,Vector(0,1,0)));
	EXPECT_TRUE(varComp.checkTuple(varN3,Vector(0,1,0)));

};
TEST_F(PlaneTest, RayParallelToPlane) {
	Plane varPlane = Plane();
	Ray varRay = Ray(Point(0,10,0), Vector(0,0,1));
	Intersections varIx = varPlane.getIntersections(varRay);
	EXPECT_TRUE(varIx.mbrIntersections.size() == 0);
};
TEST_F(PlaneTest, CoplanarRayToPlane) {
	Plane varPlane = Plane();
	Ray varRay = Ray(Point(0,0,0), Vector(0,0,1));
	Intersections varIx = varPlane.getIntersections(varRay);
	EXPECT_TRUE(varIx.mbrIntersections.size() == 0);
};
TEST_F(PlaneTest, RayIntersectingPlaneAbove) {
	Plane varPlane = Plane();
	Ray varRay = Ray(Point(0,1,0), Vector(0,-1,0));
	Intersections varIx = varPlane.getIntersections(varRay);
	EXPECT_TRUE(varIx.mbrIntersections.size() == 1);
	// EXPECT_EQ(varIx.mbrIntersections[0].mbrTime, 1);
	// EXPECT_TRUE(varIx.mbrIntersections[0].mbrObject->checkEqual(varPlane));
	EXPECT_EQ(varIx.mbrIntersections[0]->mbrTime, 1);
	EXPECT_TRUE(varIx.mbrIntersections[0]->mbrObject->checkEqual(varPlane));
};
TEST_F(PlaneTest, RayIntersectingPlaneBelow) {
	Plane varPlane = Plane();
	Ray varRay = Ray(Point(0,-1,0), Vector(0,1,0));
	Intersections varIx = varPlane.getIntersections(varRay);
	EXPECT_TRUE(varIx.mbrIntersections.size() == 1);
	// EXPECT_EQ(varIx.mbrIntersections[0].mbrTime, 1);
	// EXPECT_TRUE(varIx.mbrIntersections[0].mbrObject->checkEqual(varPlane));
	EXPECT_EQ(varIx.mbrIntersections[0]->mbrTime, 1);
	EXPECT_TRUE(varIx.mbrIntersections[0]->mbrObject->checkEqual(varPlane));
};