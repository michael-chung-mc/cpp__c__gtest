#include "intersection.h"
#include "form.h"
#include "ray.h"
#include "tuple.h"
#include "pch.h"
#include <algorithm>

IntersectionState::IntersectionState() {
	mbrTime = 0;
	mbrObject = std::make_unique<Form>();
	mbrPoint = Point();
	mbrEye = Vector();
	mbrNormal = Vector();
	mbrInside = false;
	mbrUnderPoint = Point();
	mbrReflect = Vector();
	mbrOverPoint = Point();
	mbrRefractiveIndexOne = 0.0;
	mbrRefractiveIndexTwo = 0.0;
}
IntersectionState::IntersectionState(const IntersectionState &argOther) {
	mbrTime = argOther.mbrTime;
	setObject(argOther.mbrObject.get());
	mbrPoint = argOther.mbrPoint;
	mbrEye = argOther.mbrEye;
	mbrNormal = argOther.mbrNormal;
	mbrInside = argOther.mbrInside;
	mbrOverPoint = argOther.mbrOverPoint;
	mbrReflect = argOther.mbrReflect;
	mbrOverPoint = argOther.mbrOverPoint;
	mbrRefractiveIndexOne = argOther.mbrRefractiveIndexOne;
	mbrRefractiveIndexTwo = argOther.mbrRefractiveIndexTwo;
}
IntersectionState::IntersectionState( IntersectionState &&argOther) noexcept {
	mbrTime = argOther.mbrTime;
	mbrObject = std::move(argOther.mbrObject);
	argOther.mbrObject = nullptr;
	mbrPoint = argOther.mbrPoint;
	mbrEye = argOther.mbrEye;
	mbrNormal = argOther.mbrNormal;
	mbrInside = argOther.mbrInside;
	mbrOverPoint = argOther.mbrOverPoint;
	mbrReflect = argOther.mbrReflect;
	mbrOverPoint = argOther.mbrOverPoint;
	mbrRefractiveIndexOne = argOther.mbrRefractiveIndexOne;
	mbrRefractiveIndexTwo = argOther.mbrRefractiveIndexTwo;
}
IntersectionState& IntersectionState::operator=(const IntersectionState &argOther) {
	if (this == &argOther) return *this;
	mbrTime = argOther.mbrTime;
	setObject(argOther.mbrObject.get());
	mbrPoint = argOther.mbrPoint;
	mbrEye = argOther.mbrEye;
	mbrNormal = argOther.mbrNormal;
	mbrInside = argOther.mbrInside;
	mbrOverPoint = argOther.mbrOverPoint;
	mbrReflect = argOther.mbrReflect;
	mbrOverPoint = argOther.mbrOverPoint;
	mbrRefractiveIndexOne = argOther.mbrRefractiveIndexOne;
	mbrRefractiveIndexTwo = argOther.mbrRefractiveIndexTwo;
	return *this;
}
IntersectionState& IntersectionState::operator=(IntersectionState &&argOther) noexcept {
	if (this == &argOther) return *this;
	mbrTime = argOther.mbrTime;
	mbrObject = std::move(argOther.mbrObject);
	argOther.mbrObject = nullptr;
	mbrPoint = argOther.mbrPoint;
	mbrEye = argOther.mbrEye;
	mbrNormal = argOther.mbrNormal;
	mbrInside = argOther.mbrInside;
	mbrOverPoint = argOther.mbrOverPoint;
	mbrReflect = argOther.mbrReflect;
	mbrOverPoint = argOther.mbrOverPoint;
	mbrRefractiveIndexOne = argOther.mbrRefractiveIndexOne;
	mbrRefractiveIndexTwo = argOther.mbrRefractiveIndexTwo;
	return *this;
}
void IntersectionState::setObject(Form* argObject) {
    if (Sphere *varSphere = dynamic_cast<Sphere *>(argObject))
    {
        mbrObject = std::make_unique<Sphere>(*varSphere);
    }
    else if (SphereGlass *varSphere = dynamic_cast<SphereGlass *>(argObject))
    {
        mbrObject = std::make_unique<SphereGlass>(*varSphere);
    }
    else if (Plane *varPlane = dynamic_cast<Plane *>(argObject))
    {
        mbrObject = std::make_unique<Plane>(*varPlane);
    }
    else {
        mbrObject = std::make_unique<Form>(*argObject);
    }
}
void IntersectionState::renderConsole() const {
	std::cout << "IntersectionState::renderConsole()" << std::endl;
	std::cout << "IntersectionState::mbrTime: " << mbrTime << std::endl;
	std::cout << "IntersectionState::mbrObject: ";
	mbrObject->renderConsole();
	std::cout << "IntersectionState::mbrPoint: ";
	mbrPoint.renderConsole();
	std::cout << "IntersectionState::mbrEye: ";
	mbrEye.renderConsole();
	std::cout << "IntersectionState::mbrNormal: ";
	mbrNormal.renderConsole();
	std::cout << "IntersectionState::mbrInside: " << mbrInside << std::endl;
	std::cout << "IntersectionState::mbrOverPoint: ";
	mbrOverPoint.renderConsole();
	std::cout << "IntersectionState::mbrReflect: ";
	mbrReflect.renderConsole();
}

Intersection::Intersection()
{
	mbrObject = std::make_unique<Form>();
	mbrTime = 0;
	mbrExists = true;
}
Intersection::Intersection(double time, Form *s)
{
	setObject(s);
	this->mbrTime = time;
	mbrExists = true;
}
// Intersection::Intersection(double time, std::unique_ptr<Form> s)
// {
// 	setObject(s.get());
// 	this->mbrTime = time;
// 	mbrExists = true;
// }
Intersection::Intersection(const Intersection &argOther) {
	setObject(argOther.mbrObject.get());
	mbrTime = argOther.mbrTime;
	mbrExists = argOther.mbrExists;
}
Intersection::Intersection(Intersection &&argOther) noexcept {
	mbrObject = std::move(argOther.mbrObject);
	argOther.mbrObject = nullptr;
	mbrTime = argOther.mbrTime;
	mbrExists = argOther.mbrExists;
}
Intersection& Intersection::operator=(const Intersection &argOther){
	if (this == &argOther) return *this;
	setObject(argOther.mbrObject.get());
	mbrTime = argOther.mbrTime;
	mbrExists = argOther.mbrExists;
	return *this;
}
Intersection& Intersection::operator=(Intersection &&argOther) noexcept {
	if (this == &argOther) return *this;
	mbrObject = std::move(argOther.mbrObject);
	argOther.mbrObject = nullptr;
	mbrTime = argOther.mbrTime;
	mbrExists = argOther.mbrExists;
	return *this;
}
bool Intersection::checkEqual(Intersection other)
{
	return mbrTime == other.mbrTime && mbrObject->checkEqual(*other.mbrObject.get());
}
// IntersectionState Intersection::getState(Ray argRay)
// {
// 	IntersectionState is = IntersectionState();
// 	is.mbrTime = mbrTime;
// 	is.setObject(mbrObject.get());
// 	is.mbrPoint = argRay.getPosition(is.mbrTime);
// 	is.mbrEye = -(argRay.mbrDirection);
// 	is.mbrNormal = is.mbrObject->getNormal(is.mbrPoint);
// 	if (is.mbrNormal.dot(is.mbrEye) < 0) {
// 		is.mbrInside = true;
// 		is.mbrNormal = -is.mbrNormal;
// 	}
// 	else {
// 		is.mbrInside = false;
// 	}
// 	is.mbrOverPoint = is.mbrPoint + is.mbrNormal * getEpsilon();
// 	is.mbrReflect = argRay.mbrDirection.reflect(is.mbrNormal);
// 	return is;
// }
// IntersectionState Intersection::getState(Ray argRay, const Intersections &argIntersections)
// {
// 	IntersectionState is = IntersectionState();
// 	is.mbrTime = mbrTime;
// 	is.setObject(mbrObject.get());
// 	is.mbrPoint = argRay.getPosition(is.mbrTime);
// 	is.mbrEye = -(argRay.mbrDirection);
// 	is.mbrNormal = is.mbrObject->getNormal(is.mbrPoint);
// 	if (is.mbrNormal.dot(is.mbrEye) < 0) {
// 		is.mbrInside = true;
// 		is.mbrNormal = -is.mbrNormal;
// 	}
// 	else {
// 		is.mbrInside = false;
// 	}
// 	is.mbrOverPoint = is.mbrPoint + is.mbrNormal * getEpsilon();
// 	is.mbrReflect = argRay.mbrDirection.reflect(is.mbrNormal);
// 	std::vector<Form*> varHitObjects;
// 	// Intersection varHit = argIntersections.hit();
// 	Intersection varHit = Intersection(is.mbrTime,mbrObject.get());
// 	for (int i = 0; i < argIntersections.mbrIntersections.size(); ++i) {
// 		if (varHit.checkEqual(*argIntersections.mbrIntersections[i].get())) {
// 			if (varHitObjects.size() == 0) { is.mbrRefractiveIndexOne = 1.0; }
// 			else { is.mbrRefractiveIndexOne = varHitObjects.back()->mbrMaterial->mbrRefractiveIndex; }
// 		}
// 		int varFound = -1;
// 		std::vector<Form*>::iterator varItr = varHitObjects.begin();
// 		for (; varItr != varHitObjects.end(); ++varItr)
// 		{
// 			if (*varItr == varHit.mbrObject.get()) {
// 				varHitObjects.erase(varItr);
// 				varFound = 1;
// 				break;
// 			}
// 			// if (varHitObjects[j] == varHit.mbrObject.get())
// 			// {
// 			// 	varFound = j;
// 			// 	break;
// 			// }
// 		}
// 		// if (varFound > 0) {varHitObjects.erase(varHitObjects.begin()+varFound);}
// 		// else {varHitObjects.push_back(varHit.mbrObject.get());}
// 		if (varFound < 0) {varHitObjects.push_back(varHit.mbrObject.get());}
// 		if (varHit.checkEqual(*argIntersections.mbrIntersections[i].get())) {
// 			if (varHitObjects.empty()) { is.mbrRefractiveIndexTwo = 1.0; }
// 			else { is.mbrRefractiveIndexTwo = varHitObjects.back()->mbrMaterial->mbrRefractiveIndex; }
// 			break;
// 		}
// 	}
// 	return is;
// }
IntersectionState Intersection::getState(Ray argRay, const std::vector<std::unique_ptr<Intersection>> &argIntersections)
{
	IntersectionState is = IntersectionState();
	is.mbrTime = mbrTime;
	// std::cout << "Intersection::getState()::is.mbrTime=(" << is.mbrTime << std::endl;
	is.setObject(mbrObject.get());
	is.mbrPoint = argRay.getPosition(is.mbrTime);
	// std::cout << "Intersection::getState()::is.mbrPoint=(x:" << is.mbrPoint.mbrX << ",y:" << is.mbrPoint.mbrY << ",z:" << is.mbrPoint.mbrZ << ",w:" << is.mbrPoint.mbrW << std::endl;
	is.mbrEye = -(argRay.mbrDirection);
	is.mbrNormal = is.mbrObject->getNormal(is.mbrPoint);
	if (is.mbrNormal.dot(is.mbrEye) < 0) {
		is.mbrInside = true;
		is.mbrNormal = -is.mbrNormal;
	}
	else {
		is.mbrInside = false;
	}
	is.mbrOverPoint = is.mbrPoint + (is.mbrNormal * getEpsilon());
	// std::cout << "Intersection::getState()::is.mbrOverPoint=(x:" << is.mbrOverPoint.mbrX << ",y:" << is.mbrOverPoint.mbrY << ",z:" << is.mbrOverPoint.mbrZ << ",w:" << is.mbrOverPoint.mbrW;
	// std::cout << " = Intersection::getState()::is.mbrNormal=(x:" << is.mbrNormal.mbrX << ",y:" << is.mbrNormal.mbrY << ",z:" << is.mbrNormal.mbrZ << ",w:" << is.mbrNormal.mbrW << std::endl;
	is.mbrReflect = argRay.mbrDirection.reflect(is.mbrNormal);
	std::vector<Form*> varHitObjects;
	// Intersection varHit = argIntersections.hit();
	Intersection varHit = Intersection(is.mbrTime,mbrObject.get());
	// std::cout << "Intersection::getState()::hit.mbrTime(" << varHit.mbrTime << std::endl;
	for (int i = 0; i < argIntersections.size(); ++i) {
		// std::cout << "Intersection::getState()::argIntersections[i].get()->mbrTime(" << argIntersections[i].get()->mbrTime << std::endl;
		// std::cout << "Intersection::getState()::argIntersections[i].get()->mbrObject->mbrMaterial->mbrRefractiveIndex(" << argIntersections[i].get()->mbrObject->mbrMaterial->mbrRefractiveIndex << std::endl;
		if (varHit.checkEqual(*argIntersections[i].get())) {
			if (varHitObjects.size() == 0) { is.mbrRefractiveIndexOne = 1.0; }
			else { is.mbrRefractiveIndexOne = varHitObjects.back()->mbrMaterial->mbrRefractiveIndex; }
		}
		int varFound = -1;
		std::vector<Form*>::iterator varItr = varHitObjects.begin();
		for (; varItr != varHitObjects.end(); ++varItr)
		{
			if ((*varItr)->checkEqual(*argIntersections[i]->mbrObject.get())) {
				// std::cout << "Intersection::getState()::erase(argIntersections[i]->mbrObject.get()(" << argIntersections[i]->mbrObject.get()->mbrMaterial->mbrRefractiveIndex << std::endl;
				varHitObjects.erase(varItr);
				varFound = 1;
				break;
			}
			// if (varHitObjects[j] == varHit.mbrObject.get())
			// {
			// 	varFound = j;
			// 	break;
			// }
		}
		// if (varFound > 0) {varHitObjects.erase(varHitObjects.begin()+varFound);}
		// else {varHitObjects.push_back(varHit.mbrObject.get());}
		if (varFound < 0) {
			varHitObjects.push_back(argIntersections[i]->mbrObject.get());
			// std::cout << "Intersection::getState()::varHitObjects.back()->mbrMaterial->mbrRefractiveIndex(" << varHitObjects.back()->mbrMaterial->mbrRefractiveIndex << std::endl;
		}
		if (varHit.checkEqual(*argIntersections[i].get())) {
			if (varHitObjects.empty()) { is.mbrRefractiveIndexTwo = 1.0; }
			else { is.mbrRefractiveIndexTwo = varHitObjects.back()->mbrMaterial->mbrRefractiveIndex; }
			break;
		}
		// std::cout << "Intersection::getState()::is.mbrRefractiveIndexOne" << is.mbrRefractiveIndexOne << std::endl;
		// std::cout << "Intersection::getState()::is.mbrRefractiveIndexTwo" << is.mbrRefractiveIndexTwo << std::endl;
	}
	// std::cout << "Intersection::getState()::is.mbrRefractiveIndexOne" << is.mbrRefractiveIndexOne << std::endl;
	// std::cout << "Intersection::getState()::is.mbrRefractiveIndexTwo" << is.mbrRefractiveIndexTwo << std::endl;
	// is.mbrUnderPoint = is.mbrPoint.subtract(is.mbrNormal * getEpsilon());
	is.mbrUnderPoint = is.mbrPoint.subtract(is.mbrNormal * getEpsilon());
	return is;
}
void Intersection::setObject(Form* argObject) {
    if (Sphere *varSphere = dynamic_cast<Sphere *>(argObject))
    {
        mbrObject = std::make_unique<Sphere>(*varSphere);
    }
    else if (SphereGlass *varSphere = dynamic_cast<SphereGlass *>(argObject))
    {
        mbrObject = std::make_unique<SphereGlass>(*varSphere);
    }
    else if (Plane *varPlane = dynamic_cast<Plane *>(argObject))
    {
        mbrObject = std::make_unique<Plane>(*varPlane);
    }
    else {
        mbrObject = std::make_unique<Form>(*argObject);
    }
}

Intersections::Intersections()
{
	//Intersection i = Intersection(0, Sphere());
	//this->intersections.push_back(i);
}
Intersections::Intersections(const Intersections& other)
{
	mbrIntersections.clear();
	for (int i = 0; i < other.mbrIntersections.size(); ++i)
	{
		setIntersection(other.mbrIntersections[i].get());
		// Intersection varIs = other.mbrIntersections[i];
		// mbrIntersections.push_back(varIs);
	}
	//this->mbrIntersections = other.mbrIntersections;
}
Intersections::Intersections(double t, Form *s)
{
	setIntersection(t, s);
	// Intersection i = Intersection(t,std::make_unique<Form>(*s.get()));
	// mbrIntersections.push_back(i);
}
// Intersections::Intersections(double t, std::unique_ptr<Form> s)
// {
// 	setIntersection(t, s.get());
// 	// Intersection i = Intersection(t,std::make_unique<Form>(*s.get()));
// 	// mbrIntersections.push_back(i);
// }
Intersections& Intersections::operator=(const Intersections other)
{
	if (this == &other) return *this;
	mbrIntersections.clear();
	for (int i = 0; i < other.mbrIntersections.size(); ++i)
	{
		setIntersection(other.mbrIntersections[i].get());
		// Intersection varIs = other.mbrIntersections[i];
		// mbrIntersections.push_back(varIs);
	}
	// this->mbrIntersections = other.mbrIntersections;
	return *this;
}
// void Intersections::intersect(double t, std::unique_ptr<Form> argObject)
// {
// 	auto funcComp = [&](const std::unique_ptr<Intersection> &argA, const std::unique_ptr<Intersection> &argB) -> bool {
// 		return argA->mbrTime < argB->mbrTime;
// 	};
// 	setIntersection(t, argObject.get());
// 	//mbrIntersections.push_back(Intersection(t, std::make_unique<Form>(*argObject)));
//     sort(mbrIntersections.begin(), mbrIntersections.end(), funcComp);
// }
void Intersections::intersect(double t, Form* argObject)
{
	auto funcComp = [&](const std::unique_ptr<Intersection> &argA, const std::unique_ptr<Intersection> &argB) -> bool {
		return argA->mbrTime < argB->mbrTime;
	};
	setIntersection(t, argObject);
	//mbrIntersections.push_back(Intersection(t, std::make_unique<Form>(*argObject)));
    sort(mbrIntersections.begin(), mbrIntersections.end(), funcComp);
}
Intersection Intersections::hit() const
{
	int index = -1;
	for (int i = 0; i < mbrIntersections.size(); ++i)
	{
		if ((mbrIntersections[i]->mbrTime > 0)
			&& ((index < 0) || (mbrIntersections[i]->mbrTime <= mbrIntersections[index]->mbrTime)))
		{
			index = i;
			break;
		}
	}
	if (index < 0) {
		//std::cout << "hit missed" << std::endl;
		Intersection varIx = Intersection();
		varIx.mbrExists = false;
		return varIx;
	}
	else {
		//std::cout << "hit" << std::endl;
		return *mbrIntersections[index].get();
	}
}
void Intersections::setIntersection(Intersection* argIx) {
	mbrIntersections.push_back(std::make_unique<Intersection>(*argIx));
}
void Intersections::setIntersection(double t, Form* argObject) {
	mbrIntersections.push_back(std::make_unique<Intersection>(t, argObject));
}