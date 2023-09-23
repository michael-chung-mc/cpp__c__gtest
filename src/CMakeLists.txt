set (SOURCES main.cpp
canvas.h canvas.cpp canvas_test_unit.cpp
color.h color.cpp color_test_unit.cpp
comparinator.h comparinator.cpp comparinator_test_unit.cpp
datetime.h datetime.cpp
pch.h pch.cpp
projectile.cpp
tuple.h tuple.cpp tuple_test_unit.cpp
)
add_executable(main ${SOURCES})
target_link_libraries(main ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)