#include "camera.h"
#include "matrix.h"
#include "ray.h"
#include "canvas.h"
#include "world.h"
#include <iostream>
#include <cmath>

Camera::Camera(const Camera &argOther) {
    mbrCanvasHorizontal = argOther.mbrCanvasHorizontal;
    mbrCanvasVertical = argOther.mbrCanvasVertical;
    mbrFieldOfView = argOther.mbrFieldOfView;
    mbrHalfWidth = argOther.mbrHalfWidth;
    mbrHalfHeight = argOther.mbrHalfHeight;
    mbrPixelSquare = argOther.mbrPixelSquare;
    // setTransform(argOther.mbrTransform.get());
    setTransform(std::make_unique<Matrix>(*argOther.mbrTransform.get()));
}
Camera::Camera(Camera &&argOther) noexcept {
    mbrCanvasHorizontal = argOther.mbrCanvasHorizontal;
    mbrCanvasVertical = argOther.mbrCanvasVertical;
    mbrFieldOfView = argOther.mbrFieldOfView;
    mbrHalfWidth = argOther.mbrHalfWidth;
    mbrHalfHeight = argOther.mbrHalfHeight;
    mbrPixelSquare = argOther.mbrPixelSquare;
    mbrTransform = std::move(argOther.mbrTransform);
    argOther.mbrTransform = nullptr;
}
Camera::Camera(int argH, int argV, double argFOV)
{
    mbrCanvasHorizontal = argH;
    mbrCanvasVertical = argV;
    mbrFieldOfView = argFOV;
    double varHalfView = tan(mbrFieldOfView/2);
    double varAspectRatio = (double)mbrCanvasHorizontal/(double)mbrCanvasVertical;
    if (varAspectRatio >= 1) {
        mbrHalfWidth = varHalfView;
        mbrHalfHeight = varHalfView/varAspectRatio;
    }
    else {
        mbrHalfWidth = varHalfView * varAspectRatio;
        mbrHalfHeight = varHalfView;
    }
    mbrPixelSquare = (mbrHalfWidth * 2) / mbrCanvasHorizontal;
    setTransform(std::make_unique<Matrix>(IdentityMatrix(4,4)));
}
Camera::~Camera() {
}
Camera& Camera::operator=(const Camera &argOther) {
    if (this == &argOther) return *this;
    mbrCanvasHorizontal = argOther.mbrCanvasHorizontal;
    mbrCanvasVertical = argOther.mbrCanvasVertical;
    mbrFieldOfView = argOther.mbrFieldOfView;
    mbrHalfWidth = argOther.mbrHalfWidth;
    mbrHalfHeight = argOther.mbrHalfHeight;
    mbrPixelSquare = argOther.mbrPixelSquare;
    // setTransform(argOther.mbrTransform.get());
    setTransform(std::make_unique<Matrix>(*argOther.mbrTransform.get()));
    return *this;
}
Camera& Camera::operator=(Camera &&argOther) noexcept {
    if (this == &argOther) return *this;
    mbrCanvasHorizontal = argOther.mbrCanvasHorizontal;
    mbrCanvasVertical = argOther.mbrCanvasVertical;
    mbrFieldOfView = argOther.mbrFieldOfView;
    mbrHalfWidth = argOther.mbrHalfWidth;
    mbrHalfHeight = argOther.mbrHalfHeight;
    mbrPixelSquare = argOther.mbrPixelSquare;
    mbrTransform = std::move(argOther.mbrTransform);
    argOther.mbrTransform = nullptr;
    return *this;
}
Ray Camera::getRay(int argPxX, int argPxY)
{
    double varOffsetX = (argPxX + 0.5) * mbrPixelSquare;
    double varOffsetY = (argPxY + 0.5) * mbrPixelSquare;
    double varWorldX = mbrHalfWidth - varOffsetX;
    double varWorldY = mbrHalfHeight - varOffsetY;
    // Point varPixelPos = *mbrTransform->invert() * Point(varWorldX, varWorldY, -1);
    // Point varOrigin = *mbrTransform->invert() * Point(0,0,0);
    Point varPixelPos = *mbrTransformInverse.get() * Point(varWorldX, varWorldY, -1);
    Point varOrigin = *mbrTransformInverse.get() * Point(0,0,0);
    Vector varDirection = (varPixelPos - varOrigin).normalize();
    return Ray(varOrigin, varDirection);
}

Canvas Camera::renderCanvas(World &argWorld)
{
    int varCounterLimit = 1000;
    Canvas varCanvas = Canvas(mbrCanvasHorizontal, mbrCanvasVertical);
    for (int i = 0; i < mbrCanvasVertical; ++i)
    {
        for (int j = 0; j < mbrCanvasHorizontal; ++j)
        {
            Ray varRay = getRay(j, i);
            Color varColor = argWorld.getColor(varRay);
            varCanvas.setPixel(j, i, varColor);
            if ((i * mbrCanvasVertical + j) % varCounterLimit == 0) { std::cout << "rendered pixel: " << (i * mbrCanvasVertical + j) << "/" << (mbrCanvasVertical*mbrCanvasHorizontal) << std::endl; }
        }
    }
    return varCanvas;
}
// void Camera::setTransform (Matrix *argMatrix) {
//     mbrTransform = std::make_unique<Matrix>(*argMatrix);
//     mbrTransformInverse = std::make_unique<Matrix>(*argMatrix->invert());
// }
void Camera::setTransform (std::unique_ptr<Matrix>argMatrix) {
    mbrTransform = std::move(argMatrix);
    argMatrix = nullptr;
    // mbrTransformInverse = std::make_unique<Matrix>(*mbrTransform->invert());
    mbrTransformInverse = std::make_unique<Matrix>(mbrTransform->getInverse());
}