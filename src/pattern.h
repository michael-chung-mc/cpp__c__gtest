#pragma once
#ifndef PATTERN_H
#define PATTERN_H

class Matrix;
#include "color.h"
#include "tuple.h"
#include <vector>
#include <memory>

class Pattern {
public:
    Color mbrBlack;
    Color mbrWhite;
    std::vector<Color> mbrColors;
    std::unique_ptr<Matrix> mbrTransform;
    std::unique_ptr<Matrix> mbrTransformInverse;
    Pattern();
	Pattern(const Pattern& other);
    Pattern(const Color &argColorA, const Color &argColorB);
    virtual ~Pattern();
    virtual Color getColorLocal(const Point &argPoint);
    void setTransform(const Matrix &argMatrix);
    void renderConsole() const;
};

class PatternStripe : public Pattern {
public:
    PatternStripe();
	PatternStripe(const PatternStripe& other);
    PatternStripe(const Color &argColorA, const Color &argColorB);
    Color getColorLocal(const Point &argPoint) override;
};

class PatternGradient : public Pattern {
public:
    PatternGradient();
	PatternGradient(const PatternGradient& other);
    PatternGradient(const Color &argColorA, const Color &argColorB);
    Color getColorLocal(const Point &argPoint) override;
};

class PatternRing : public Pattern {
public:
    PatternRing();
	PatternRing(const PatternRing& other);
    PatternRing(const Color &argColorA, const Color &argColorB);
    Color getColorLocal(const Point &argPoint) override;
};

class PatternChecker : public Pattern {
public:
    PatternChecker();
	PatternChecker(const PatternChecker& other);
    PatternChecker(const Color &argColorA, const Color &argColorB);
    Color getColorLocal(const Point &argPoint) override;
};

#endif