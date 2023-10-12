#include "world.h"
#include "form.h"
#include "material.h"
#include "matrix.h"
#include "ray.h"
#include "comparinator.h"
#include "intersection.h"
#include <iostream>
#include <cmath>

World::World ()
{
    mbrObjects.clear();
}
World::World (const World &argOther)
{
    mbrObjects.clear();
    for (int i = 0; i < argOther.mbrObjects.size(); ++i)
    {
        setObject(argOther.mbrObjects[i].get());
        // mbrObjects.push_back(std::make_unique<Form>(*argOther.mbrObjects[i].get()));
    }
    mbrLights = argOther.mbrLights;
}
World& World::operator=(const World &argOther)
{
    if (this == &argOther) return *this;
    mbrObjects.clear();
    for (int i = 0; i < argOther.mbrObjects.size(); ++i)
    {
        setObject(argOther.mbrObjects[i].get());
        //mbrObjects.push_back(std::make_unique<Form>(*argOther.mbrObjects[i].get()));
    }
    mbrLights = argOther.mbrLights;
    return *this;
}
Intersections World::getIntersect(const Ray &argRay)
{
    Intersections hits = Intersections();
    for (int i = 0; i < mbrObjects.size(); ++i)
    {
        Intersections varIx = mbrObjects[i]->getIntersections(argRay);
        for (int j = 0; j < varIx.mbrIntersections.size(); ++j)
        {
            hits.intersect(varIx.mbrIntersections[j]->mbrTime, varIx.mbrIntersections[j]->mbrObject.get());
        }
    }
    return hits;
}
Color World::getColor(const Ray &r, int argLimit)
{
    // std::cout << "World::getColor( #:" << argLimit << " )" << std::endl;
    Intersections xs = getIntersect(r);
    Intersection hit = xs.hit();
    // if (!hit.mbrExists) return Color(50,205,50);
    if (!hit.mbrExists) return Color(0,0,0);
    IntersectionState is = hit.getState(r, xs.mbrIntersections);
    // std::cout << "World::getColor()::is.mbrPoint(x:" << is.mbrPoint.mbrX << ",y:" << is.mbrPoint.mbrY << ",z:" << is.mbrPoint.mbrZ << ",w:" << is.mbrPoint.mbrW << std::endl;
    // std::cout << "World::getColor()::is.mbrOverPoint(x:" << is.mbrOverPoint.mbrX << ",y:" << is.mbrOverPoint.mbrY << ",z:" << is.mbrOverPoint.mbrZ << ",w:" << is.mbrOverPoint.mbrW << std::endl;
    // std::cout << "World::getColor()::is.mbrEye(x:" << is.mbrEye.mbrX << ",y:" << is.mbrEye.mbrY << ",z:" << is.mbrEye.mbrZ << ",w:" << is.mbrEye.mbrW << std::endl;
    // std::cout << "World::getColor()::is.mbrNormal(x:" << is.mbrNormal.mbrX << ",y:" << is.mbrNormal.mbrY << ",z:" << is.mbrNormal.mbrZ << ",w:" << is.mbrNormal.mbrW << std::endl;
    return getColorShaded(is, argLimit);
}
Color World::getColorLighting(const IntersectionState &argIxState, int argLimit)
{
    if (argLimit < 1) return Color(0,0,0);
    bool varInShadow = checkShadowed(argIxState.mbrOverPoint);
    Color varShade = Color(0,0,0);
    for (int i = 0; i < mbrLights.size();++i)
    {
        varShade = varShade + argIxState.mbrObject->getColor(mbrLights[i], argIxState.mbrPoint, argIxState.mbrEye, argIxState.mbrNormal, varInShadow);
        // varShade = varShade + argIxState.mbrObject->getColor(mbrLights[i], argIxState.mbrOverPoint, argIxState.mbrEye, argIxState.mbrNormal, varInShadow);
    }
    return varShade;
}
Color World::getColorShaded(const IntersectionState &argIxState, int argLimit)
{
    // std::cout << "World::getColorShaded( #:" << argLimit << ", t: " << argIxState.mbrTime << " )" << std::endl;
    if (argLimit < 1) return Color(0,0,0);
    // std::cout << "World::getColorShaded()::argIxState.mbrPoint(x:" << argIxState.mbrPoint.mbrX << ",y:" << argIxState.mbrPoint.mbrY << ",z:" << argIxState.mbrPoint.mbrZ << ",w:" << argIxState.mbrPoint.mbrW << std::endl;
    // std::cout << "World::getColorShaded()::argIxState.mbrOverPoint(x:" << argIxState.mbrOverPoint.mbrX << ",y:" << argIxState.mbrOverPoint.mbrY << ",z:" << argIxState.mbrOverPoint.mbrZ << ",w:" << argIxState.mbrOverPoint.mbrW << std::endl;
    // std::cout << "World::getColorShaded()::argIxState.mbrEye(x:" << argIxState.mbrEye.mbrX << ",y:" << argIxState.mbrEye.mbrY << ",z:" << argIxState.mbrEye.mbrZ << ",w:" << argIxState.mbrEye.mbrW << std::endl;
    // std::cout << "World::getColorShaded()::argIxState.mbrNormal(x:" << argIxState.mbrNormal.mbrX << ",y:" << argIxState.mbrNormal.mbrY << ",z:" << argIxState.mbrNormal.mbrZ << ",w:" << argIxState.mbrNormal.mbrW << std::endl;
    // argIxState.renderConsole();
    bool varInShadow = checkShadowed(argIxState.mbrOverPoint);
    Color varDiffuse = Color(0,0,0);
    for (int i = 0; i < mbrLights.size();++i)
    {
        // varDiffuse = varDiffuse + argIxState.mbrObject->getColor(mbrLights[i], argIxState.mbrPoint, argIxState.mbrEye, argIxState.mbrNormal, varInShadow);
        varDiffuse = varDiffuse + argIxState.mbrObject->getColor(mbrLights[i], argIxState.mbrOverPoint, argIxState.mbrEye, argIxState.mbrNormal, varInShadow);
    }
    // std::cout << "World::getColorShaded()::Diffuse(r:" << varDiffuse.mbrRed << ",g:" << varDiffuse.mbrGreen << ",b:" << varDiffuse.mbrBlue << std::endl;
    Color varReflect = getColorReflect(argIxState, argLimit);
    // std::cout << "World::getColorShaded()::Reflect(r:" << varReflect.mbrRed << ",g:" << varReflect.mbrGreen << ",b:" << varReflect.mbrBlue << std::endl;
    Color varRefract = getColorRefracted(argIxState, argLimit);
    // std::cout << "World::getColorShaded()::Refract(r:" << varRefract.mbrRed << ",g:" << varRefract.mbrGreen << ",b:" << varRefract.mbrBlue << std::endl;
    Color varRes = varDiffuse + varReflect + varRefract;
    // std::cout << "World::getColorShaded()->Color(r:" << varRes.mbrRed << ",g:" << varRes.mbrGreen << ",b:" << varRes.mbrBlue << ")" << std::endl;
    // return varDiffuse + varReflect;
    return varRes;
}
Color World::getColorReflect(const IntersectionState &argIntersectionState, int argLimit) {
    // std::cout << "World::getColorReflect( #:" << argLimit << ", t: " << argIntersectionState.mbrTime << " )" << std::endl;
    // argIntersectionState.renderConsole();
    // std::cout << "World::getColorShaded()::argIntersectionState.mbrPoint(x:" << argIntersectionState.mbrPoint.mbrX << ",y:" << argIntersectionState.mbrPoint.mbrY << ",z:" << argIntersectionState.mbrPoint.mbrZ << ",w:" << argIntersectionState.mbrPoint.mbrW << std::endl;
    // std::cout << "World::getColorShaded()::argIntersectionState.mbrOverPoint(x:" << argIntersectionState.mbrOverPoint.mbrX << ",y:" << argIntersectionState.mbrOverPoint.mbrY << ",z:" << argIntersectionState.mbrOverPoint.mbrZ << ",w:" << argIntersectionState.mbrOverPoint.mbrW << std::endl;
    // std::cout << "World::getColorShaded()::argIntersectionState.mbrEye(x:" << argIntersectionState.mbrEye.mbrX << ",y:" << argIntersectionState.mbrEye.mbrY << ",z:" << argIntersectionState.mbrEye.mbrZ << ",w:" << argIntersectionState.mbrEye.mbrW << std::endl;
    // std::cout << "World::getColorShaded()::argIntersectionState.mbrNormal(x:" << argIntersectionState.mbrNormal.mbrX << ",y:" << argIntersectionState.mbrNormal.mbrY << ",z:" << argIntersectionState.mbrNormal.mbrZ << ",w:" << argIntersectionState.mbrNormal.mbrW << std::endl;
    if (argLimit < 1) return Color(0,0,0);
    Comparinator varComp = Comparinator();
    if (varComp.checkFloat(argIntersectionState.mbrObject->mbrMaterial->mbrReflective, 0)) return Color(0,0,0);
    Ray varRayReflect = Ray(argIntersectionState.mbrOverPoint, argIntersectionState.mbrReflect);
    // std::cout << "World::getColorShaded()::varRayReflect.mbrOrigin(x:" << varRayReflect.mbrOrigin.mbrX << ",y:" << varRayReflect.mbrOrigin.mbrY << ",z:" << varRayReflect.mbrOrigin.mbrZ << ",w:" << varRayReflect.mbrOrigin.mbrW << std::endl;
    // std::cout << "World::getColorShaded()::varRayReflect.mbrDirection(x:" << varRayReflect.mbrDirection.mbrX << ",y:" << varRayReflect.mbrDirection.mbrY << ",z:" << varRayReflect.mbrDirection.mbrZ << ",w:" << varRayReflect.mbrDirection.mbrW << std::endl;
    Color varColor = getColor(varRayReflect, argLimit - 1);
    // std::cout << "World::getColorReflect()::Color(r:" << varColor.mbrRed << ",g:" << varColor.mbrGreen << ",b:" << varColor.mbrBlue << ")" << "* mbrReflective(" << argIntersectionState.mbrObject->mbrMaterial->mbrReflective << std::endl;
    return varColor * argIntersectionState.mbrObject->mbrMaterial->mbrReflective;;
    Color varRes = varColor * argIntersectionState.mbrObject->mbrMaterial->mbrReflective;
    // std::cout << "World::getColorReflect()::Color(r:" << varRes.mbrRed << ",g:" << varRes.mbrGreen << ",b:" << varRes.mbrBlue << ")" << std::endl;
    return varRes;
}
Color World::getColorRefracted(const IntersectionState &argIntersectionState, int argLimit) {
    // std::cout << "World::getColorRefracted( #:" << argLimit << ", t: " << argIntersectionState.mbrTime << " )" << std::endl;
    // argIntersectionState.renderConsole("Color World::getColorRefracted");
    if (argLimit < 1) { return Color(0,0,0); }
    Comparinator varComp = Comparinator();
    if (varComp.checkFloat(argIntersectionState.mbrObject->mbrMaterial->mbrTransparency, 0)) { return Color(0,0,0); }
    double varNToN = argIntersectionState.mbrRefractiveIndexOne/argIntersectionState.mbrRefractiveIndexTwo;
    double varCosThetaI = argIntersectionState.mbrEye.dot(argIntersectionState.mbrNormal);
    double varSinThetaTSquared = (varNToN*varNToN) * (1.0-(varCosThetaI*varCosThetaI));
    // std::cout << "World::getColorRefracted()::varNToN=(" << varNToN << std::endl;
    // std::cout << "World::getColorRefracted()::varCosThetaI=(" << varCosThetaI << std::endl;
    // std::cout << "World::getColorRefracted()::varSinThetaTSquared=(" << varSinThetaTSquared << std::endl;
    if (varSinThetaTSquared > 1) { return Color(0,0,0); }
    double varCosThetaT = sqrt(1.0-varSinThetaTSquared);
    Vector varRefractDirection = (argIntersectionState.mbrNormal * ((varNToN * varCosThetaI) - varCosThetaT)).subtract(argIntersectionState.mbrEye * varNToN);
    // std::cout << "World::getColorRefracted()::varRefractDirection(x:" << varRefractDirection.mbrX << ",y:" << varRefractDirection.mbrY << ",z:" << varRefractDirection.mbrZ << ",w:" << varRefractDirection.mbrW << std::endl;
    Ray varRefractRay = Ray(argIntersectionState.mbrUnderPoint, varRefractDirection);
    // std::cout << "World::getColorRefracted()::argIntersectionState.mbrUnderPoint(x:" << argIntersectionState.mbrUnderPoint.mbrX << ",y:" << argIntersectionState.mbrUnderPoint.mbrY << ",z:" << argIntersectionState.mbrUnderPoint.mbrZ << ",w:" << argIntersectionState.mbrUnderPoint.mbrW << std::endl;
    Color varRefractColor = getColor(varRefractRay, argLimit-1) * argIntersectionState.mbrObject->mbrMaterial->mbrTransparency;
    // std::cout << "World::getColorRefracted()->Color(r:" << varRefractColor.mbrRed << ",g:" << varRefractColor.mbrGreen << ",b:" << varRefractColor.mbrBlue << ")" << std::endl;
    return varRefractColor;
}
bool World::checkShadowed(const Point &argPoint) {
    bool varFlagShadow = false;
    for (int i = 0; i < mbrLights.size(); ++i)
    {
        Vector varDirection = mbrLights[i].mbrPosition - argPoint;
        double varDistance = varDirection.magnitude();
        Vector varDirectionNormalized = varDirection.normalize();
        Ray varRay = Ray (argPoint, varDirectionNormalized);
        Intersection varHit = getIntersect(varRay).hit();
        bool varShadow = varHit.mbrExists && (varHit.mbrTime < varDistance);
        varFlagShadow = varShadow ? true : varFlagShadow;
    }
    return varFlagShadow;
}
void World::setObject(Form* argObject) {
    if (Sphere *varSphere = dynamic_cast<Sphere *>(argObject))
    {
        mbrObjects.push_back(std::make_unique<Sphere>(*varSphere));
    }
    else if (Plane *varPlane = dynamic_cast<Plane *>(argObject))
    {
        mbrObjects.push_back(std::make_unique<Plane>(*varPlane));
    }
    else {
        mbrObjects.push_back(std::make_unique<Form>(*argObject));
    }
}
// void World::setObject(std::unique_ptr<Form> &&argObject) {
//     //mbrObjects.push_back(std::make_unique<Form>(*argObject.get()));
//     mbrObjects.push_back(std::move(argObject));
// }
void World::setLight(PointSource argLight) {
    mbrLights.push_back(argLight);
}

DefaultWorld::DefaultWorld() : World()
{
    PointSource varDefaultLight = PointSource(Point(-10,10,-10), Color(1,1,1));
    setLight(varDefaultLight);
    Sphere s = Sphere();
    s.setMaterial(Material());
    s.mbrMaterial->mbrColor = Color (0.8,1.0,0.6);
    s.mbrMaterial->mbrDiffuse = 0.7;
    s.mbrMaterial->mbrSpecular = 0.2;
    Sphere t = Sphere();
    t.setTransform(ScalingMatrix(0.5,0.5,0.5));
    setObject(new Sphere(s));
    setObject(new Sphere(t));
    // this->mbrObjects.push_back(std::make_unique<Sphere>(s));
    // this->mbrObjects.push_back(std::make_unique<Sphere>(t));
}