#include "pattern.h"
#include "color.h"
#include "tuple.h"
#include "matrix.h"
#include <cmath>
#include <memory>
#include <iostream>

Pattern::Pattern()
{
    mbrWhite = Color(1,1,1);
    mbrBlack = Color(0,0,0);
    setTransform(std::make_unique<Matrix>(IdentityMatrix(4,4)).get());
}
Pattern::Pattern(const Pattern& other)
{
    mbrColors = other.mbrColors;
    setTransform(*other.mbrTransform.get());
}
Pattern::Pattern(const Color &argColorA, const Color &argColorB) : Pattern() {
    mbrColors.push_back(argColorA);
    mbrColors.push_back(argColorB);
    setTransform(std::make_unique<Matrix>(IdentityMatrix(4,4)).get());
}
Pattern::~Pattern() { }
Color Pattern::getColorLocal(const Point &argPoint) {
    // std::cout << "Pattern::getColorLocal(x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << ")" << std::endl;
    Color varRes = Color(argPoint.mbrX, argPoint.mbrY, argPoint.mbrZ);
    // std::cout << "Pattern::getColorLocal::varRes(r:" << varRes.mbrRed << ",b:" << varRes.mbrBlue << ",g:" << varRes.mbrGreen << std::endl;
    return varRes;
    // return Color(argPoint.mbrX, argPoint.mbrY, argPoint.mbrZ);
}
void Pattern::setTransform(const Matrix &argMatrix) {
    mbrTransform = std::make_unique<Matrix>(argMatrix);
    // mbrTransformInverse = std::make_unique<Matrix>(*argMatrix.invert());
    mbrTransformInverse = std::make_unique<Matrix>(argMatrix.getInverse());
}
void Pattern::renderConsole() const {
    std::cout << "rPattern::enderConsole()" << std::endl;
    std::cout << "Pattern::mbrColors(" << std::endl;
    for (int i = 0; i < 0; ++i) {
        mbrColors[i].renderConsole();
    }
    std::cout << "Pattern::mbrTransform(" << std::endl;
    mbrTransform->renderConsole();
}

PatternStripe::PatternStripe() : Pattern() {
    mbrColors.push_back(mbrWhite);
    mbrColors.push_back(mbrBlack);
}
PatternStripe::PatternStripe(const PatternStripe& other) : Pattern()
{
    mbrColors = other.mbrColors;
    setTransform(*other.mbrTransform.get());
}
PatternStripe::PatternStripe(const Color &argColorA, const Color &argColorB) : Pattern() {
    mbrColors.push_back(argColorA);
    mbrColors.push_back(argColorB);
}
Color PatternStripe::getColorLocal(const Point &argPoint) {
    // std::cout << "PatternStripe::getColorLocal(x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << ")" << std::endl;
    Color res = (int)std::floor(argPoint.mbrX) % 2 == 0 ? mbrColors[0] : mbrColors[1];
    // std::cout << "stripe: x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << "C: r:" << res.mbrRed << " b:" << res.mbrBlue << " g:" << res.mbrGreen << std::endl;
    return res;
    // return (int)std::floor(argPoint.mbrX) % 2 == 0 ? mbrColors[0] : mbrColors[1];
}

PatternGradient::PatternGradient() : Pattern() {
    mbrColors.push_back(mbrWhite);
    mbrColors.push_back(mbrBlack);
}
PatternGradient::PatternGradient(const PatternGradient& other) : Pattern()
{
    mbrColors = other.mbrColors;
    setTransform(*other.mbrTransform.get());
}
PatternGradient::PatternGradient(const Color &argColorA, const Color &argColorB) : Pattern() {
    mbrColors.push_back(argColorA);
    mbrColors.push_back(argColorB);
}
Color PatternGradient::getColorLocal(const Point &argPoint) {
    // std::cout << "PatternGradient::getColorLocal(x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << ")" << std::endl;
    Color res = mbrColors[0] + (mbrColors[1]-mbrColors[0]) * (argPoint.mbrX - floor(argPoint.mbrX));
    // std::cout << "gradient: x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << "C: r:" << res.mbrRed << " b:" << res.mbrBlue << " g:" << res.mbrGreen << std::endl;
    return res;
    // return mbrColors[0] + (mbrColors[1]-mbrColors[0]) * (argPoint.mbrX - floor(argPoint.mbrX));
}

PatternRing::PatternRing() : Pattern() {
    mbrColors.push_back(mbrWhite);
    mbrColors.push_back(mbrBlack);
}
PatternRing::PatternRing(const PatternRing& other) : Pattern()
{
    mbrColors = other.mbrColors;
    setTransform(*other.mbrTransform.get());
}
PatternRing::PatternRing(const Color &argColorA, const Color &argColorB) : Pattern() {
    mbrColors.push_back(argColorA);
    mbrColors.push_back(argColorB);
}
Color PatternRing::getColorLocal(const Point &argPoint) {
    // std::cout << "PatternRing::getColorLocal(x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << ")" << std::endl;
    Color res = (int)fmod(floor(sqrt(pow(argPoint.mbrX,2) + pow(argPoint.mbrZ,2))),2) == 0 ? mbrColors[0]: mbrColors[1];
    // std::cout << "ring: x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << "C: r:" << res.mbrRed << " b:" << res.mbrBlue << " g:" << res.mbrGreen << std::endl;
    return res;
    // return (int)fmod(floor(sqrt(pow(argPoint.mbrX,2) + pow(argPoint.mbrZ,2))),2) == 0 ? mbrColors[0]: mbrColors[1];
}

PatternChecker::PatternChecker() : Pattern() {
    mbrColors.push_back(mbrWhite);
    mbrColors.push_back(mbrBlack);
}
PatternChecker::PatternChecker(const PatternChecker& other) : Pattern()
{
    mbrColors = other.mbrColors;
    setTransform(*other.mbrTransform.get());
}
PatternChecker::PatternChecker(const Color &argColorA, const Color &argColorB) : Pattern() {
    mbrColors.push_back(argColorA);
    mbrColors.push_back(argColorB);
}
Color PatternChecker::getColorLocal(const Point &argPoint) {
    // std::cout << "PatternChecker::getColorLocal(x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << ")" << std::endl;
    Color res = (int)fmod(floor(argPoint.mbrX) + floor(argPoint.mbrY) + floor(argPoint.mbrZ),2) == 0 ? mbrColors[0]: mbrColors[1];
    // std::cout << "checker 3d: x:" << argPoint.mbrX << " y:" << argPoint.mbrY << " z:" << argPoint.mbrZ << "C: r:" << res.mbrRed << " b:" << res.mbrBlue << " g:" << res.mbrGreen << std::endl;
    return res;
    // return (int)fmod(floor(argPoint.mbrX) + floor(argPoint.mbrZ),2) == 0 ? mbrColors[0]: mbrColors[1];
}