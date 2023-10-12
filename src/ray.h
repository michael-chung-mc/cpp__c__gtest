#pragma once
#ifndef RAY_H
#define RAY_H

#include "tuple.h"
#include "matrix.h"

class Ray {
public:
	Point mbrOrigin;
	Vector mbrDirection;
	Ray();
	Ray(Point origin, Vector direction);
	Ray(const Ray& argOther);
	Ray& operator=(const Ray& argOther);
	Point getPosition(double time);
	bool checkEqual(Ray other);
	Ray transform(Matrix matrix);
	Ray transform(TranslationMatrix matrix);
	Ray transform(ScalingMatrix matrix);
	void renderConsole() const;
};

#endif