#include "world.h"
#include "comparinator.h"
#include "color.h"
#include "form.h"
#include "intersection.h"
#include "pattern.h"
#include "ray.h"
#include "pch.h"

class WorldTest : public ::testing::Test {
protected:
	DefaultWorld varDefaultWorld;
    Comparinator varComp;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        varDefaultWorld = DefaultWorld();
        varComp = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(WorldTest, CanaryTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
};

TEST_F(WorldTest, WorldEmptyCtor) {
	World w = World();
    EXPECT_EQ(w.mbrObjects.size(), 0);
    EXPECT_EQ(w.mbrLights.size(), 0);
};

TEST_F(WorldTest, WorldDefaultCtor) {
    PointSource l = PointSource(Point(-10,10,-10), Color(1,1,1));
    Sphere s = Sphere();
    s.setMaterial(Material());
    s.mbrMaterial->mbrColor = Color (0.8,1.0,0.6);
    s.mbrMaterial->mbrDiffuse = 0.7;
    s.mbrMaterial->mbrSpecular = 0.2;
    Sphere t = Sphere();
    // t.setTransform(*(ScalingMatrix(0.5,0.5,0.5) * IdentityMatrix(4,4)));
    t.setTransform(ScalingMatrix(0.5,0.5,0.5) * IdentityMatrix(4,4));
    EXPECT_TRUE(l.checkEqual(varDefaultWorld.mbrLights[0]));
    EXPECT_TRUE(varDefaultWorld.mbrObjects[0]->checkEqual(s));
    EXPECT_TRUE(varDefaultWorld.mbrObjects[1]->checkEqual(t));
};

TEST_F(WorldTest, WorldRayIntersect) {
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Intersections xs = varDefaultWorld.getIntersect(r);
    // EXPECT_EQ(xs.mbrIntersections.size(), 4);
    // EXPECT_EQ(xs.mbrIntersections[0].mbrTime, 4);
    // EXPECT_EQ(xs.mbrIntersections[1].mbrTime, 4.5);
    // EXPECT_EQ(xs.mbrIntersections[2].mbrTime, 5.5);
    // EXPECT_EQ(xs.mbrIntersections[3].mbrTime, 6);
    EXPECT_EQ(xs.mbrIntersections.size(), 4);
    EXPECT_EQ(xs.mbrIntersections[0]->mbrTime, 4);
    EXPECT_EQ(xs.mbrIntersections[1]->mbrTime, 4.5);
    EXPECT_EQ(xs.mbrIntersections[2]->mbrTime, 5.5);
    EXPECT_EQ(xs.mbrIntersections[3]->mbrTime, 6);
};

TEST_F(WorldTest, WorldIntersectionShading) {
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Form obj = *varDefaultWorld.mbrObjects[0].get();
    Sphere s = Sphere();
    s.setMaterial(Material());
    s.mbrMaterial->mbrColor = Color (0.8,1.0,0.6);
    s.mbrMaterial->mbrDiffuse = 0.7;
    s.mbrMaterial->mbrSpecular = 0.2;
    EXPECT_TRUE(obj.checkEqual(s));
    // Intersection i = Intersection(4,std::make_unique<Form>(obj));
    // Intersection i = Intersection(4,new Form(obj));
    Intersections varIx = Intersections(4,new Form(obj));
    // EXPECT_TRUE(varIx.mbrObject->checkEqual(obj));
    IntersectionState is = varIx.hit().getState(r, varIx.mbrIntersections);
    Color c = varDefaultWorld.getColorShaded(is);
    Color expectedColor = Color(0.38066, 0.47583, 0.2855);
    EXPECT_TRUE(c.checkEqual(expectedColor));
};

TEST_F(WorldTest, WorldIntersectionInteriorShading) {
    varDefaultWorld.mbrLights[0] = PointSource(Point(0,0.25,0), Color(1,1,1));
    Ray r = Ray(Point(0,0,0), Vector(0,0,1));
    Form obj = *varDefaultWorld.mbrObjects[1].get();
    // Intersection i = Intersection(0.5,std::make_unique<Form>(obj));
    // Intersection i = Intersection(0.5,new Form(obj));
    Intersections varIx = Intersections(0.5,new Form(obj));
    IntersectionState is = varIx.hit().getState(r, varIx.mbrIntersections);
    // Color c = varDefaultWorld.getColorShaded(is);
    Color c = varDefaultWorld.getColorLighting(is);
    Color expectedColor = Color(0.90498, 0.90498, 0.90498);
    EXPECT_TRUE(c.checkEqual(expectedColor));
};

TEST_F(WorldTest, WorldColorMissIsBlack) {
    Ray r = Ray(Point(0,0,-5), Vector(0,1,0));
    Color c = varDefaultWorld.getColor(r);
    Color expectedColor = Color(0,0,0);
    EXPECT_TRUE(c.checkEqual(expectedColor));
};

TEST_F(WorldTest, WorldColorHit) {
    Ray r = Ray(Point(0,0,-5), Vector(0,0,1));
    Color c = varDefaultWorld.getColor(r);
    Color expectedColor = Color(0.38066, 0.47583, 0.2855);
    EXPECT_TRUE(c.checkEqual(expectedColor));
};

TEST_F(WorldTest, WorldColorHitInsideInnerSphere) {
    varDefaultWorld.mbrObjects[0]->mbrMaterial->mbrAmbient = 1;
    varDefaultWorld.mbrObjects[1]->mbrMaterial->mbrAmbient = 1;
    Ray r = Ray(Point(0,0,0.75), Vector(0,0,-1));
    Color c = varDefaultWorld.getColor(r);
    Color expectedColor = varDefaultWorld.mbrObjects[1]->mbrMaterial->mbrColor;
    EXPECT_TRUE(c.checkEqual(expectedColor));
};

TEST_F(WorldTest, NoShadowIfObjectCollinearWithPointLight) {
    Point varPoint = Point(0,10,0);
    EXPECT_FALSE(varDefaultWorld.checkShadowed(varPoint));
};

TEST_F(WorldTest, ShadowIfObjectBetweenPointLight) {
    Point varPoint = Point(10,-10,10);
    EXPECT_TRUE(varDefaultWorld.checkShadowed(varPoint));
};

TEST_F(WorldTest, NoShadowIfObjectBehindLight) {
    Point varPoint = Point(-20,20,-20);
    EXPECT_FALSE(varDefaultWorld.checkShadowed(varPoint));
};

TEST_F(WorldTest, NoShadowIfObjectBehindPoint) {
    Point varPoint = Point(-2,2,-2);
    EXPECT_FALSE(varDefaultWorld.checkShadowed(varPoint));
};

TEST_F(WorldTest, ShadeWithShadowIntersections) {
	World varWorld = World();
    PointSource varLight = PointSource(Point(0,0,-10), Color(1,1,1));
    varWorld.setLight(varLight);
    Sphere varS1 = Sphere();
    varWorld.setObject(new Sphere(varS1));
    // varWorld.setObject(std::make_unique<Sphere>(varS1));
    Sphere varS2 = Sphere();
    varS2.setTransform(TranslationMatrix(0,0,10));
    varWorld.setObject(new Sphere(varS2));
    // varWorld.setObject(std::make_unique<Sphere>(varS2));
    Ray varRay = Ray(Point(0,0,5), Vector(0,0,1));
    // Intersection varIx = Intersection(4,std::make_unique<Sphere>(varS2));
    // Intersection varIx = Intersection(4,new Sphere(varS2));
    Intersections varIx = Intersections(4, new Sphere(varS2));
    IntersectionState varIs = varIx.hit().getState(varRay, varIx.mbrIntersections);
    Color varClr = varWorld.getColorShaded(varIs);
    Color varExpectedClr = Color(0.1,0.1,0.1);
    EXPECT_TRUE(varExpectedClr.checkEqual(varClr));
};

TEST_F(WorldTest, NonReflectiveReflectedColor) {
    DefaultWorld varWorld = DefaultWorld();
    Ray varRay = Ray(Point(0,0,0), Vector(0,0,1));
    Form *varObj = varWorld.mbrObjects[1].get();
    varObj->mbrMaterial->mbrAmbient = 1;
    // Intersection varIx = Intersection(1, varObj);
    Intersections varIx = Intersections(1, varObj);
    IntersectionState varIs = varIx.hit().getState(varRay, varIx.mbrIntersections);
    Color varColor = varWorld.getColorReflect(varIs);
    EXPECT_TRUE(varColor.checkEqual(Color(0,0,0)));
};

TEST_F(WorldTest, ReflectiveReflectedColor) {
    DefaultWorld varWorld = DefaultWorld();
    Plane *varPlane = new Plane();
    varPlane->mbrMaterial->mbrReflective = 0.5;
    varPlane->setTransform(TranslationMatrix(0,-1,0));
    varWorld.setObject(varPlane);
    Ray varRay = Ray(Point(0,0,-3), Vector(0,-sqrt(2)/2,sqrt(2)/2));
    // Intersection varIx = Intersection(sqrt(2), varPlane);
    Intersections varIx = Intersections(sqrt(2), varPlane);
    IntersectionState varIs = varIx.hit().getState(varRay, varIx.mbrIntersections);
    Color varColor = varWorld.getColorReflect(varIs);
    EXPECT_TRUE(varColor.checkEqual(Color(0.19032,0.2379,0.14274)));
    // Color varExpectedColor = Color(0.19033,0.23791, 0.14274);
    // EXPECT_TRUE(varExpectedColor.checkEqual(varColor));
};

TEST_F(WorldTest, ReflectiveShading) {
    DefaultWorld varWorld = DefaultWorld();
    Plane *varPlane = new Plane();
    varPlane->mbrMaterial.get()->mbrReflective = 0.5;
    varPlane->setTransform(TranslationMatrix(0,-1,0));
    varWorld.setObject(varPlane);
    Ray varRay = Ray(Point(0,0,-3), Vector(0,-sqrt(2)/2,sqrt(2)/2));
    // Intersection varIx = Intersection(sqrt(2), varPlane);
    Intersections varIx = Intersections(sqrt(2), varPlane);
    IntersectionState varIs = varIx.hit().getState(varRay, varIx.mbrIntersections);
    // std::cout << "expect -> t=1.41421 c(.6864,.6864,.6864) + r(.1903, .2379, .1428)" << std::endl;
    Color varColor = varWorld.getColorShaded(varIs);
    EXPECT_TRUE(varColor.checkEqual(Color(0.87677, 0.92436, 0.82918)));
};

TEST_F(WorldTest, InfiniteReflectionsBetweenMirrors) {
    World varWorld = World();
    varWorld.setLight(PointSource(Point(0,0,0), Color(1,1,1)));
    Plane *varLower = new Plane();
    varLower->mbrMaterial.get()->mbrReflective = 1;
    varLower->setTransform(TranslationMatrix(0,-1,0));
    varWorld.setObject(varLower);
    Plane *varUpper = new Plane();
    varUpper->mbrMaterial.get()->mbrReflective = 1;
    varUpper->setTransform(TranslationMatrix(0,1,0));
    varWorld.setObject(varUpper);
    Ray varRay = Ray(Point(0,0,0), Vector(0,1,0));
    Color varColor = varWorld.getColor(varRay);
    EXPECT_NO_FATAL_FAILURE();
};

TEST_F(WorldTest, InfiniteReflectionsAtMaxDepth) {
    DefaultWorld varWorld = DefaultWorld();
    Plane *varPlane = new Plane();
    varPlane->mbrMaterial->mbrReflective = 0.5;
    varPlane->setTransform(TranslationMatrix(0,-1,0));
    varWorld.setObject(varPlane);
    Ray varRay = Ray(Point(0,0,-3), Vector(0,-sqrt(2)/2,sqrt(2)/2));
    Intersections varIx = Intersections(sqrt(2), varPlane);
    // Intersection varIx = Intersection(sqrt(2), varPlane);
    IntersectionState varIs = varIx.hit().getState(varRay, varIx.mbrIntersections);
    Color varColor = varWorld.getColorReflect(varIs, 0);
    EXPECT_TRUE(varColor.checkEqual(Color(0,0,0)));
};

TEST_F(WorldTest, RefractiveWithOpaqueIsBlack) {
    DefaultWorld varWorld = DefaultWorld();
    Form *varObj = varWorld.mbrObjects[0].get();
    Ray varRay = Ray(Point(0,0,-5), Vector(0,0,1));
    Intersections varIx = Intersections();
    varIx.intersect(4, varObj);
    varIx.intersect(4, varObj);
    IntersectionState varIs = varIx.mbrIntersections[0]->getState(varRay, varIx.mbrIntersections);
    Color varColor = varWorld.getColorRefracted(varIs, 5);
    EXPECT_TRUE(varColor.checkEqual(Color(0,0,0)));
};

TEST_F(WorldTest, InfiniteRefractionIsBlack) {
    DefaultWorld varWorld = DefaultWorld();
    Form *varObj = varWorld.mbrObjects[0].get();
    varObj->mbrMaterial->mbrTransparency = 1.0;
    varObj->mbrMaterial->mbrTransparency = 1.5;
    Ray varRay = Ray(Point(0,0,-5), Vector(0,0,1));
    Intersections varIx = Intersections();
    varIx.intersect(4, varObj);
    varIx.intersect(4, varObj);
    IntersectionState varIs = varIx.mbrIntersections[0]->getState(varRay, varIx.mbrIntersections);
    Color varColor = varWorld.getColorRefracted(varIs, 0);
    EXPECT_TRUE(varColor.checkEqual(Color(0,0,0)));
};

TEST_F(WorldTest, TotalInternalRefractionIsBlack) {
    DefaultWorld varWorld = DefaultWorld();
    Form *varObj = varWorld.mbrObjects[0].get();
    varObj->mbrMaterial->mbrTransparency = 1.0;
    varObj->mbrMaterial->mbrRefractiveIndex = 1.5;
    Ray varRay = Ray(Point(0,0,sqrt(2)/2), Vector(0,1,0));
    Intersections varIx = Intersections();
    varIx.intersect(-sqrt(2)/2, varObj);
    varIx.intersect(sqrt(2)/2, varObj);
    IntersectionState varIs = varIx.mbrIntersections[1]->getState(varRay, varIx.mbrIntersections);
    Color varColor = varWorld.getColorRefracted(varIs, 5);
    EXPECT_TRUE(varColor.checkEqual(Color(0,0,0)));
};

TEST_F(WorldTest, RefractionBasic) {
    DefaultWorld varWorld = DefaultWorld();
    varWorld.mbrObjects[0].get()->mbrMaterial->mbrAmbient = 1.0;
    // varWorld.mbrObjects[0].get()->mbrMaterial->setPattern(new Pattern(Color(0,0,0), Color(1,1,1)));
    varWorld.mbrObjects[0].get()->mbrMaterial->setPattern(std::make_unique<Pattern>(Color(0,0,0), Color(1,1,1)));
    varWorld.mbrObjects[0].get()->mbrMaterial->mbrPattern->getColorLocal(Point(0,0,0));
    varWorld.mbrObjects[1].get()->mbrMaterial->mbrTransparency = 1.0;
    varWorld.mbrObjects[1].get()->mbrMaterial->mbrRefractiveIndex = 1.5;
    Ray varRay = Ray(Point(0,0,0.1), Vector(0,1,0));
    Intersections varIx = Intersections();
    varIx.intersect(-0.9899, varWorld.mbrObjects[0].get());
    varIx.intersect(-0.4899, varWorld.mbrObjects[1].get());
    varIx.intersect(0.4899, varWorld.mbrObjects[1].get());
    varIx.intersect(0.9899, varWorld.mbrObjects[0].get());
    IntersectionState varIs = varIx.mbrIntersections[2]->getState(varRay, varIx.mbrIntersections);
    Color varColor = varWorld.getColorRefracted(varIs, 5);
    // World::getColorRefracted()::varNToN = n1/n2 = 1.5/1 = 1.5
    // World::getColorRefracted()::varCosThetaI = (0,-1,0,0)dot(0,-0.979796, -0.19999,0) = 0.979796073
    // World::getColorRefracted()::varSinThetaTSquared = 1.5^2 * (1-0.979796^2) = 0.08999
    // World::getColorRefracted()::varCosThetaT = sqrt(1-0.08999) = 0.9539
    // World::getColorRefracted()::varRefractDirection = (0,-0.979796, -0.19999,0) * (1.5*0.979796-0.9539) - (0,-1,0,0) * 1.5 = (0,0.99466,-0.1031,0)
    // World::getColorRefracted()::varRefractRay = ((0,0.4899,0.10000,0),(0,0.99466,-0.1031,0))
    // World::getColorRefracted()::getcolor() * mbrTransparency(1)
    // World::getcolor()::hit::mbrTime=(0.511)
    // World::getcolor()::hit::mbrObject::mbrColor=(0.8000,1,0.59999)
    // World::getcolor()::hit::mbrPoint=(0,.9988,0.047219,1)
    // World::getcolor()::hit::mbrOverPoint=(0,0.9987,0.0472,1)
    // World::getcolor()::hit::mbrUnderPoint=(0,0.99889,0.04721,1)
    // World::getcolor()::hit::mbrEye=(0,-.9946,0.1031,0)
    // World::getcolor()::hit::mbrNormal=(0,-0.99888,-.047219,0)
    // World::getcolor()::hit::mbrReflect=(0,-0.9804,-.1965,0)
    // World::getcolor()::hit::mbrRefractiveIndexOne=(1)
    // World::getcolor()::hit::mbrRefractiveIndexTwo=(1)
    // World::getcolorShaded()::argIxState.mbrOverPoint=(0,0.9988,0.0472,1)
    // World::getcolorShaded()::mbrRefractiveIndexTwo=(0)varInShadow=(true)
    // Material::getColor(...)::varColor=mbrColor=(0,0.998885,0.472194
    // Material::getColor(...)::varShade=(0,0.998885,0.472194
    // Material::getColor(...)::varResAmbient=(0,0.998885,0.472194
    // Form::getColor(...)::varRes=(0,0.998885,0.472194
    // World::getColorShaded()::varDiffuse=(0,0.998885,0.472194
    // World::getColorShaded()::varReflect=(0,0,0)
    // World::getColorShaded()::varRes=(0,0.998885,0.472194
    EXPECT_TRUE(varColor.checkEqual(Color(0, 0.99888, 0.04725)));
};

TEST_F(WorldTest, RefractionTransparentColor) {
    DefaultWorld varWorld = DefaultWorld();
    std::unique_ptr<Plane> varFloor = std::make_unique<Plane>();
    varFloor->setTransform(TranslationMatrix(0,-1,0));
    varFloor->mbrMaterial->mbrTransparency = 0.5;
    varFloor->mbrMaterial->mbrRefractiveIndex = 1.5;
    varWorld.setObject(varFloor.get());
    std::unique_ptr<Sphere> varSphere = std::make_unique<Sphere>();
    varSphere->setTransform(TranslationMatrix(0,-3.5,-.5));
    varSphere->mbrMaterial->mbrColor=Color(1,0,0);
    varSphere->mbrMaterial->mbrAmbient = 0.5;
    varWorld.setObject(varSphere.get());
    Ray varRay = Ray(Point(0,0,-3), Vector(0,-sqrt(2)/2,sqrt(2)/2));
    Intersections varIx = Intersections(sqrt(2), varFloor.get());
    IntersectionState varIs = varIx.mbrIntersections[0]->getState(varRay, varIx.mbrIntersections);
    Color varColor = varWorld.getColorShaded(varIs, 5);
    EXPECT_TRUE(varColor.checkEqual(Color(0.93642, 0.68642, 0.68642)));
};