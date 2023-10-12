#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "canvas.h"
#include "world.h"
#include "matrix.h"

class Camera {
public:
    int mbrCanvasHorizontal;
    int mbrCanvasVertical;
    double mbrFieldOfView;
    double mbrHalfWidth;
    double mbrHalfHeight;
    double mbrPixelSquare;
    std::unique_ptr<Matrix> mbrTransform;
    std::unique_ptr<Matrix> mbrTransformInverse;
    Camera(const Camera &argOther);
    Camera(Camera &&argOther) noexcept;
    Camera(int argH, int argV, double argFOV);
    ~Camera();
    Camera& operator=(const Camera &argOther);
    Camera& operator=(Camera &&argOther) noexcept;
    Ray getRay(int argPxX, int argPxY);
    Canvas render(World &argWorld);
    // void setTransform (Matrix *argMatrix);
    void setTransform (std::unique_ptr<Matrix>argMatrix);
};

#endif