#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "form.h"
#include "tuple.h"
class Ray;
#include <vector>

class IntersectionState {
public:
	double mbrTime;
	std::unique_ptr<Form> mbrObject;
	Point mbrPoint;
	Point mbrOverPoint;
	Point mbrUnderPoint;
	Vector mbrEye;
	Vector mbrNormal;
	Vector mbrReflect;
	bool mbrInside;
	double mbrRefractiveIndexOne;
	double mbrRefractiveIndexTwo;
	IntersectionState();
	IntersectionState(const IntersectionState &argOther);
	IntersectionState(IntersectionState &&argOther) noexcept;
	virtual ~IntersectionState() = default;
	IntersectionState& operator=(const IntersectionState &argOther);
	IntersectionState& operator=(IntersectionState &&argOther) noexcept;
    void setObject(Form* argObject);
	void renderConsole() const;
};

class Intersection {
public:
	bool mbrExists;
	double mbrTime;
	std::unique_ptr<Form> mbrObject;
	Intersection();
	Intersection(const Intersection &argOther);
	Intersection(Intersection &&argOther) noexcept;
	Intersection(double time, Form *s);
	// Intersection(double time, std::unique_ptr<Form> s);
	virtual ~Intersection() = default;
	Intersection& operator=(const Intersection &argOther);
	Intersection& operator=(Intersection &&argOther) noexcept;
	bool checkEqual(Intersection other);
	// IntersectionState getState(Ray argRay);
	// IntersectionState getState(Ray argRay, const Intersections &argIntersections);
	IntersectionState getState(Ray argRay, const std::vector<std::unique_ptr<Intersection>> &argIntersections);
    void setObject(Form* argObject);
};


class Intersections {
public:
    std::vector<std::unique_ptr<Intersection>> mbrIntersections;
	Intersections();
	Intersections(const Intersections& other);
	Intersections(double time, Form *s);
	// Intersections(double time, std::unique_ptr<Form> s);
	virtual ~Intersections() = default;
	Intersections& operator=(const Intersections other);
	void intersect(double time, Form* argObject);
	// void intersect(double t, std::unique_ptr<Form> argObject);
	Intersection hit() const;
	void setIntersection(Intersection* argIx);
    void setIntersection(double t, Form* argObject);
};

#endif