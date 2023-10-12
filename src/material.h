#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

class PointSource;
class Point;
class Vector;
class Material;
class Pattern;
#include "color.h"
#include <memory>

class Material {
public:
    double mbrAmbient;
    double mbrDiffuse;
    double mbrSpecular;
    double mbrShininess;
    double mbrReflective;
    double mbrTransparency;
    double mbrRefractiveIndex;
    Color mbrColor;
    std::unique_ptr<Pattern> mbrPattern;
    Material();
	Material(const Material& other);
    virtual ~Material();
	Material& operator=(const Material other);
    bool checkEqual(Material other);
    Color getColor(PointSource argLighting, Point argPosition, Vector argEye, Vector argNormal, bool argInShadow);
    // void setPattern(Pattern *argPattern);
    void setPattern(std::unique_ptr<Pattern> argPattern);
    void renderConsole() const;
};

#endif