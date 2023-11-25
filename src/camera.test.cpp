#include "camera.h"
#include "comparinator.h"
#include "ray.h"
#include "world.h"
#include "canvas.h"
#include "pch.h"

class CameraTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(CameraTest, Canary)
{
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(CameraTest, CameraDefault)
{
	int varH = 160;
    int varV = 120;
    double varFOV = getPI()/2;
    IdentityMatrix varIdentity = IdentityMatrix(4,4);
    Camera varCamera = Camera(varH, varV, varFOV);
    EXPECT_EQ(varCamera.mbrCanvasHorizontal, varH);
    EXPECT_EQ(varCamera.mbrCanvasVertical, varV);
    EXPECT_TRUE(ce.checkFloat(varCamera.mbrFieldOfView, varFOV));
    EXPECT_TRUE(varIdentity.checkEqual(*varCamera.mbrTransform.get()));
}

TEST_F(CameraTest, CameraCanvasPixelSizeHorizontalGTVertical)
{
    Camera varCamera = Camera(200, 125, getPI()/2);
    EXPECT_TRUE(ce.checkFloat(varCamera.mbrPixelSquare, 0.01));
}

TEST_F(CameraTest, CameraCanvasPixelSizeVerticalGTHorizontal)
{
    Camera varCamera = Camera(125, 200, getPI()/2);
    EXPECT_TRUE(ce.checkFloat(varCamera.mbrPixelSquare, 0.01));
}

TEST_F(CameraTest, CameraRayCastToCanvasCenter)
{
    Camera varCamera = Camera(201, 101, getPI()/2);
    Ray varCast = varCamera.getRay(100,50);
    Point varExpectedOrigin = Point(0,0,0);
    Vector varExpectedDirection = Vector(0,0,-1);
    EXPECT_TRUE(ce.checkTuple(varCast.mbrOrigin, varExpectedOrigin));
    EXPECT_TRUE(ce.checkTuple(varCast.mbrDirection, varExpectedDirection));
}

TEST_F(CameraTest, CameraRayCastToCanvasCorner)
{
    Camera varCamera = Camera(201, 101, getPI()/2);
    Ray varCast = varCamera.getRay(0,0);
    Point varExpectedOrigin = Point(0,0,0);
    Vector varExpectedDirection = Vector(0.66519, 0.33259, -.66851);
    EXPECT_TRUE(ce.checkTuple(varCast.mbrOrigin, varExpectedOrigin));
    EXPECT_TRUE(ce.checkTuple(varCast.mbrDirection, varExpectedDirection));
}

TEST_F(CameraTest, TransformedCameraRayCastToCanvas)
{
    Camera varCamera = Camera(201, 101, getPI()/2);
    // varCamera.setTransform(YRotationMatrix(getPI()/4) * TranslationMatrix(0,-2,5));
    varCamera.setTransform(std::make_unique<Matrix>(YRotationMatrix(getPI()/4) * TranslationMatrix(0,-2,5)));
    Ray varCast = varCamera.getRay(100,50);
    Point varExpectedOrigin = Point(0,2,-5);
    Vector varExpectedDirection = Vector(sqrt(2)/2,0,-sqrt(2)/2);
    EXPECT_TRUE(ce.checkTuple(varCast.mbrOrigin, varExpectedOrigin));
    EXPECT_TRUE(ce.checkTuple(varCast.mbrDirection, varExpectedDirection));
}

TEST_F(CameraTest, CameraRenderDefaultWorld)
{
    DefaultWorld varWorld = DefaultWorld();
    Camera varCamera = Camera(11, 11, getPI()/2);
    // varCamera.setTransform(new ViewMatrix(Point(0,0,-5), Point(0,0,0), Vector(0,1,0)));
    varCamera.setTransform(std::make_unique<ViewMatrix>(Point(0,0,-5), Point(0,0,0), Vector(0,1,0)));
    Canvas varImg = varCamera.renderCanvas(varWorld);
    Color varExpectedColor = Color(0.38066, 0.47583, 0.2855);
    EXPECT_TRUE(varImg.getPixel(5,5).checkEqual(varExpectedColor));
}