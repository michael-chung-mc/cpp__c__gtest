#include "color.h"
#include "comparinator.h"
#include "tuple.h"
#include <iostream>

Color::Color()
{
	mbrRed = 0;
	mbrGreen = 0;
	mbrBlue = 0;
}
Color::Color(double red, double green, double blue)
{
	mbrRed = red;
	mbrGreen = green;
	mbrBlue = blue;
}

Color Color::operator+(const Color &argOther) {
	Color varRes = Color(mbrRed + argOther.mbrRed, mbrGreen + argOther.mbrGreen, mbrBlue + argOther.mbrBlue);
	// return Color(mbrRed + argOther.mbrRed, mbrGreen + argOther.mbrGreen, mbrBlue + argOther.mbrBlue);
	// std::cout << "Color::operator+-> varRes(r:" << varRes.mbrRed << ",g:" << varRes.mbrGreen << ",b:" << varRes.mbrBlue;
	// std::cout << " = this(r:" << mbrRed << ",g:" << mbrGreen << ",b:" << mbrBlue;
	// std::cout << " + this(r:" << argOther.mbrRed << ",g:" << argOther.mbrGreen << ",b:" << argOther.mbrBlue << std::endl;
	return varRes;
}
Color Color::operator-(const Color &argOther) {
	return Color(mbrRed - argOther.mbrRed, mbrGreen - argOther.mbrGreen, mbrBlue - argOther.mbrBlue);
}
Color Color::operator*(float x) {
	return Color(mbrRed * x, mbrGreen * x, mbrBlue * x);
}
Color Color::operator*(const Color &argOther) {
	return Color(mbrRed * argOther.mbrRed, mbrGreen * argOther.mbrGreen, mbrBlue * argOther.mbrBlue);
}
bool Color::checkEqual(const Color &other) const
{
	Comparinator ce = Comparinator();
	return ce.checkFloat(mbrRed,other.mbrRed) && ce.checkFloat(mbrGreen,other.mbrGreen) && ce.checkFloat(mbrBlue,other.mbrBlue);
}
void Color::renderConsole() const {
    std::cout << "Color::renderConsole::Color(";
    std::cout << "= mbrRed:" << mbrRed;
    std::cout << "= mbrGreen:" << mbrGreen;
    std::cout << "= mbrBlue:" << mbrBlue << std::endl;
}