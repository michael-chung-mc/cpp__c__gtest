#include "material.h"
#include "tuple.h"
#include "light.h"
#include "color.h"
#include "comparinator.h"
#include "pattern.h"
#include <memory>
#include <cmath>
#include <iostream>

Material::Material ()
{
    mbrAmbient = 0.1;
    mbrDiffuse = 0.9;
    mbrSpecular = 0.9;
    mbrShininess = 200.0;
    mbrReflective = 0.0;
    mbrTransparency = 0.0;
    mbrRefractiveIndex = 1.0;
    mbrColor = Color(1,1,1);
    mbrPattern = std::make_unique<Pattern>(Pattern());
}
Material::Material(const Material& other)
{
    mbrAmbient = other.mbrAmbient;
    mbrDiffuse = other.mbrDiffuse;
    mbrSpecular = other.mbrSpecular;
    mbrShininess = other.mbrShininess;
    mbrReflective = other.mbrReflective;
    mbrTransparency = other.mbrTransparency;
    mbrRefractiveIndex = other.mbrRefractiveIndex;
    mbrColor = other.mbrColor;
    // setPattern(other.mbrPattern.get());
    setPattern(std::make_unique<Pattern>(*other.mbrPattern.get()));
}
Material::~Material() {
}
Material& Material::operator=(const Material other)
{
	if (this == &other) return *this;
    mbrAmbient = other.mbrAmbient;
    mbrDiffuse = other.mbrDiffuse;
    mbrSpecular = other.mbrSpecular;
    mbrShininess = other.mbrShininess;
    mbrReflective = other.mbrReflective;
    mbrColor = other.mbrColor;
    mbrTransparency = other.mbrTransparency;
    mbrRefractiveIndex = other.mbrRefractiveIndex;
    // setPattern(other.mbrPattern.get());
    setPattern(std::make_unique<Pattern>(*other.mbrPattern.get()));
    return *this;
}
bool Material::checkEqual(Material other)
{
    Comparinator ce = Comparinator();
    return ce.checkTuple(mbrColor, other.mbrColor) && ce.checkFloat(mbrAmbient, other.mbrAmbient) && ce.checkFloat(mbrDiffuse, other.mbrDiffuse) && ce.checkFloat(mbrSpecular, other.mbrSpecular) && ce.checkFloat(mbrShininess, other.mbrShininess);
}

Color Material::getColor(PointSource argLighting, Point argPosition, Vector argEye, Vector argNormal, bool argInShadow)
{
    // std::cout << "Material::getColor()" << std::endl;
    Color varColor = mbrPattern->mbrColors.size() != 0 ? mbrPattern->getColorLocal(argPosition) : mbrColor;
    // std::cout << "Material::getColor()::varColor(r:" << varColor.mbrRed << ",g:" << varColor.mbrGreen << ",b:" << varColor.mbrBlue << ")" << std::endl;
    Color varShade = varColor * argLighting.mbrIntensity;
    // std::cout << "Material::getColor()::varShade(r:" << varShade.mbrRed << ",g:" << varShade.mbrGreen << ",b:" << varShade.mbrBlue << ")";
    // std::cout << " = varColor * argLighting.mbrIntensity(r." << argLighting.mbrIntensity.mbrRed << ",g:" << argLighting.mbrIntensity.mbrGreen << ",b:" << argLighting.mbrIntensity.mbrBlue << std::endl;
    Color varResAmbient = varShade * mbrAmbient;
    // std::cout << "Material::getColor()::varResAmbient(r:" << varResAmbient.mbrRed << ",g:" << varResAmbient.mbrGreen << ",b:" << varResAmbient.mbrBlue << ")";
    // std::cout << " = varShade * mbrAmbient(" << mbrAmbient << std::endl;
    if (argInShadow) return varResAmbient;
    Vector varLight = (argLighting.mbrPosition - argPosition).normalize();
    // std::cout << "Material::getColor()::varLight(x:" << varLight.mbrX << ",y:" << varLight.mbrY << ",z:" << varLight.mbrZ << ",w:" << varLight.mbrW << ")";
    // std::cout << " = normalized(argLighting.mbrPosition(x:" << argLighting.mbrPosition.mbrX << ",y:" << argLighting.mbrPosition.mbrY << ",z:" << argLighting.mbrPosition.mbrZ << ")";
    // std::cout << " - argPosition(x:" << argPosition.mbrX << ",y:" << argPosition.mbrY << ",z:" << argPosition.mbrZ << ")" << std::endl;
    double varLightDotNormal = varLight.dot(argNormal);
    // std::cout << "Material::getColor()::varLightDotNormal(" << varLightDotNormal;
    // std::cout << " = dot(varLight,argNormal(x:" << argNormal.mbrX << ",y:" << argNormal.mbrY << ",z:" << argNormal.mbrZ << ",w:" << argNormal.mbrW << ")" << std::endl;
    Color varResDiffuse;
    Color varResSpecular;
    Vector varReflect;
    double varReflectDotEye;
    double varFactor;
    if (varLightDotNormal < 0.0)
    {
        varResDiffuse = Color(0,0,0);
        varResSpecular = Color(0,0,0);
    }
    else
    {
        varResDiffuse = varShade * (mbrDiffuse * varLightDotNormal);
        // std::cout << "Material::getColor()::varShade(r:" << varShade.mbrRed << ",g:" << varShade.mbrGreen << ",b:" << varShade.mbrBlue << ")";
        // std::cout << " = varColor * argLighting.mbrIntensity(r." << argLighting.mbrIntensity.mbrRed << ",g:" << argLighting.mbrIntensity.mbrGreen << ",b:" << argLighting.mbrIntensity.mbrBlue << std::endl;
        // std::cout << "* Material::getColor()::varResDiffuse = varShade * mbrDiffuse(" << mbrDiffuse << " * varLightDotNormal=(" << varLightDotNormal << std::endl;
        varReflect = (-varLight).reflect(argNormal);
        varReflectDotEye = varReflect.dot(argEye);
        // std::cout << "Material::getColor()::varReflectDotEye(" << varReflectDotEye;
        // std::cout << " = dot(varReflect * argEye(x:" << argEye.mbrX  << ",y:" << argEye.mbrY  << ",z:" << argEye.mbrZ  << ",w:" << argEye.mbrW << std::endl;
        if (varReflectDotEye <= 0.0)
        {
            varResSpecular = Color(0,0,0);
        }
        else
        {
            varFactor = pow(varReflectDotEye, mbrShininess);
            // std::cout << "Material::getColor()::varFactor(" << varFactor;
            // std::cout << " = varReflectDotEye ^ mbrShininess(x:" << mbrShininess << std::endl;
            varResSpecular = argLighting.mbrIntensity * (mbrSpecular * varFactor);
            // std::cout << "Material::getColor()::varResSpecular = argLighting.mbrIntensity * mbrSpecular" << mbrSpecular << "* varFactor" << std::endl;
        }
    }
    // std::cout << "Material::getColor()::varReflect(x:" << varReflect.mbrX << ",y:" << varReflect.mbrY << ",z:" << varReflect.mbrZ << ")" << std::endl;
    // std::cout << "Material::getColor()::varResDiffuse(r:" << varResDiffuse.mbrRed << ",g:" << varResDiffuse.mbrGreen << ",b:" << varResDiffuse.mbrBlue << ")" << std::endl;
    // std::cout << "Material::getColor()::varResSpecular(r:" << varResSpecular.mbrRed << ",g:" << varResSpecular.mbrGreen << ",b:" << varResSpecular.mbrBlue << ")" << std::endl;
    Color varRes = varResAmbient + (varResDiffuse + varResSpecular);
    // return argInShadow ? varResAmbient : varResAmbient + varResDiffuse + varResSpecular;
    // std::cout << "Material::getColor()->varRes(r:" << varRes.mbrRed << ",g:" << varRes.mbrGreen << ",b:" << varRes.mbrBlue << ") = varResAmbient?varResAmbient+varResDiffuse+varResSpecular" << std::endl;
    // std::cout << " == varResAmbient(r:" << varResAmbient.mbrRed << ",g:" << varResAmbient.mbrGreen << ",b:" << varResAmbient.mbrBlue << ")";
    // std::cout << " + varResDiffuse(r:" << varResDiffuse.mbrRed << ",g:" << varResDiffuse.mbrGreen << ",b:" << varResDiffuse.mbrBlue << ")";
    // std::cout << " + varResSpecular(r:" << varResSpecular.mbrRed << ",g:" << varResSpecular.mbrGreen << ",b:" << varResSpecular.mbrBlue << ")" << std::endl;
    return varRes;
}
void Material::setPattern(std::unique_ptr<Pattern> argPattern) {
    mbrPattern = std::move(argPattern);
}
// void Material::setPattern(Pattern *argPattern) {
//     if (PatternStripe *varPS = dynamic_cast<PatternStripe *>(argPattern))
//     {
//         mbrPattern = std::make_unique<PatternStripe>(*varPS);
//     }
//     else if (PatternGradient *varPS = dynamic_cast<PatternGradient *>(argPattern))
//     {
//         mbrPattern = std::make_unique<PatternGradient>(*varPS);
//     }
//     else if (PatternRing *varPS = dynamic_cast<PatternRing *>(argPattern))
//     {
//         mbrPattern = std::make_unique<PatternRing>(*varPS);
//     }
//     else if (PatternChecker *varPS = dynamic_cast<PatternChecker *>(argPattern))
//     {
//         mbrPattern = std::make_unique<PatternChecker>(*varPS);
//     }
//     else {
//         mbrPattern = std::make_unique<Pattern>(*argPattern);
//     }
// }
void Material::renderConsole() const {
    std::cout << "Material::renderConsole()" << std::endl;
    std::cout << "Material::renderConsole()::mbrAmbient(" << mbrAmbient << std::endl;
    std::cout << "Material::renderConsole()::mbrDiffuse(" << mbrDiffuse << std::endl;
    std::cout << "Material::renderConsole()::mbrSpecular(" << mbrSpecular << std::endl;
    std::cout << "Material::renderConsole()::mbrShininess(" << mbrShininess << std::endl;
    std::cout << "Material::renderConsole()::mbrReflective(" << mbrReflective << std::endl;
    std::cout << "Material::renderConsole()::mbrColor( ";
    mbrColor.renderConsole();
    std::cout << "Material::renderConsole()::mbrPattern( ";
    mbrPattern->renderConsole();
}