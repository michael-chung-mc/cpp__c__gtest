#pragma once
#ifndef FORM_H
#define FORM_H

#include "tuple.h"
#include "matrix.h"
#include "material.h"
#include "ray.h"
class Intersections;
#include <vector>

class Form {
public:
	Point mbrOrigin;
	double mbrRadius;
	std::unique_ptr<Matrix> mbrTransform;
	std::unique_ptr<Matrix> mbrTransformInverse;
	std::unique_ptr<Material> mbrMaterial;
	Ray mbrObjectRay;
	Form();
	Form(const Form& other);
	Form(Form&& other) noexcept;
	virtual ~Form();
	Form& operator=(const Form other);
	Form& operator=(Form&& other) noexcept;
	virtual Intersections getIntersections(Ray argRay);
	virtual Intersections getIntersectionsLocal(Ray argRay);
	virtual bool checkEqual(Form other);
	virtual Vector getNormal(Point argPoint);
	virtual Vector getNormalLocal(Point argPoint);
	Color getColor(const PointSource &argLighting, const Point &argPosition, const Vector &argEye, const Vector &argNormal, bool argInShadow);
	// Color getColorShaded(const PointSource &argLighting, const Point &argPosition, const Vector &argEye, const Vector &argNormal, bool argInShadow);
	Color getColorLocal(Point argPosition);
	void setTransform(const Matrix &argMatrix);
	void setMaterial(const Material &argMaterial);
	void renderConsole() const;
};

class Sphere : public Form {
public:
	Sphere();
	bool checkEqual(Form other) override;
	// Intersections getIntersections(Ray argRay) override;
	Intersections getIntersectionsLocal(Ray argRay) override;
	Vector getNormalLocal(Point argPoint) override;
};

class SphereGlass : public Sphere {
public:
	SphereGlass();
};

class Plane : public Form {
public:
	Plane();
	// Intersections getIntersections(Ray argRay) override;
	Intersections getIntersectionsLocal(Ray argRay) override;
	Vector getNormalLocal(Point argPoint) override;
};

#endif