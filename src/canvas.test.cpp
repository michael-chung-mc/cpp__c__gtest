#include "canvas.h"
#include "comparinator.h"
#include "color.h"
#include "pch.h"

class CanvasTest : public ::testing::Test {
protected:
    Comparinator ce;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        ce = Comparinator();
    }
	//void TearDown() override { }
};

TEST_F(CanvasTest, Canary)
{
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(CanvasTest, CanvasInit)
{
	//Scenario: Creating a canvas
	//Given c ← canvas(10, 20)
	//Then c.width = 10
	//And c.height = 20
	//And every pixel of c is color(0, 0, 0)
	Canvas c = Canvas(10,20);
	EXPECT_EQ(c.mbrWidth, 10);
	EXPECT_EQ(c.mbrHeight, 20);
	EXPECT_TRUE(c.isClean());
}

TEST_F(CanvasTest, CanvasSetColor)
{
	//Scenario: Writing pixels to a canvas
	//Given c ← canvas(10, 20)
	//And red ← color(1, 0, 0)
	//When write_pixel(c, 2, 3, red)
	//Then pixel_at(c, 2, 3) = red
	Canvas c = Canvas(10, 20);
	Color red = Color(1, 0, 0);
	c.setPixel(2, 3, red);
	Color test = c.getPixel(2, 3);
	EXPECT_TRUE(test.checkEqual(red));
}

TEST_F(CanvasTest, CanvasPPM)
{
	//Scenario: Constructing the PPM header
	//And c1 ← color(1.5, 0, 0)
	//And c2 ← color(0, 0.5, 0)
	//And c3 ← color(-0.5, 0, 1)
	//When write_pixel(c, 0, 0, c1)
	//And write_pixel(c, 2, 1, c2)
	//And write_pixel(c, 4, 2, c3)
	//And ppm ← canvas_to_ppm(c)
	Canvas c = Canvas(5, 3);
	EXPECT_TRUE(c.isClean());
	Color c1 = Color(1.5, 0, 0);
	Color c2 = Color(0, 0.5, 0);
	Color c3 = Color(-.5, 0, 1);
	c.setPixel(0, 0, c1);
	c.setPixel(2, 1, c2);
	c.setPixel(4, 2, c3);
	std::string ppm = c.getPPM();
	std::string cppm = "P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
	EXPECT_EQ(ppm, cppm);
}

TEST_F(CanvasTest, CanvasPPMLength)
{
	//Scenario: Splitting long lines in PPM files
	//Given c ← canvas(10, 2)
	//When every pixel of c is set to color(1, 0.8, 0.6)
	//And ppm ← canvas_to_ppm(c)
	Canvas c = Canvas(10, 2);
	Color c1 = Color(1, 0.8, 0.6);
	c.fill(c1);
	std::string ppm = c.getPPM();
	std::string cppm = "P3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n";
	EXPECT_EQ(ppm, cppm);
}