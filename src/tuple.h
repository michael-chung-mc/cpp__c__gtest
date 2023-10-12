#pragma once
#ifndef TUPLE_H
#define TUPLE_H

#include <string>

class Tuple {
public:
	double mbrX;
	double mbrY;
	double mbrZ;
	double mbrW;
	Tuple();
	Tuple(double argx, double argy, double argz, double argw);
	Tuple(const Tuple &argOther);
	Tuple& operator=(const Tuple &argOther);
	Tuple operator-();
	Tuple operator*(double multiple);
	Tuple operator/(double multiple);
	Tuple operator+(const Tuple &argOther);
	Tuple operator-(const Tuple &argOther);
	virtual void add(const Tuple &argOther);
	// virtual Tuple add(const Tuple &argOther);
	Tuple subtract(const Tuple &argOther) const;
	virtual Tuple negate();
	virtual double magnitude() const;
	const double dot(const Tuple &argOther) const;
	Tuple reflect(Tuple normal);
	bool checkEqual(const Tuple &argOther);
	virtual void renderConsole() const;
};

class Vector : public Tuple {
public:
	Vector();
	Vector(double argx, double argy, double argz);
	Vector operator-();
	Vector operator+(const Tuple &argOther);
	const Vector operator*(double multiple) const;
	Vector subtract(const Tuple &argOther) const;
	Vector normalize();
	Vector cross(const Vector &argOther);
	Vector reflect(Vector normal);
};

class Point : public Tuple {
public:
	Point();
	Point(double argx, double argy, double argz);
	Point operator+(const Tuple &argOther);
	Vector operator-(const Point &argOther);
	Point subtract(const Tuple &argOther);
};

#endif