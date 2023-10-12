#include "tuple.h"
#include "comparinator.h"
#include <cmath>
#include <iostream>

class Tuple;
class Point;
class Vector;

Tuple::Tuple()
{
	mbrX = 0;
	mbrY = 0;
	mbrZ = 0;
	mbrW = 0;
}
Tuple::Tuple(double argx, double argy, double argz, double argw)
{
	mbrX = argx;
	mbrY = argy;
	mbrZ = argz;
	mbrW = argw;
};
Tuple::Tuple(const Tuple &argOther) {
	mbrX = argOther.mbrX;
	mbrY = argOther.mbrY;
	mbrZ = argOther.mbrZ;
	mbrW = argOther.mbrW;
}
Tuple& Tuple::operator=(const Tuple &argOther) {
	if (this==&argOther) {return *this;}
	mbrX = argOther.mbrX;
	mbrY = argOther.mbrY;
	mbrZ = argOther.mbrZ;
	mbrW = argOther.mbrW;
	return *this;
}
Tuple Tuple::operator-()
{
	return Tuple(-mbrX, -mbrY, -mbrZ, -mbrW);
}

Tuple Tuple::operator*(double multiple)
{
	return Tuple(mbrX * multiple, mbrY * multiple, mbrZ * multiple, mbrW * multiple);
}
Tuple Tuple::operator/(double multiple)
{
	return Tuple(mbrX / multiple, mbrY / multiple, mbrZ / multiple, mbrW / multiple);
}
Tuple Tuple::operator+(const Tuple &argOther)
{
	return Tuple(argOther.mbrX + mbrX, argOther.mbrY + mbrY, argOther.mbrZ + mbrZ, argOther.mbrW + mbrW);;
}
Tuple Tuple::operator-(const Tuple &argOther)
{
	return Tuple(argOther.mbrX - mbrX, argOther.mbrY - mbrY, argOther.mbrZ - mbrZ, argOther.mbrW - mbrW);;
}
void Tuple::add(const Tuple &argOther)
{
	mbrX += argOther.mbrX;
	mbrY += argOther.mbrY;
	mbrZ += argOther.mbrZ;
	mbrW += argOther.mbrW;
};
// Tuple Tuple::add(const Tuple &argOther)
// {
// 	return Tuple(argOther.mbrX + mbrX, argOther.mbrY + mbrY, argOther.mbrZ + mbrZ, argOther.mbrW + mbrW);
// };
Tuple Tuple::subtract(const Tuple &argOther) const
{
	return Tuple(mbrX - argOther.mbrX, mbrY - argOther.mbrY, mbrZ - argOther.mbrZ, mbrW - argOther.mbrW);
};
Tuple Tuple::negate()
{
	return Tuple(-mbrX, -mbrY, -mbrZ, -mbrW);
};
double Tuple::magnitude() const
{
	return sqrt(pow(mbrX, 2) + pow(mbrY, 2) + pow(mbrZ, 2) + pow(mbrW, 2));
}
const double Tuple::dot(const Tuple &argOther) const
{
	return ((mbrX * argOther.mbrX) + (mbrY * argOther.mbrY) + (mbrZ * argOther.mbrZ) + (mbrW * argOther.mbrW));
};
Tuple Tuple::reflect(Tuple normal)
{
	return subtract(normal * 2.0 * dot(normal));
}
bool Tuple::checkEqual(const Tuple &argOther)
{
	Comparinator varComp = Comparinator();
	return varComp.checkTuple(*this, argOther);
}
void Tuple::renderConsole() const {
    std::cout << "Tuple::renderConsole() -> (";
    std::cout << " mbrX:" << mbrX;
    std::cout << ", mbrY:" << mbrY;
    std::cout << ", mbrZ:" << mbrZ;
    std::cout << ", mbrW:" << mbrW << std::endl;
}

Point::Point() : Tuple(0.0, 0.0, 0.0, 1.0) {};
Point::Point(double argx, double argy, double argz) : Tuple(argx, argy, argz, 1.0) {};
Point Point::operator+(const Tuple &argOther)
{
	return Point(argOther.mbrX + mbrX, argOther.mbrY + mbrY, argOther.mbrZ + mbrZ);;
}
Vector Point::operator-(const Point &argOther)
{
	return Vector(mbrX-argOther.mbrX, mbrY-argOther.mbrY, mbrZ-argOther.mbrZ);;
}
Point Point::subtract(const Tuple &argOther)
{
	return Point(mbrX - argOther.mbrX, mbrY - argOther.mbrY, mbrZ - argOther.mbrZ);
}

Vector::Vector() : Tuple(0.0, 0.0, 0.0, 0.0) {};
Vector::Vector(double argx, double argy, double argz) : Tuple(argx, argy, argz, 0.0) {};
Vector Vector::operator+(const Tuple &argOther)
{
	return Vector(argOther.mbrX + mbrX, argOther.mbrY + mbrY, argOther.mbrZ + mbrZ);;
}
Vector Vector::operator-()
{
	return Vector(-mbrX, -mbrY, -mbrZ);
}
const Vector Vector::operator*(double multiple) const
{
	return Vector(mbrX * multiple, mbrY * multiple, mbrZ * multiple);
}
Vector Vector::subtract(const Tuple &argOther) const
{
	return Vector(mbrX - argOther.mbrX, mbrY - argOther.mbrY, mbrZ - argOther.mbrZ);
}
Vector Vector::normalize()
{
	// double varX = magnitude() == 0 ? 0 : mbrX / magnitude();
	// double varY = magnitude() == 0 ? 0 : mbrY / magnitude();
	// double varZ = magnitude() == 0 ? 0 : mbrZ / magnitude();
	// return Vector(varX, varY, varZ);
	Comparinator varComp = Comparinator();
	double varMagnitude = magnitude();
	return varComp.checkFloat(varMagnitude, 0) ? Vector(0.0,0.0,0.0) : Vector(mbrX/varMagnitude, mbrY/varMagnitude, mbrZ/varMagnitude);
};
Vector Vector::cross(const Vector &argOther)
{
	return Vector(mbrY * argOther.mbrZ - mbrZ * argOther.mbrY, mbrZ * argOther.mbrX - mbrX * argOther.mbrZ, mbrX * argOther.mbrY - mbrY * argOther.mbrX);
};
Vector Vector::reflect(Vector normal)
{
	return subtract(normal * 2.0 * dot(normal));
}