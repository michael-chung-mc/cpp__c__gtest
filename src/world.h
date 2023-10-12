#pragma once
#ifndef WORLD_H
#define WORLD_H

class Intersections;
class IntersectionState;
class Ray;
class Color;
#include "form.h"
#include "light.h"
#include <vector>

class World {
public:
    std::vector<std::unique_ptr<Form>> mbrObjects;
    std::vector<PointSource> mbrLights;
    World();
    World(const World &argOther);
    ~World() = default;
    World& operator=(const World &argOther);
    Intersections getIntersect(const Ray &argRay);
    Color getColor(const Ray &r, int argLimit = 5);
    Color getColorLighting(const IntersectionState &argIntersectionState, int argLimit = 5);
    Color getColorShaded(const IntersectionState &argIntersectionState, int argLimit = 5);
    Color getColorReflect(const IntersectionState &argIntersectionState, int argLimit = 5);
    Color getColorRefracted(const IntersectionState &argIntersectionState, int argLimit = 5);
    bool checkShadowed(const Point &argPoint);
    void setObject(Form* argObject);
    // void setObject(std::unique_ptr<Form> &&argObject);
    void setLight(PointSource argLight);
};

class DefaultWorld : public World {
public:
    DefaultWorld();
};

#endif