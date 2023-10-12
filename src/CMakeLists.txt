set (SOURCES main.cpp
camera.h camera.cpp camera.test.cpp
canvas.h canvas.cpp canvas.test.cpp
color.h color.cpp color.test.cpp
comparinator.h comparinator.cpp comparinator.test.cpp
datetime.h datetime.cpp
intersection.h intersection.cpp intersection.test.cpp
matrix.h matrix.cpp matrix.test.cpp
pattern.h pattern.cpp pattern.test.cpp
pch.h pch.cpp
ray.h ray.cpp ray.test.cpp
form.h form.cpp form.test.cpp
tuple.h tuple.cpp tuple.test.cpp
light.h light.cpp light.test.cpp
material.h material.cpp material.test.cpp
world.h world.cpp world.test.cpp
raytracer.h raytracer.cpp
)
add_executable(main ${SOURCES})
target_link_libraries(main ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)