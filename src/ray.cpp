#include "ray.h"
#include "tuple.h"
#include "matrix.h"
#include "comparinator.h"
#include <iostream>

Ray::Ray()
{
	this->mbrOrigin = Point(0,0,0);
	this->mbrDirection = Vector(0,0,0);
}

Ray::Ray(Point origin, Vector direction)
{
	this->mbrOrigin = origin;
	//std::cout << this->origin.x << std::endl;
	this->mbrDirection = direction;
}
Ray::Ray(const Ray& argOther) {
	this->mbrOrigin = argOther.mbrOrigin;
	this->mbrDirection = argOther.mbrDirection;
}
Ray& Ray::operator=(const Ray& argOther) {
	if (this == &argOther) { return *this; }
	this->mbrOrigin = argOther.mbrOrigin;
	this->mbrDirection = argOther.mbrDirection;
	return *this;
}
Point Ray::getPosition(double time)
{
	// std::cout << "Ray::getPosition()";
	// std::cout << " + Ray::mbrDirection(x:" << mbrDirection.mbrX << ",y:" << mbrDirection.mbrY << ",z:" << mbrDirection.mbrZ << ",w:" << mbrDirection.mbrW;
	// std::cout << " * " << time << std::endl;
	Vector varDelta = mbrDirection * time;
	// std::cout << "+ Ray::varDelta(x:" << varDelta.mbrX << ",y:" << varDelta.mbrY << ",z:" << varDelta.mbrZ << ",w:" << varDelta.mbrW << std::endl;
	// std::cout << "+ Ray::mbOrigin(x:" << mbrOrigin.mbrX << ",y:" << mbrOrigin.mbrY << ",z:" << mbrOrigin.mbrZ << ",w:" << mbrOrigin.mbrW << std::endl;
	Point varRes = mbrOrigin + varDelta;
	// return mbrOrigin + mbrDirection * time;
	// std::cout << "Ray::getPosition()->varRes(x:" << varRes.mbrX << ",y:" << varRes.mbrY << ",z:" << varRes.mbrZ << ",w:" << varRes.mbrW << std::endl;
	return varRes;
}
bool Ray::checkEqual(Ray other)
{
	Comparinator varComp = Comparinator();
	return varComp.checkTuple(mbrOrigin, other.mbrOrigin) && varComp.checkTuple(mbrDirection, other.mbrDirection);
}
Ray Ray::transform(Matrix matrix)
{
	return Ray(matrix * this->mbrOrigin, matrix * mbrDirection);
}
Ray Ray::transform(TranslationMatrix matrix)
{
	return Ray(matrix * this->mbrOrigin, matrix * mbrDirection);
}
Ray Ray::transform(ScalingMatrix matrix)
{
	return Ray(matrix * this->mbrOrigin, matrix * mbrDirection);
}
void Ray::renderConsole() const {
    std::cout << "Ray::renderConsole()";
    std::cout << "Ray::renderConsole()::mbrOrigin(";
	mbrOrigin.renderConsole();
    std::cout << "Ray::renderConsole()::mbrDirection(";
	mbrDirection.renderConsole();
}