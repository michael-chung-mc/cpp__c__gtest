#include "intersection.h"
#include "form.h"
#include "comparinator.h"
#include "ray.h"
#include "pch.h"

class IntersectionTest : public ::testing::Test {
public:
	Comparinator varComp;
	void SetUp () override {
		varComp = Comparinator();
	}
};

TEST_F(IntersectionTest, CanaryTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
};

TEST_F(IntersectionTest, InitTest) {
	Sphere s = Sphere();
	double t = 3.5;
	// Intersection i = Intersection(t, std::make_unique<Sphere>(s));
	Intersection i = Intersection(t, new Sphere(s));
	EXPECT_EQ(i.mbrTime, t);
	EXPECT_TRUE(i.mbrObject->checkEqual(s));
};

TEST_F(IntersectionTest, AggregationTest) {
	Sphere s = Sphere();
	double t1 = 1;
	double t2 = 2;
	// Intersections i = Intersections(t1, std::make_unique<Sphere>(s));
	// i.intersect(t2, std::make_unique<Sphere>(s));
	Intersections i = Intersections(t1, new Sphere(s));
	i.intersect(t2, new Sphere(s));
	// std::vector<Intersection> xs = i.mbrIntersections;
	// i.intersect(t2, s);
	// std::vector<std::unique_ptr<Intersection>> xs = i.mbrIntersections;
	EXPECT_EQ(i.mbrIntersections.size(),2);
	// EXPECT_EQ(xs[0].mbrTime, t1);
	// EXPECT_EQ(xs[1].mbrTime, t2);
	EXPECT_EQ(i.mbrIntersections[0]->mbrTime, t1);
	EXPECT_EQ(i.mbrIntersections[1]->mbrTime, t2);
};

TEST_F(IntersectionTest, PositiveT) {
	Sphere s = Sphere();
	Intersections i = Intersections(1, new Sphere(s));
	// Intersections i = Intersections(1, std::make_unique<Sphere>(s));
	// i.intersect(2, std::make_unique<Sphere>(s));
	i.intersect(2, new Sphere(s));
	// std::vector<std::unique_ptr<Intersection>> xs = i.mbrIntersections;
	Intersection hit = i.hit();
	// EXPECT_TRUE(hit.checkEqual(xs[0]));
	EXPECT_TRUE(hit.checkEqual(*i.mbrIntersections[0].get()));
};

TEST_F(IntersectionTest, NegativeT) {
	Sphere s = Sphere();
	Intersections i = Intersections(-1, new Sphere(s));
	// Intersections i = Intersections(-1, std::make_unique<Sphere>(s));
	// i.intersect(2, std::make_unique<Sphere>(s));
	i.intersect(2, new Sphere(s));
	// std::vector<Intersection> xs = i.mbrIntersections;
	// std::vector<std::unique_ptr<Intersection>> xs = i.mbrIntersections;
	Intersection hit = i.hit();
	// EXPECT_TRUE(hit.checkEqual(xs[1]));
	EXPECT_TRUE(hit.checkEqual(*i.mbrIntersections[1].get()));
};

TEST_F(IntersectionTest, AllNegativeT) {
	Sphere s = Sphere();
	// Intersections i = Intersections(-1, std::make_unique<Sphere>(s));
	Intersections i = Intersections(-1, new Sphere(s));
	// i.intersect(-2, std::make_unique<Sphere>(s));
	i.intersect(-2, new Sphere(s));
	// std::vector<Intersection> xs = i.mbrIntersections;
	// std::vector<std::unique_ptr<Intersection>> xs = i.mbrIntersections;
	Intersection hit = i.hit();
	EXPECT_FALSE(hit.mbrExists);
};

TEST_F(IntersectionTest, HitIsNonnegativeIntersection) {
	Sphere s = Sphere();
	// Intersections i = Intersections(5, std::make_unique<Sphere>(s));
	Intersections i = Intersections(5, new Sphere(s));
	i.intersect(7, new Sphere(s));
	// i.intersect(7, std::make_unique<Sphere>(s));
	i.intersect(-3, new Sphere(s));
	// i.intersect(-3, std::make_unique<Sphere>(s));
	// i.intersect(2, std::make_unique<Sphere>(s));
	i.intersect(2, new Sphere(s));
	// std::vector<Intersection> xs = i.mbrIntersections;
	// std::vector<std::unique_ptr<Intersection>> xs = i.mbrIntersections;
	Intersection hit = i.hit();
	// EXPECT_TRUE(hit.checkEqual(xs[1]));
	EXPECT_TRUE(hit.checkEqual(*i.mbrIntersections[1].get()));
};

TEST_F(IntersectionTest, PrecomputeIntersectionState) {
	Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
	Sphere s = Sphere();
	// Intersection i = Intersection(4, std::make_unique<Sphere>(s));
	// Intersection i = Intersection(4, new Sphere(s));
	// IntersectionState is = i.getState(r);
	Intersections i = Intersections(4, new Sphere(s));
	IntersectionState is = i.hit().getState(r, i.mbrIntersections);
	EXPECT_TRUE(varComp.checkFloat(is.mbrTime, i.hit().mbrTime));
	EXPECT_TRUE(is.mbrObject->checkEqual(*i.hit().mbrObject.get()));
	EXPECT_TRUE(varComp.checkTuple(is.mbrPoint, Point(0,0,-1)));
	EXPECT_TRUE(varComp.checkTuple(is.mbrEye, Vector(0,0,-1)));
	EXPECT_TRUE(varComp.checkTuple(is.mbrNormal, Vector(0,0,-1)));
};

TEST_F(IntersectionTest, PrecomputeIntersectionStateInteriorHitFalse) {
	Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
	Sphere s = Sphere();
	// Intersection i = Intersection(4, std::make_unique<Sphere>(s));
	// Intersection i = Intersection(4, new Sphere (s));
	// IntersectionState is = i.getState(r);
	Intersections i = Intersections(4, new Sphere (s));
	IntersectionState is = i.hit().getState(r, i.mbrIntersections);
	EXPECT_FALSE(is.mbrInside);
}

TEST_F(IntersectionTest, PrecomputeIntersectionStateInteriorHitTrue) {
	Ray r = Ray(Point(0,0,0), Vector(0,0,1));
	Sphere s = Sphere();
	// Intersection i = Intersection(1, std::make_unique<Sphere>(s));
	// Intersection i = Intersection(1, new Sphere(s));
	Intersections i = Intersections(1, new Sphere(s));
	// IntersectionState is = i.getState(r);
	IntersectionState is = i.hit().getState(r, i.mbrIntersections);
	EXPECT_TRUE(varComp.checkTuple(is.mbrPoint, Point(0,0,1)));
	EXPECT_TRUE(varComp.checkTuple(is.mbrEye, Vector(0,0,-1)));
	EXPECT_TRUE(is.mbrInside);
	EXPECT_TRUE(varComp.checkTuple(is.mbrNormal, Vector(0,0,-1)));
}

TEST_F(IntersectionTest, HitShouldOffsetPoint) {
	Ray varRay = Ray(Point(0,0,-5), Vector(0,0,1));
	Sphere varSphere = Sphere();
	varSphere.setTransform(TranslationMatrix(0,0,1));
	// Intersection varIntersection = Intersection(5, std::make_unique<Sphere>(varSphere));
	// Intersection varIntersection = Intersection(5, new Sphere(varSphere));
	Intersections varIntersection = Intersections(5, new Sphere(varSphere));
	// IntersectionState varIs = varIntersection.getState(varRay);
	IntersectionState varIs = varIntersection.hit().getState(varRay, varIntersection.mbrIntersections);
	EXPECT_TRUE(varIs.mbrOverPoint.mbrZ < -getEpsilon()/2);
	EXPECT_TRUE(varIs.mbrPoint.mbrZ > varIs.mbrOverPoint.mbrZ);
}

TEST_F(IntersectionTest, ReflectionIntersectionState)
{
    Plane varObj = Plane();
    Ray varRay = Ray(Point(0,1,-1), Vector(0,-sqrt(2)/2, sqrt(2)/2));
	// Intersection varIx = Intersection(sqrt(2), new Plane(varObj));
	Intersections varIx = Intersections(sqrt(2), new Plane(varObj));
    // IntersectionState varIs = varIx.getState(varRay);
    IntersectionState varIs = varIx.hit().getState(varRay, varIx.mbrIntersections);
    EXPECT_TRUE(varComp.checkTuple(varIs.mbrReflect, Vector(0,sqrt(2)/2, sqrt(2)/2)));
}

TEST_F(IntersectionTest, RefractiveIndex) {
	SphereGlass varSphereA = SphereGlass();
	varSphereA.setTransform(ScalingMatrix(2,2,2));
	varSphereA.mbrMaterial->mbrRefractiveIndex = 1.5;
	SphereGlass varSphereB = SphereGlass();
	varSphereB.setTransform(TranslationMatrix(0,0,-0.25));
	varSphereB.mbrMaterial->mbrRefractiveIndex = 2.0;
	SphereGlass varSphereC = SphereGlass();
	varSphereC.setTransform(TranslationMatrix(0,0,0.25));
	varSphereC.mbrMaterial->mbrRefractiveIndex = 2.5;
	Ray argRay = Ray(Point(0,0,-4), Vector(0,0,1));
	Intersections varIs = Intersections();
	varIs.intersect(2, new SphereGlass(varSphereA));
	varIs.intersect(2.75, new SphereGlass(varSphereB));
	varIs.intersect(3.25, new SphereGlass(varSphereC));
	varIs.intersect(4.75, new SphereGlass(varSphereB));
	varIs.intersect(5.25, new SphereGlass(varSphereC));
	varIs.intersect(6, new SphereGlass(varSphereA));
	// IntersectionState varIx0 = varIs.mbrIntersections[0]->getState(argRay, varIs);
	// EXPECT_TRUE(varComp.checkFloat(varIx0.mbrRefractiveIndexOne, 1.0));
	// EXPECT_TRUE(varComp.checkFloat(varIx0.mbrRefractiveIndexTwo, 1.5));
	// IntersectionState varIx1 = varIs.mbrIntersections[1]->getState(argRay, varIs);
	// EXPECT_TRUE(varComp.checkFloat(varIx1.mbrRefractiveIndexOne, 1.5));
	// EXPECT_TRUE(varComp.checkFloat(varIx1.mbrRefractiveIndexTwo, 2.0));
	// IntersectionState varIx2 = varIs.mbrIntersections[2]->getState(argRay, varIs);
	// EXPECT_TRUE(varComp.checkFloat(varIx2.mbrRefractiveIndexOne, 2.0));
	// EXPECT_TRUE(varComp.checkFloat(varIx2.mbrRefractiveIndexTwo, 2.5));
	// IntersectionState varIx3 = varIs.mbrIntersections[3]->getState(argRay, varIs);
	// EXPECT_TRUE(varComp.checkFloat(varIx3.mbrRefractiveIndexOne, 2.5));
	// EXPECT_TRUE(varComp.checkFloat(varIx3.mbrRefractiveIndexTwo, 2.5));
	// IntersectionState varIx4 = varIs.mbrIntersections[4]->getState(argRay, varIs);
	// EXPECT_TRUE(varComp.checkFloat(varIx4.mbrRefractiveIndexOne, 2.5));
	// EXPECT_TRUE(varComp.checkFloat(varIx4.mbrRefractiveIndexTwo, 1.5));
	// IntersectionState varIx5 = varIs.mbrIntersections[5]->getState(argRay, varIs);
	// EXPECT_TRUE(varComp.checkFloat(varIx5.mbrRefractiveIndexOne, 1.5));
	// EXPECT_TRUE(varComp.checkFloat(varIx5.mbrRefractiveIndexTwo, 1.0));
	IntersectionState varIx0 = varIs.mbrIntersections[0]->getState(argRay, varIs.mbrIntersections);
	EXPECT_TRUE(varComp.checkFloat(varIx0.mbrRefractiveIndexOne, 1.0));
	EXPECT_TRUE(varComp.checkFloat(varIx0.mbrRefractiveIndexTwo, 1.5));
	IntersectionState varIx1 = varIs.mbrIntersections[1]->getState(argRay, varIs.mbrIntersections);
	EXPECT_TRUE(varComp.checkFloat(varIx1.mbrRefractiveIndexOne, 1.5));
	EXPECT_TRUE(varComp.checkFloat(varIx1.mbrRefractiveIndexTwo, 2.0));
	IntersectionState varIx2 = varIs.mbrIntersections[2]->getState(argRay, varIs.mbrIntersections);
	EXPECT_TRUE(varComp.checkFloat(varIx2.mbrRefractiveIndexOne, 2.0));
	EXPECT_TRUE(varComp.checkFloat(varIx2.mbrRefractiveIndexTwo, 2.5));
	IntersectionState varIx3 = varIs.mbrIntersections[3]->getState(argRay, varIs.mbrIntersections);
	EXPECT_TRUE(varComp.checkFloat(varIx3.mbrRefractiveIndexOne, 2.5));
	EXPECT_TRUE(varComp.checkFloat(varIx3.mbrRefractiveIndexTwo, 2.5));
	IntersectionState varIx4 = varIs.mbrIntersections[4]->getState(argRay, varIs.mbrIntersections);
	EXPECT_TRUE(varComp.checkFloat(varIx4.mbrRefractiveIndexOne, 2.5));
	EXPECT_TRUE(varComp.checkFloat(varIx4.mbrRefractiveIndexTwo, 1.5));
	IntersectionState varIx5 = varIs.mbrIntersections[5]->getState(argRay, varIs.mbrIntersections);
	EXPECT_TRUE(varComp.checkFloat(varIx5.mbrRefractiveIndexOne, 1.5));
	EXPECT_TRUE(varComp.checkFloat(varIx5.mbrRefractiveIndexTwo, 1.0));
};

TEST_F(IntersectionTest, UnderPointUnderSurfaceByEpsilon)
{
    Ray varRay = Ray(Point(0,0,-5), Vector(0,0,1));
	SphereGlass varObj = SphereGlass();
	varObj.setTransform(TranslationMatrix(0,0,1));
	Intersections varIx = Intersections(5, new SphereGlass(varObj));
    IntersectionState varIs = varIx.hit().getState(varRay, varIx.mbrIntersections);
    EXPECT_TRUE(varIs.mbrUnderPoint.mbrZ > getEpsilon()/2);
    EXPECT_TRUE(varIs.mbrPoint.mbrZ < varIs.mbrUnderPoint.mbrZ);
}