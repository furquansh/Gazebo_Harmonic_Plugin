cmake_minimum_required(VERSION 3.5)
project(bcr_bot)

find_package(ament_cmake REQUIRED)


find_package(gz-sim8 REQUIRED)
find_package(gz-plugin2 REQUIRED)
find_package(gz-transport13 REQUIRED)

add_library(DummySensor SHARED
  scripts/dummy_sensor.cc
)

target_include_directories(DummySensor PUBLIC include)

target_link_libraries(DummySensor
  gz-sim8::gz-sim8
  gz-plugin2::gz-plugin2
  gz-transport13::gz-transport13
)

install(TARGETS DummySensor LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)


install(
    DIRECTORY launch urdf config 
    DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY launch meshes models urdf worlds rviz scripts 
    DESTINATION share/${PROJECT_NAME}/
)

install( DIRECTORY config/
         DESTINATION share/${PROJECT_NAME}/config)
         
         
install(PROGRAMS scripts/remapper.py
        DESTINATION lib/${PROJECT_NAME})

        install(PROGRAMS scripts/dummy_sensor.cc
        DESTINATION lib/${PROJECT_NAME})

ament_package()
