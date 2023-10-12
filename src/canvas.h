#pragma once
#ifndef CANVAS_H
#define CANVAS_H

class Color;
#include <vector>
#include <string>

class Canvas {
public:
	int mbrWidth;
	int mbrHeight;
	std::vector<std::vector<Color>> mbrGrid;
	Canvas(int width, int height);
	Color getPixel(int x, int y);
	std::string getPPM();
	bool isClean();
	bool inBounds(int x, int y);
	void setPixel(int x, int y, Color c);
	void fill(Color x);
	void save();
};

#endif