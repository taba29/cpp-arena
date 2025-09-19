add_executable(test_day1_basic test_day1_basic.cpp)
add_test(NAME day1_basic COMMAND test_day1_basic)

add_executable(test_day3_physics test_day3_physics.cpp)
add_test(NAME day3_physics COMMAND test_day3_physics)

add_executable(test_day4_physics test_day4_physics.cpp)
add_test(NAME day4_physics COMMAND test_day4_physics)

add_executable(test_day5_ai test_day5_ai.cpp)
add_test(NAME day5_ai COMMAND test_day5_ai)

add_executable(test_day6_geometry test_day6_geometry.cpp)
add_test(NAME day6_geometry COMMAND test_day6_geometry)

add_executable(test_day7_integration test_day7_integration.cpp)
add_test(NAME day7_integration COMMAND test_day7_integration)
