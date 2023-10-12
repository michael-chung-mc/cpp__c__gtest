#include "pch.h"
#include "raytracer.h"

int main(int argc, char **argv)
{
	// int firepower = 10;
	// std::cout << "Firing: " << firepower << std::endl;
	// Simulation sim;
	// sim.fire(firepower);

	RayTracer rh = RayTracer();
	rh.test();

    ::testing::InitGoogleTest( &argc, argv);
    return RUN_ALL_TESTS();

	// 	return 0;
}