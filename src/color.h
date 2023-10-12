#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "tuple.h"
#include <string>

class Color : public Tuple {
public:
	double mbrRed;
	double mbrGreen;
	double mbrBlue;
	Color();
	Color(double red, double green, double blue);
	Color operator+(const Color &argOther);
	Color operator-(const Color &argOther);
	Color operator*(float x);
	Color operator*(const Color &argOther);
	bool checkEqual(const Color &other) const;
	void renderConsole() const;
};

#endif