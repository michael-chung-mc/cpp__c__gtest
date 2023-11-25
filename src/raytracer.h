#pragma once
#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "pch.h"
#include "camera.h"
#include "tuple.h"
#include "canvas.h"
#include "color.h"
#include "light.h"
#include "ray.h"
#include "material.h"
#include "intersection.h"
#include "form.h"
#include "pattern.h"

class Projectile {
public:
	Projectile(Point pos, Vector vel)
	{
		position = pos;
		velocity = vel;
	}
	Point position;
	Vector velocity;
};

class Environment {
public:
	Environment(Vector g, Vector w)
	{
		gravity = g;
		wind = w;
	}
	Vector gravity;
	Vector wind;
};

class Simulation {
private:
	Canvas c = Canvas(getPPMWidth(), getPPMHeight());
public:
	Projectile tick(Environment env, Projectile ball)
	{
		Point position = ball.position + ball.velocity;
		Vector velocity = ball.velocity + env.gravity + env.wind;
		return Projectile(position, velocity);
	}
	void fire(int power) {
		c.fill(Color(1, 1, 1));
		//Projectile b = Projectile(Point(0, 1, 0), (Vector(1, 1, 0)*power).normalize());
		Projectile b = Projectile(Point(0, 1, 0), (Vector(1, 1, 0).normalize()) * power);
		Environment e = Environment(Vector(0, -.1, 0), Vector(-.01, 0, 0));
		while (b.position.mbrY >= 0)
		{
			b = tick(e,b);
			std::cout << "x: " << std::to_string(b.position.mbrX) << " y: " << std::to_string(b.position.mbrY) << " z: " << std::to_string(b.position.mbrZ) << " w: " << std::to_string(b.position.mbrW) << std::endl;
			Color white = Color(0, 0, 0);
			c.setPixel((int)b.position.mbrX, getPPMHeight() - b.position.mbrY, white);
		}
		c.save();
	}
};

class RayTracer {
public:
    void test() {
        Point varTestEye = Point(0,0,-5);
        int varTestCanvasWidthSingle = 100;
        int varTestCanvasHeightSingle = 100;
        double varTestCanvasAngleSingle = getPI()/4;

        PointSource varTestLight = PointSource(Point(-10,10,-10), Color(1,1,1));

        Color varWhite = Color(1,1,1);
        Color varOrange = Color(.8, 0.333, 0);
        std::unique_ptr<Material> varTestMat = std::make_unique<Material>();
        varTestMat->mbrColor = varOrange;
        varTestMat->mbrDiffuse = 0.7;
        varTestMat->mbrSpecular = 0.3;
        std::unique_ptr<Material> varTestMatStripe = std::make_unique<Material>();
        varTestMatStripe->setPattern(std::make_unique<PatternStripe>(varOrange, varWhite));
        std::unique_ptr<Material> varTestMatGradient = std::make_unique<Material>();
        varTestMatGradient->setPattern(std::make_unique<PatternGradient>(varOrange, varWhite));
        varTestMatGradient->mbrPattern->setTransform(*std::make_unique<ScalingMatrix>(varTestCanvasWidthSingle,0.01,varTestCanvasHeightSingle).get());
        std::unique_ptr<Material> varTestMatChecker = std::make_unique<Material>();
        varTestMatChecker->setPattern(std::make_unique<PatternChecker>(varOrange, varWhite));
        varTestMatChecker->mbrPattern->setTransform(*std::make_unique<ScalingMatrix>(0.05,0.05,0.05).get());
        std::unique_ptr<Material> varTestMatRing = std::make_unique<Material>();
        varTestMatRing->setPattern(std::make_unique<PatternRing>(varOrange, varWhite));
        varTestMatRing->mbrPattern->setTransform(*std::make_unique<ScalingMatrix>(0.05,0.01,0.05).get());

        // directTracerShadow(varOrange);

        // directRenderSphere(varTestEye, varTestLight, 10, 10, 100, varOrange);
        // cameraRenderSphere(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(1.5,1.5,1.5), *varTestMat.get());
        cameraRenderSphere(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(1.5,1.5,1.5), *varTestMatStripe.get());
        cameraRenderSphere(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(1.5,1.5,1.5), *varTestMatGradient.get());
        cameraRenderSphere(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(1.5,1.5,1.5), *varTestMatChecker.get());
        cameraRenderSphere(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(1.5,1.5,1.5), *varTestMatRing.get());

        cameraRenderPlane(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(0.05,0.05,0.05).rotateX(getPI()/2), *varTestMat.get());
        cameraRenderPlane(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(0.05,0.05,0.05).rotateX(getPI()/2), *varTestMatStripe.get());
        cameraRenderPlane(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(0.05,0.05,0.05).rotateX(getPI()/2), *varTestMatGradient.get());
        cameraRenderPlane(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(0.05,0.05,0.05).rotateX(getPI()/2), *varTestMatChecker.get());
        cameraRenderPlane(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(0.05,0.05,0.05).rotateX(-getPI()/4), *varTestMatChecker.get());
        cameraRenderPlane(ViewMatrix(varTestEye, Point(0,0,0), Vector(0,1,0)), varTestCanvasWidthSingle, varTestCanvasHeightSingle, varTestCanvasAngleSingle, varTestLight, ScalingMatrix(0.05,0.05,0.05).rotateX(getPI()/2), *varTestMatRing.get());


        cameraRenderRoom();

        // cameraRenderSpheres();
        // cameraRenderPlanes();

        // cameraRenderSpherePlane();
        // cameraRenderPatterns();
        // cameraRenderReflections();
        // cameraRenderReflectRefract();
    }
    void directTracerShadow(Color argColor)
    {
        std::cout << "raytracer::directTracerShadow()" << std::endl;
        Point pov = Point(0,0,-5);
        double wallWidth = 10;
        double wallZ = 10;
        double wallXY = wallWidth/2;
        double pixels = 100;
        double pixelSize = wallWidth/pixels;
        Canvas canvas = Canvas(pixels,pixels);

        Sphere obj = Sphere();

        for (int i = 0; i <= pixels; ++i)
        {
            double worldY = wallXY - pixelSize * i;
            for (int j = 0; j <= pixels; ++j)
            {
                double worldX = -wallXY + pixelSize * j;
                Point position = Point(worldX, worldY, wallZ);
                //std::cout << worldX << worldY << wallZ << std::endl;
                Ray r = Ray(pov, (position-pov).normalize());
                // std::vector<Intersection> xs = obj.getIntersections(r).mbrIntersections;
                std::vector<std::unique_ptr<Intersection>> xs = obj.getIntersections(r).mbrIntersections;
                if (xs.size() != 0)
                {
                    canvas.setPixel(i,j,argColor);
                }
            }
        }
        canvas.save();
    }
    void directRenderSphere(Point argPov, PointSource argLight, double argScreenWidth, double argScreenZ, double argScreenPixels, Color argSphereColor)
    {
        std::cout << "raytracer::directRenderSphere()" << std::endl;
        Canvas varCanvas = Canvas(argScreenPixels,argScreenPixels);
        double varScreenXY = argScreenWidth/2;
        double varPixelSize = argScreenWidth/argScreenPixels;

        Sphere varObj = Sphere();
        varObj.setMaterial(Material());
        //varObj.material.shininess = 0;
        varObj.mbrMaterial->mbrColor = argSphereColor;

        PointSource varLight = argLight;

        for (int i = 0; i <= argScreenPixels; ++i)
        {
            double varWorldY = varScreenXY - varPixelSize * i;
            for (int j = 0; j <= argScreenPixels; ++j)
            {
                double varWorldX = -varScreenXY + varPixelSize * j;
                Point varWorldPosition = Point(varWorldX, varWorldY, argScreenZ);
                //std::cout << worldX << worldY << wallZ << std::endl;
                Ray r = Ray(argPov, (varWorldPosition-argPov).normalize());
                // std::vector<Intersection> xs = varObj.getIntersections(r).mbrIntersections;
                std::vector<std::unique_ptr<Intersection>> xs = varObj.getIntersections(r).mbrIntersections;
                if (xs.size() != 0)
                {
                    // Point p = r.getPosition(xs[0].mbrTime);
                    // Vector normal = xs[0].mbrObject->getNormal(p);
                    Point p = r.getPosition(xs[0]->mbrTime);
                    Vector normal = xs[0]->mbrObject->getNormal(p);
                    Vector pov = -r.mbrDirection;
                    Color shade = varObj.mbrMaterial->getColor(varLight, p, pov, normal, false);
                    varCanvas.setPixel(i,j,shade);
                }
            }
        }
        varCanvas.save();
    }
    void cameraRenderSphere(ViewMatrix argView, double argScreenHeight, double argScreenWidth, double argFov, PointSource argLight, Matrix argSphereTransform, Material argSphereMaterial)
    {
        std::cout << "raytracer::cameraRenderSphere()" << std::endl;
        Camera varCamera = Camera(argScreenWidth,argScreenHeight,argFov);
        varCamera.setTransform(std::make_unique<ViewMatrix>(argView));
        World varEnv = World();
        varEnv.setLight(argLight);
        Sphere varObj = Sphere();
        varObj.setTransform(argSphereTransform);
        varObj.setMaterial(argSphereMaterial);
        varEnv.setObject(new Sphere(varObj));
        Canvas img = varCamera.renderCanvas(varEnv);
        img.save();
    }
    void cameraRenderPlane(ViewMatrix argView, double argScreenHeight, double argScreenWidth, double argFov, PointSource argLight, Matrix argObjTransform, Material argObjMaterial)
    {
        std::cout << "raytracer::cameraRenderPlane()" << std::endl;
        Camera varCamera = Camera(argScreenWidth,argScreenHeight,argFov);
        varCamera.setTransform(std::make_unique<ViewMatrix>(argView));
        World varEnv = World();
        varEnv.setLight(argLight);
        std::unique_ptr<Plane> varObj = std::make_unique<Plane>();
        varObj->setTransform(argObjTransform);
        varObj->setMaterial(argObjMaterial);
        varEnv.setObject(varObj.get());
        Canvas img = varCamera.renderCanvas(varEnv);
        img.save();
    }
    void cameraRenderRoom()
    {
        std::cout << "raytracer::cameraRenderRoom()" << std::endl;
        // Camera varCamera = Camera(160,90,getPI()/2);
        Camera varCamera = Camera(400,200,1.152);
        varCamera.setTransform(std::make_unique<ViewMatrix>(Point(-2.6,1.5,-3.9), Point(-0.6,1,-0.8), Vector(0,1,0)));

        World varEnv = World();

        PointSource varLight = PointSource(Point(-4.9,4.9,-1), Color(1,1,1));
        varEnv.setLight(varLight);

        Material varWallMaterial = Material();
        varWallMaterial.setPattern(std::make_unique<PatternStripe>(Color(0.45,0.45,0.45), Color(0.55,0.55,0.55)));
        varWallMaterial.mbrPattern->setTransform(ScalingMatrix(0.25,0.25,0.25).rotateY(1.5708));
        // varWallMaterial.mbrPattern->setTransform(YRotationMatrix(1.5708).scale(0.25,0.25,0.25));
        varWallMaterial.mbrAmbient = 0;
        varWallMaterial.mbrDiffuse = 0.4;
        varWallMaterial.mbrSpecular = 0;
        varWallMaterial.mbrReflective = 0.3;

        Plane varFloor = Plane();
        varFloor.setTransform(YRotationMatrix(0.31415));
        varFloor.setMaterial(Material());
        varFloor.mbrMaterial->setPattern(std::make_unique<PatternChecker>(Color(0.35,0.35,0.35), Color(0.65,0.65,0.65)));
        varFloor.mbrMaterial->mbrSpecular = 0;
        varFloor.mbrMaterial->mbrReflective = 0.4;
        varEnv.setObject(std::make_unique<Plane>(varFloor).get());

        Plane varCeiling = Plane();
        varCeiling.setTransform(TranslationMatrix(0,5,0));
        varCeiling.setMaterial(Material());
        varCeiling.mbrMaterial->mbrColor = Color(0.8,0.8,0.8);
        varCeiling.mbrMaterial->mbrAmbient = 0.3;
        varCeiling.mbrMaterial->mbrSpecular = 0;
        varEnv.setObject(std::make_unique<Plane>(varCeiling).get());

        Plane varWallWest = Plane();
        varWallWest.setTransform(YRotationMatrix(1.5708).rotateX(1.5708).translate(-5,0,0));
        // varWallWest.setTransform(TranslationMatrix(-5,0,0).rotateX(1.5708)->rotateY(1.5708));
        varWallWest.setMaterial(Material(varWallMaterial));
        varEnv.setObject(std::make_unique<Plane>(varWallWest).get());

        Plane varWallEast = Plane();
        varWallEast.setTransform(YRotationMatrix(1.5708).rotateZ(1.5708).translate(5,0,0));
        // varWallEast.setTransform(TranslationMatrix(5,0,0).rotateZ(1.5708)->rotateY(1.5708));
        varWallEast.setMaterial(Material(varWallMaterial));
        varEnv.setObject(std::make_unique<Plane>(varWallEast).get());

        Plane varWallNorth = Plane();
        varWallNorth.setTransform(XRotationMatrix(1.5708).translate(0,0,5));
        // varWallNorth.setTransform(TranslationMatrix(0,0,5).rotateX(1.5708));
        varWallNorth.setMaterial(Material(varWallMaterial));
        varEnv.setObject(std::make_unique<Plane>(varWallNorth).get());

        Plane varWallSouth = Plane();
        varWallSouth.setTransform(XRotationMatrix(1.5708).translate(0,0,-5));
        // varWallSouth.setTransform(TranslationMatrix(0,0,-5).rotateX(1.5708));
        varWallSouth.setMaterial(Material(varWallMaterial));
        varEnv.setObject(std::make_unique<Plane>(varWallSouth).get());

        Canvas img = varCamera.renderCanvas(varEnv);
        img.save();
    }






    // void cameraRenderSpheres()
    // {
    //     PointSource varLight = PointSource(Point(-10,10,-10), Color(1,1,1));

    //     Sphere varFloor = Sphere();
    //     varFloor.setTransform(ScalingMatrix(10,0.01,10));
    //     varFloor.setMaterial(Material());
    //     varFloor.mbrMaterial->mbrColor = Color(1,0.9,0.9);
    //     varFloor.mbrMaterial->mbrSpecular = 0;

    //     Sphere varLeftWall = Sphere();
    //     varLeftWall.setTransform(*(*(*(TranslationMatrix(0,0,5) * YRotationMatrix(-getPI()/4)) * XRotationMatrix(getPI()/2)) * ScalingMatrix(10,0.01,10)));
    //     varLeftWall.setMaterial(*varFloor.mbrMaterial);

    //     Sphere varRightWall = Sphere();
    //     varRightWall.setTransform(*(*(*(TranslationMatrix(0,0,5) * YRotationMatrix(getPI()/4)) * XRotationMatrix(getPI()/2)) * ScalingMatrix(10,0.01,10)));
    //     varRightWall.setMaterial(*varFloor.mbrMaterial);

    //     Sphere varObjMid = Sphere();
    //     varObjMid.setTransform(TranslationMatrix(-0.5,1,0.5));
    //     varObjMid.setMaterial(Material());
    //     varObjMid.mbrMaterial->mbrColor = Color(0.1,1,0.5);
    //     varObjMid.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjMid.mbrMaterial->mbrSpecular = 0.3;

    //     Sphere varObjRight = Sphere();
    //     varObjRight.setTransform(*(TranslationMatrix(1.5,0.5,-0.5) * ScalingMatrix(0.5,0.5,0.5))); 
    //     varObjRight.setMaterial(Material());
    //     varObjRight.mbrMaterial->mbrColor = Color(0.5,1,0.1);
    //     varObjRight.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjRight.mbrMaterial->mbrSpecular = 0.3;

    //     Sphere varObjLeft = Sphere();
    //     varObjLeft.setTransform(*(TranslationMatrix(-1.5,0.33,-0.75) * ScalingMatrix(0.33,0.33,0.33))); 
    //     varObjLeft.setMaterial(Material());
    //     varObjLeft.mbrMaterial->mbrColor = Color(1,0.8,0.1);
    //     varObjLeft.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjLeft.mbrMaterial->mbrSpecular = 0.3;

    //     World varEnv = World();
    //     varEnv.setObject(new Sphere(varFloor));
    //     varEnv.setObject(new Sphere(varLeftWall));
    //     varEnv.setObject(new Sphere(varRightWall));
    //     varEnv.setObject(new Sphere(varObjMid));
    //     varEnv.setObject(new Sphere(varObjRight));
    //     varEnv.setObject(new Sphere(varObjLeft));
    //     // varEnv.setObject(std::make_unique<Sphere>(varFloor));
    //     // varEnv.setObject(std::make_unique<Sphere>(varLeftWall));
    //     // varEnv.setObject(std::make_unique<Sphere>(varRightWall));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjMid));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjRight));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjLeft));
    //     varEnv.mbrLights.push_back(varLight);

    //     Camera varCamera = Camera(100,50,getPI()/3);
    //     varCamera.setTransform(new ViewMatrix(Point(0,1.5,-5), Point(0,1,0), Vector(0,1,0)));

    //     Canvas img = varCamera.render(varEnv);
    //     img.save();
    // }


    // void cameraRenderSpherePlane()
    // {
    //     PointSource varLight = PointSource(Point(-10,10,-10), Color(1,1,1));

    //     Plane varFloor = Plane();
    //     varFloor.setTransform(*(TranslationMatrix(0,-1,0) * ScalingMatrix(10,1,10)));
    //     varFloor.setMaterial(Material());
    //     varFloor.mbrMaterial->mbrSpecular = 1;
    //     varFloor.mbrMaterial->setPattern(new PatternChecker(Color(0,0,0), Color(1,1,1)));
    //     varFloor.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(1,0.1,1));

    //     Plane varLeftWall = Plane();
    //     varLeftWall.setTransform(*(*(*(TranslationMatrix(0,0,5) * YRotationMatrix(-getPI()/4)) * XRotationMatrix(getPI()/2)) * ScalingMatrix(10,1,10)));
    //     varLeftWall.setMaterial(Material());
    //     varLeftWall.mbrMaterial->setPattern(new PatternGradient(Color(1,0,0), Color(0,0,1)));
    //     varLeftWall.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(1,1,2));

    //     Plane varRightWall = Plane();
    //     varRightWall.setTransform(*(*(*(TranslationMatrix(0,0,5) * YRotationMatrix(getPI()/4)) * XRotationMatrix(getPI()/2)) * ScalingMatrix(10,1,10)));
    //     varRightWall.setMaterial(Material());
    //     varRightWall.mbrMaterial->setPattern(new PatternRing(Color(1,0,0), Color(1,1,1)));
    //     varRightWall.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(0.05,0.05,0.05));

    //     Sphere varObjMid = Sphere();
    //     varObjMid.setTransform(TranslationMatrix(-0.5,1,0.5));
    //     varObjMid.setMaterial(Material());
    //     varObjMid.mbrMaterial->mbrColor = Color(0.1,1,0.5);
    //     varObjMid.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjMid.mbrMaterial->mbrSpecular = 0.3;

    //     Sphere varObjRight = Sphere();
    //     varObjRight.setTransform(*(TranslationMatrix(1.5,0.5,-0.5) * ScalingMatrix(2,0.5,2))); 
    //     varObjRight.setMaterial(Material());
    //     varObjRight.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjRight.mbrMaterial->mbrSpecular = 0.3;
    //     varObjRight.mbrMaterial->setPattern(new PatternStripe(Color(1,0,0), Color(0,0,1)));
    //     varObjRight.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(0.25,0.25,0.25));

    //     Sphere varObjLeft = Sphere();
    //     varObjLeft.setTransform(*(TranslationMatrix(-1.5,0.33,-0.75) * ScalingMatrix(0.33,0.33,0.33))); 
    //     varObjLeft.setMaterial(Material());
    //     varObjLeft.mbrMaterial->mbrColor = Color(1,0.8,0.1);
    //     varObjLeft.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjLeft.mbrMaterial->mbrSpecular = 0.3;

    //     World varEnv = World();
    //     varEnv.setObject(new Plane(varFloor));
    //     varEnv.setObject(new Plane(varLeftWall));
    //     varEnv.setObject(new Plane(varRightWall));
    //     varEnv.setObject(new Sphere(varObjMid));
    //     varEnv.setObject(new Sphere(varObjRight));
    //     varEnv.setObject(new Sphere(varObjLeft));
    //     // varEnv.setObject(std::make_unique<Sphere>(varFloor));
    //     // varEnv.setObject(std::make_unique<Sphere>(varLeftWall));
    //     // varEnv.setObject(std::make_unique<Sphere>(varRightWall));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjMid));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjRight));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjLeft));
    //     varEnv.mbrLights.push_back(varLight);

    //     Camera varCamera = Camera(100,50,getPI()/2);
    //     varCamera.setTransform(new ViewMatrix(Point(0,1.5,-5), Point(0,1,0), Vector(0,1,0)));

    //     Canvas img = varCamera.render(varEnv);
    //     img.save();
    // }

    // void cameraRenderPatterns()
    // {
    //     PointSource varLightL = PointSource(Point(-10,10,-10), Color(1,1,1));
    //     PointSource varLightR = PointSource(Point(10,10,-10), Color(1,1,1));

    //     Plane varFloor = Plane();
    //     varFloor.setTransform(TranslationMatrix(0,-1,0));
    //     // varFloor.setTransform(*(TranslationMatrix(0,-1,0) * ScalingMatrix(1,1,1)));
    //     varFloor.setMaterial(Material());
    //     varFloor.mbrMaterial->setPattern(new PatternChecker(Color(0,0,0), Color(1,1,1)));
    //     // varFloor.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(10,1,10));

    //     Plane varLeftWall = Plane();
    //     varLeftWall.setTransform(*IdentityMatrix(4,4).translate(0,0,5)->rotateY(-getPI()/4)->rotateX(getPI()/2));
    //     // varLeftWall.setTransform(*(*(*(TranslationMatrix(0,10,5) * YRotationMatrix(-getPI()/4)) * XRotationMatrix(getPI()/2)) * ScalingMatrix(0.1,1,0.1)));
    //     varLeftWall.setMaterial(Material());
    //     varLeftWall.mbrMaterial->setPattern(new PatternGradient(Color(1,0,0), Color(0,0,1)));
    //     varLeftWall.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(2,2,2));

    //     Plane varRightWall = Plane();
    //     varRightWall.setTransform(*IdentityMatrix(4,4).translate(0,0,5)->rotateY(getPI()/4)->rotateX(getPI()/2));
    //     // varRightWall.setTransform(*(*(*(TranslationMatrix(0,10,5) * YRotationMatrix(getPI()/4)) * XRotationMatrix(getPI()/2)) * ScalingMatrix(0.1,1,0.1)));
    //     varRightWall.setMaterial(Material());
    //     varRightWall.mbrMaterial->setPattern(new PatternRing(Color(1,0,0), Color(1,1,1)));
    //     // varRightWall.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(10,1,10));

    //     Sphere varObjMid = Sphere();
    //     varObjMid.setTransform(IdentityMatrix(4,4).translate(0,2,-6)->scale(2,2,2));
    //     // varObjMid.setTransform(TranslationMatrix(-0.5,0.6,0.5).scale(2,0.5,2));
    //     varObjMid.setMaterial(Material());
    //     varObjMid.mbrMaterial->mbrColor = Color(0.1,1,0.5);
    //     varObjMid.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjMid.mbrMaterial->mbrSpecular = 0.3;
    //     varObjMid.mbrMaterial->setPattern(new PatternGradient(Color(1,0,0), Color(0,0,1)));
    //     varObjMid.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(2,2,2));
    //     varObjMid.mbrMaterial->mbrReflective = 1;

    //     Sphere varObjRight = Sphere();
    //     varObjRight.setTransform(IdentityMatrix(4,4).translate(6,2,-6)->scale(2,2,2));
    //     // varObjRight.setTransform(*(TranslationMatrix(1.5,0.5,-0.5) * ScalingMatrix(2,0.5,2))); 
    //     varObjRight.setMaterial(Material());
    //     varObjRight.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjRight.mbrMaterial->mbrSpecular = 0.3;
    //     varObjRight.mbrMaterial->setPattern(new PatternStripe(Color(1,0,0), Color(0,0,1)));
    //     varObjRight.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(0.25,0.25,0.25));
    //     varObjRight.mbrMaterial->mbrReflective = 1;

    //     Sphere varObjLeft = Sphere();
    //     varObjLeft.setTransform(IdentityMatrix(4,4).translate(-6,2,-6)->scale(2,2,2));
    //     // varObjLeft.setTransform(*(TranslationMatrix(-1.5,0.33,-2) * ScalingMatrix(0.33,0.33,0.33))); 
    //     varObjLeft.setMaterial(Material());
    //     varObjLeft.mbrMaterial->mbrColor = Color(1,0.8,0.1);
    //     varObjLeft.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjLeft.mbrMaterial->mbrSpecular = 0.3;
    //     varObjLeft.mbrMaterial->mbrReflective = 1;

    //     World varEnv = World();
    //     varEnv.setObject(new Plane(varFloor));
    //     varEnv.setObject(new Plane(varLeftWall));
    //     varEnv.setObject(new Plane(varRightWall));
    //     varEnv.setObject(new Sphere(varObjMid));
    //     varEnv.setObject(new Sphere(varObjRight));
    //     varEnv.setObject(new Sphere(varObjLeft));
    //     // varEnv.setObject(std::make_unique<Sphere>(varFloor));
    //     // varEnv.setObject(std::make_unique<Sphere>(varLeftWall));
    //     // varEnv.setObject(std::make_unique<Sphere>(varRightWall));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjMid));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjRight));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjLeft));
    //     varEnv.mbrLights.push_back(varLightL);
    //     //varEnv.mbrLights.push_back(varLightR);

    //     Camera varCamera = Camera(100,50,getPI()/2);
    //     varCamera.setTransform(new ViewMatrix(Point(0,1.5,-20), Point(0,1,0), Vector(0,1,0)));

    //     Canvas img = varCamera.render(varEnv);
    //     img.save();
    // }

    // void cameraRenderReflections()
    // {
    //     PointSource varLightL = PointSource(Point(-10,10,-10), Color(1,1,1));
    //     PointSource varLightR = PointSource(Point(10,10,-10), Color(1,1,1));

    //     Plane varFloor = Plane();
    //     varFloor.setTransform(TranslationMatrix(0,-1,0));
    //     // varFloor.setTransform(*(TranslationMatrix(0,-1,0) * ScalingMatrix(1,1,1)));
    //     varFloor.setMaterial(Material());
    //     varFloor.mbrMaterial->setPattern(new PatternChecker(Color(0,0,0), Color(1,1,1)));
    //     // varFloor.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(10,1,10));

    //     Plane varLeftWall = Plane();
    //     varLeftWall.setTransform(*IdentityMatrix(4,4).translate(0,0,5)->rotateY(-getPI()/4)->rotateX(getPI()/2));
    //     // varLeftWall.setTransform(*(*(*(TranslationMatrix(0,10,5) * YRotationMatrix(-getPI()/4)) * XRotationMatrix(getPI()/2)) * ScalingMatrix(0.1,1,0.1)));
    //     varLeftWall.setMaterial(Material());
    //     varLeftWall.mbrMaterial->setPattern(new PatternGradient(Color(1,0,0), Color(0,0,1)));
    //     varLeftWall.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(2,2,2));

    //     Plane varRightWall = Plane();
    //     varRightWall.setTransform(*IdentityMatrix(4,4).translate(0,0,5)->rotateY(getPI()/4)->rotateX(getPI()/2));
    //     // varRightWall.setTransform(*(*(*(TranslationMatrix(0,10,5) * YRotationMatrix(getPI()/4)) * XRotationMatrix(getPI()/2)) * ScalingMatrix(0.1,1,0.1)));
    //     varRightWall.setMaterial(Material());
    //     varRightWall.mbrMaterial->setPattern(new PatternRing(Color(1,0,0), Color(1,1,1)));
    //     // varRightWall.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(10,1,10));

    //     Sphere varObjMid = Sphere();
    //     varObjMid.setTransform(IdentityMatrix(4,4).translate(0,2,-6)->scale(2,2,2));
    //     // varObjMid.setTransform(TranslationMatrix(-0.5,0.6,0.5).scale(2,0.5,2));
    //     varObjMid.setMaterial(Material());
    //     varObjMid.mbrMaterial->mbrColor = Color(0.1,1,0.5);
    //     varObjMid.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjMid.mbrMaterial->mbrSpecular = 0.3;
    //     varObjMid.mbrMaterial->setPattern(new PatternGradient(Color(1,0,0), Color(0,0,1)));
    //     varObjMid.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(2,2,2));
    //     varObjMid.mbrMaterial->mbrReflective = 1;

    //     Sphere varObjRight = Sphere();
    //     varObjRight.setTransform(IdentityMatrix(4,4).translate(6,2,-6)->scale(2,2,2));
    //     // varObjRight.setTransform(*(TranslationMatrix(1.5,0.5,-0.5) * ScalingMatrix(2,0.5,2))); 
    //     varObjRight.setMaterial(Material());
    //     varObjRight.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjRight.mbrMaterial->mbrSpecular = 0.3;
    //     varObjRight.mbrMaterial->setPattern(new PatternStripe(Color(1,0,0), Color(0,0,1)));
    //     varObjRight.mbrMaterial->mbrPattern->setTransform(ScalingMatrix(0.25,0.25,0.25));
    //     varObjRight.mbrMaterial->mbrReflective = 1;

    //     Sphere varObjLeft = Sphere();
    //     varObjLeft.setTransform(IdentityMatrix(4,4).translate(-6,2,-6)->scale(2,2,2));
    //     // varObjLeft.setTransform(*(TranslationMatrix(-1.5,0.33,-2) * ScalingMatrix(0.33,0.33,0.33))); 
    //     varObjLeft.setMaterial(Material());
    //     varObjLeft.mbrMaterial->mbrColor = Color(1,0.8,0.1);
    //     varObjLeft.mbrMaterial->mbrDiffuse = 0.7;
    //     varObjLeft.mbrMaterial->mbrSpecular = 0.3;
    //     varObjLeft.mbrMaterial->mbrReflective = 1;

    //     World varEnv = World();
    //     varEnv.setObject(new Plane(varFloor));
    //     varEnv.setObject(new Plane(varLeftWall));
    //     varEnv.setObject(new Plane(varRightWall));
    //     varEnv.setObject(new Sphere(varObjMid));
    //     varEnv.setObject(new Sphere(varObjRight));
    //     varEnv.setObject(new Sphere(varObjLeft));
    //     // varEnv.setObject(std::make_unique<Sphere>(varFloor));
    //     // varEnv.setObject(std::make_unique<Sphere>(varLeftWall));
    //     // varEnv.setObject(std::make_unique<Sphere>(varRightWall));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjMid));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjRight));
    //     // varEnv.setObject(std::make_unique<Sphere>(varObjLeft));
    //     varEnv.mbrLights.push_back(varLightL);
    //     //varEnv.mbrLights.push_back(varLightR);

    //     Camera varCamera = Camera(160,90,getPI()/2);
    //     varCamera.setTransform(new ViewMatrix(Point(0,1.5,-20), Point(0,1,0), Vector(0,1,0)));

    //     Canvas img = varCamera.render(varEnv);
    //     img.save();
    // }

    // void cameraRenderReflectRefract()
    // {
    //     // Camera varCamera = Camera(400,200,1.152);
    //     // Camera varCamera = Camera(160,90,1.152);
    //     Camera varCamera = Camera(160,90,getPI()/2);
    //     // varCamera.setTransform(new ViewMatrix(Point(-2.6,1.5,-3.9), Point(-0.6,1,-0.8), Vector(0,1,0)));
    //     varCamera.setTransform(new ViewMatrix(Point(0,1.5,-20), Point(0,1,0), Vector(0,1,0)));

    //     World varEnv = World();

    //     PointSource varLight = PointSource(Point(-4.9,4.9,-1), Color(1,1,1));
    //     varEnv.setLight(varLight);

    //     Material varWallMaterial = Material();
    //     varWallMaterial.setPattern(std::make_unique<PatternStripe>(Color(0.45,0.45,0.45), Color(0.55,0.55,0.55)).get());
    //     // varWallMaterial.mbrPattern->setTransform(IdentityMatrix(4,4).scale(0.25,0.25,0.25)->rotateY(1.5708));
    //     varWallMaterial.mbrPattern->setTransform(IdentityMatrix(4,4).rotateY(1.5708)->scale(0.25,0.25,0.25));
    //     varWallMaterial.mbrAmbient = 0;
    //     varWallMaterial.mbrDiffuse = 0.4;
    //     varWallMaterial.mbrSpecular = 0;
    //     varWallMaterial.mbrReflective = 0.3;

    //     Plane varFloor = Plane();
    //     varFloor.setTransform(YRotationMatrix(0.31415));
    //     varFloor.setMaterial(Material());
    //     varFloor.mbrMaterial->setPattern(new PatternChecker(Color(0.35,0.35,0.35), Color(0.65,0.65,0.65)));
    //     varFloor.mbrMaterial->mbrSpecular = 0;
    //     varFloor.mbrMaterial->mbrReflective = 0.4;
    //     varEnv.setObject(new Plane(varFloor));

    //     Plane varCeiling = Plane();
    //     varCeiling.setTransform(TranslationMatrix(0,5,0));
    //     varCeiling.setMaterial(Material());
    //     varCeiling.mbrMaterial->mbrColor = Color(0.8,0.8,0.8);
    //     varCeiling.mbrMaterial->mbrAmbient = 0.3;
    //     varCeiling.mbrMaterial->mbrSpecular = 0;
    //     varEnv.setObject(new Plane(varCeiling));

    //     Plane varWallWest = Plane();
    //     // varWallWest.setTransform(IdentityMatrix(4,4).rotateY(1.5708)->rotateX(1.5708)->translate(-5,0,0));
    //     varWallWest.setTransform(IdentityMatrix(4,4).translate(-5,0,0)->rotateY(1.5708)->rotateX(1.5708));
    //     varWallWest.setMaterial(Material(varWallMaterial));
    //     varEnv.setObject(new Plane(varWallWest));

    //     Plane varWallEast = Plane();
    //     // varWallEast.setTransform(IdentityMatrix(4,4).rotateY(1.5708)->rotateZ(1.5708)->translate(5,0,0));
    //     varWallEast.setTransform(IdentityMatrix(4,4).translate(5,0,0)->rotateY(1.5708)->rotateZ(1.5708));
    //     varWallEast.setMaterial(Material(varWallMaterial));
    //     varEnv.setObject(new Plane(varWallEast));

    //     Plane varWallNorth = Plane();
    //     // varWallNorth.setTransform(IdentityMatrix(4,4).rotateX(1.5708)->translate(0,0,5));
    //     varWallNorth.setTransform(IdentityMatrix(4,4).translate(0,0,5)->rotateX(1.5708));
    //     varWallNorth.setMaterial(Material(varWallMaterial));
    //     varEnv.setObject(new Plane(varWallNorth));

    //     Plane varWallSouth = Plane();
    //     // varWallSouth.setTransform(IdentityMatrix(4,4).rotateX(1.5708)->translate(0,0,-5));
    //     varWallSouth.setTransform(IdentityMatrix(4,4).translate(0,0,-5)->rotateX(1.5708));
    //     varWallSouth.setMaterial(Material(varWallMaterial));
    //     varEnv.setObject(new Plane(varWallSouth));

    //     Sphere varObjBg1 = Sphere();
    //     // varObjBg1.setTransform(IdentityMatrix(4,4).scale(.4,.4,.4)->translate(4.6,0.4,1));
    //     varObjBg1.setTransform(IdentityMatrix(4,4).translate(4.6,0.4,1)->scale(.4,.4,.4));
    //     varObjBg1.setMaterial(Material());
    //     varObjBg1.mbrMaterial->mbrColor = Color(0.8,0.5,0.3);
    //     varObjBg1.mbrMaterial->mbrShininess = 50;
    //     varEnv.setObject(new Sphere(varObjBg1));

    //     Sphere varObjBg2 = Sphere();
    //     // varObjBg2.setTransform(IdentityMatrix(4,4).scale(.3,.3,.3)->translate(4.7,0.3,4));
    //     varObjBg2.setTransform(IdentityMatrix(4,4).translate(4.7,0.3,4)->scale(.3,.3,.3));
    //     varObjBg2.setMaterial(Material());
    //     varObjBg2.mbrMaterial->mbrColor = Color(0.9,0.4,0.5);
    //     varObjBg2.mbrMaterial->mbrShininess = 50;
    //     varEnv.setObject(new Sphere(varObjBg2));

    //     Sphere varObjBg3 = Sphere();
    //     // varObjBg3.setTransform(IdentityMatrix(4,4).scale(.5,.5,.5)->translate(-1,0.5,4.5));
    //     varObjBg3.setTransform(IdentityMatrix(4,4).translate(-1,0.5,4.5)->scale(.5,.5,.5));
    //     varObjBg3.setMaterial(Material());
    //     varObjBg3.mbrMaterial->mbrColor = Color(0.4,0.9,0.6);
    //     varObjBg3.mbrMaterial->mbrShininess = 50;
    //     varEnv.setObject(new Sphere(varObjBg3));

    //     Sphere varObjBg4 = Sphere();
    //     // varObjBg4.setTransform(IdentityMatrix(4,4).scale(.3,.3,.3)->translate(-1.7,0.3,4.7));
    //     varObjBg4.setTransform(IdentityMatrix(4,4).translate(-1.7,0.3,4.7)->scale(.3,.3,.3));
    //     varObjBg4.setMaterial(Material());
    //     varObjBg4.mbrMaterial->mbrColor = Color(0.4,0.6,0.9);
    //     varObjBg4.mbrMaterial->mbrShininess = 50;
    //     varEnv.setObject(new Sphere(varObjBg4));

    //     Sphere varObjFg1 = Sphere();
    //     varObjFg1.setTransform(IdentityMatrix(4,4).translate(-0.6,1,0.6));
    //     varObjFg1.setMaterial(Material());
    //     varObjFg1.mbrMaterial->mbrColor = Color(1,0.3,0.2);
    //     varObjFg1.mbrMaterial->mbrSpecular = 0.4;
    //     varObjFg1.mbrMaterial->mbrShininess = 5;
    //     varEnv.setObject(new Sphere(varObjFg1));

    //     Sphere varObjFg2 = Sphere();
    //     // varObjFg2.setTransform(IdentityMatrix(4,4).scale(0.7,0.7,0.7)->translate(0.6,0.7,-0.6));
    //     varObjFg2.setTransform(IdentityMatrix(4,4).translate(0.6,0.7,-0.6)->scale(0.7,0.7,0.7));
    //     varObjFg2.setMaterial(Material());
    //     varObjFg2.mbrMaterial->mbrColor = Color(0,0,0.2);
    //     varObjFg2.mbrMaterial->mbrAmbient = 0;
    //     varObjFg2.mbrMaterial->mbrDiffuse = 0.4;
    //     varObjFg2.mbrMaterial->mbrSpecular = 0.9;
    //     varObjFg2.mbrMaterial->mbrShininess = 300;
    //     varObjFg2.mbrMaterial->mbrReflective = 0.9;
    //     varObjFg2.mbrMaterial->mbrTransparency = 0.9;
    //     varObjFg2.mbrMaterial->mbrRefractiveIndex = 1.5;
    //     varEnv.setObject(new Sphere(varObjFg2));

    //     Sphere varObjFg3 = Sphere();
    //     // varObjFg3.setTransform(IdentityMatrix(4,4).scale(0.5,0.5,0.5)->translate(-0.7,0.5,-0.8));
    //     varObjFg3.setTransform(IdentityMatrix(4,4).translate(-0.7,0.5,-0.8)->scale(0.5,0.5,0.5));
    //     varObjFg3.setMaterial(Material());
    //     varObjFg3.mbrMaterial->mbrColor = Color(0,0.2,0);
    //     varObjFg3.mbrMaterial->mbrAmbient = 0;
    //     varObjFg3.mbrMaterial->mbrDiffuse = 0.4;
    //     varObjFg3.mbrMaterial->mbrSpecular = 0.9;
    //     varObjFg3.mbrMaterial->mbrShininess = 300;
    //     varObjFg3.mbrMaterial->mbrReflective = 0.9;
    //     varObjFg3.mbrMaterial->mbrTransparency = 0.9;
    //     varObjFg3.mbrMaterial->mbrRefractiveIndex = 1.5;
    //     varEnv.setObject(new Sphere(varObjFg3));

    //     Canvas img = varCamera.render(varEnv);
    //     img.save();
    // }
};

#endif