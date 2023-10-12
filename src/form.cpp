#include "form.h"
#include "comparinator.h"
#include "material.h"
#include "intersection.h"
#include "tuple.h"
#include "matrix.h"
#include "light.h"
#include "ray.h"
#include "pattern.h"
#include "pch.h"

Form::Form()
{
	mbrOrigin = Point(0, 0, 0);
	mbrRadius = 0;
	setTransform(std::make_unique<Matrix>(IdentityMatrix(4, 4)).get());
	mbrMaterial = std::make_unique<Material>(Material());
	mbrObjectRay = Ray();
}
Form::Form(const Form &other)
{
	mbrOrigin = other.mbrOrigin;
	mbrRadius = other.mbrRadius;
	// mbrTransform = std::make_unique<Matrix>(*other.mbrTransform.get());
	setTransform(*other.mbrTransform.get());
	setMaterial(*other.mbrMaterial.get());
	mbrObjectRay = other.mbrObjectRay;
}
Form::Form(Form&& other) noexcept {
	mbrOrigin = other.mbrOrigin;
	mbrRadius = other.mbrRadius;
	mbrTransform = std::move(other.mbrTransform);
	other.mbrTransform = nullptr;
	mbrTransformInverse = std::move(other.mbrTransformInverse);
	other.mbrTransformInverse = nullptr;
	mbrMaterial = std::move(other.mbrMaterial);
	other.mbrMaterial = nullptr;
	mbrObjectRay = other.mbrObjectRay;
}
Form::~Form()
{
}
bool Form::checkEqual(Form other)
{
	Comparinator ce = Comparinator();
	return ce.checkTuple(this->mbrOrigin, other.mbrOrigin) && mbrTransform->checkEqual(*other.mbrTransform) && mbrMaterial->checkEqual(*other.mbrMaterial) && mbrObjectRay.checkEqual(other.mbrObjectRay);
}
Form &Form::operator=(const Form other)
{
	if (this == &other) return *this;
	mbrOrigin = other.mbrOrigin;
	mbrRadius = other.mbrRadius;
	setTransform(*other.mbrTransform.get());
	setMaterial(*other.mbrMaterial.get());
	return *this;
}
Form &Form::operator=(Form&& other) noexcept
{
	if (this == &other) return *this;
	mbrOrigin = other.mbrOrigin;
	mbrRadius = other.mbrRadius;
	mbrTransform = std::move(other.mbrTransform);
	other.mbrTransform = nullptr;
	mbrTransformInverse = std::move(other.mbrTransformInverse);
	other.mbrTransformInverse = nullptr;
	mbrMaterial = std::move(other.mbrMaterial);
	other.mbrMaterial = nullptr;
	return *this;
}
Color Form::getColor(const PointSource &argLighting, const Point &argPosition, const Vector &argEye, const Vector &argNormal, bool argInShadow)
{
	// std::cout << "Form::getColor()" << std::endl;
	// Point varObjP = *(mbrTransform->invert()) * argPosition;
	Point varObjP = *(mbrTransformInverse.get()) * argPosition;
	// std::cout << "Form::getColor()::varObjP(x:" << varObjP.mbrX << ",y:" << varObjP.mbrY << ",z:" << varObjP.mbrZ << ",w:" << varObjP.mbrW << ")" << std::endl;
	// std::cout << "= inverse(mbrTransform(" << std::endl;
	// mbrTransform->renderConsole();
	// std::cout << "=" << std::endl;
	// mbrTransform->invert().renderConsole();
	// std::cout << " * argPosition(x:" << argPosition.mbrX << ",y:" << argPosition.mbrY << ",z:" << argPosition.mbrZ << ",w:" << argPosition.mbrW << std::endl;
	// Point varPatternP = *(mbrMaterial->mbrPattern->mbrTransform->invert()) * varObjP;
	Point varPatternP = *(mbrMaterial->mbrPattern->mbrTransformInverse.get()) * varObjP;
	// std::cout << "Form::getColor()::varPatternP(x:" << varPatternP.mbrX << ",y:" << varPatternP.mbrY << ",z:" << varPatternP.mbrZ << ",w:" << varPatternP.mbrW << ")" << std::endl;
	// std::cout << "= inverse(mbrTransform(" << std::endl;
	// mbrMaterial->mbrPattern->mbrTransform->renderConsole();
	// std::cout << "=" << std::endl;
	// mbrMaterial->mbrPattern->mbrTransform->invert().renderConsole();
	// std::cout << "* varObjP" << std::endl;
	Color varRes = mbrMaterial->getColor(argLighting, varPatternP, argEye, argNormal, argInShadow);
	// Color varRes = mbrMaterial->getColor(argLighting, argPosition, argEye, argNormal, argInShadow);
	// std::cout << "Form::getColor()->varRes(r:" << varRes.mbrRed << "g:" << varRes.mbrGreen << "b:" << varRes.mbrBlue << std::endl;
	return varRes;
	// return mbrMaterial->getColor(argLighting, varPatternP, argEye, argNormal, argInShadow);
}
// Color Form::getColorShaded(const PointSource &argLighting, const Point &argPosition, const Vector &argEye, const Vector &argNormal, bool argInShadow)
// {
// 	return mbrMaterial->getColor(argLighting, argPosition, argEye, argNormal, argInShadow);
// }
Color Form::getColorLocal(Point argPosition)
{
	// Point varObjP = *(mbrTransform->invert()) * argPosition;
	// Point varPatternP = *(mbrMaterial->mbrPattern->mbrTransform->invert()) * varObjP;
	Point varObjP = *(mbrTransformInverse.get()) * argPosition;
	Point varPatternP = *(mbrMaterial->mbrPattern->mbrTransformInverse) * varObjP;
	return mbrMaterial->mbrPattern->getColorLocal(varPatternP);
}
Intersections Form::getIntersections(Ray argRay)
{
    // std::cout << "default get intersections";
	// mbrObjectRay = argRay.transform(*(this->mbrTransform->invert()));
	mbrObjectRay = argRay.transform(*mbrTransformInverse.get());
	return getIntersectionsLocal(mbrObjectRay);
}
Intersections Form::getIntersectionsLocal(Ray argRay)
{
	return Intersections();
}
Vector Form::getNormal(Point argPoint)
{
	// Point varObjectPoint = *(mbrTransform->invert()) * argPoint;
	Point varObjectPoint = *mbrTransformInverse.get() * argPoint;
	Vector varObjectNormal = getNormalLocal(varObjectPoint);
	// Matrix varTransform = *(*this->mbrTransform->invert()).transpose();
	// Matrix varTransform = *(mbrTransformInverse->transpose());
	Matrix varTransform = mbrTransformInverse->transpose();
	Vector varWorldNormal = varTransform * varObjectNormal;
	varWorldNormal.mbrW = 0;
	return varWorldNormal.normalize();
}
Vector Form::getNormalLocal(Point argPoint)
{
	return Vector(argPoint.mbrX,argPoint.mbrY,argPoint.mbrZ);
}
void Form::setTransform(const Matrix &argMatrix)
{
	mbrTransform = std::make_unique<Matrix>(argMatrix);
	mbrTransformInverse = std::make_unique<Matrix>(argMatrix.getInverse());
}
void Form::setMaterial(const Material &argMaterial)
{
	mbrMaterial = std::make_unique<Material>(argMaterial);
}
void Form::renderConsole() const {
	std::cout << "Form::renderConsole()" << std::endl;
	std::cout << "Form::mbrOrigin: ";
	mbrOrigin.renderConsole();
	std::cout << "Form::mbrRadius: " << mbrRadius << std::endl;
	std::cout << "Form::mbrTransform:" << std::endl;
    mbrTransform->renderConsole();
	std::cout << "Form::mbrMaterial: ";
    mbrMaterial->renderConsole();
	std::cout << "Form::mbrObjectRay: ";
	mbrObjectRay.renderConsole();
}

Sphere::Sphere() : Form()
{
	mbrRadius = 1.0;
}
Intersections Sphere::getIntersectionsLocal(Ray argRay)
{
    // std::cout << "sphere get intersections";
	Intersections varIntersections;
	Vector sphereToRay = argRay.mbrOrigin - (Point(0, 0, 0));
	double a = argRay.mbrDirection.dot(argRay.mbrDirection);
	double b = 2 * argRay.mbrDirection.dot(sphereToRay);
	double c = sphereToRay.dot(sphereToRay) - 1;
	double discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return varIntersections;
	double intersectOne = (-b - sqrt(discriminant)) / (2 * a);
	double intersectTwo = (-b + sqrt(discriminant)) / (2 * a);
	// if (intersectOne < intersectTwo)
	// {
	// 	// varIntersections.intersect(intersectOne, std::make_unique<Sphere>(*this));
	// 	// varIntersections.intersect(intersectTwo, std::make_unique<Sphere>(*this));
	// 	varIntersections.intersect(intersectOne, this);
	// 	varIntersections.intersect(intersectTwo, this);
	// }
	// else
	// {
	// 	// varIntersections.intersect(intersectTwo, std::make_unique<Sphere>(*this));
	// 	// varIntersections.intersect(intersectOne, std::make_unique<Sphere>(*this));
	// 	varIntersections.intersect(intersectTwo, this);
	// 	varIntersections.intersect(intersectOne, this);
	// }
	varIntersections.intersect(intersectOne, this);
	varIntersections.intersect(intersectTwo, this);
	return varIntersections;
}
Vector Sphere::getNormalLocal(Point argPoint)
{
	// Point varObjectPoint = *(this->mbrTransform->invert()) * argPoint;
	Vector varObjectNormal = argPoint - this->mbrOrigin;
	return varObjectNormal.normalize();
}
// Vector Sphere::getNormal(Point argPoint)
// {
// 	// return (argPoint-origin).normalize();
// 	Point varObjectPoint = *(this->mbrTransform->invert()) * argPoint;
// 	Vector varObjectNormal = varObjectPoint - this->mbrOrigin;
// 	Matrix varTransform = *(*this->mbrTransform->invert()).transpose();
// 	Vector varWorldNormal = varTransform * varObjectNormal;
// 	varWorldNormal.mbrW = 0;
// 	return varWorldNormal.normalize();
// }
bool Sphere::checkEqual(Form other)
{
	Comparinator ce = Comparinator();
	return ce.checkTuple(mbrOrigin, other.mbrOrigin) && mbrRadius == other.mbrRadius && mbrTransform->checkEqual(*other.mbrTransform) && mbrMaterial->checkEqual(*other.mbrMaterial);
}

SphereGlass::SphereGlass() {
	mbrMaterial.get()->mbrTransparency = 1.0;
	mbrMaterial.get()->mbrRefractiveIndex = 1.5;
}

Plane::Plane() : Form() {
}
Vector Plane::getNormalLocal(Point argPoint)
{
	return Vector(0, 1, 0);
}
// Vector Plane::getNormal(Point argPoint)
// {
// 	return Vector(0, 1, 0);
// }
Intersections Plane::getIntersectionsLocal(Ray argRay)
{
    // std::cout << "plane get intersections";
	if (abs(argRay.mbrDirection.mbrY) <= getEpsilon())
	{
		return Intersections();
	}
	double varTime = -argRay.mbrOrigin.mbrY / argRay.mbrDirection.mbrY;
	// return Intersections(varTime, std::make_unique<Plane>(*this));
	return Intersections(varTime, this);
}