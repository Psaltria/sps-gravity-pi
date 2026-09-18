cmake_minimum_required(VERSION 3.25)

project(
    sps-gravity-pi
    VERSION 0.1.0
    LANGUAGES CXX
)

# Add dependencies ----------------------------------
find_package(Eigen3 CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(
    GPHOTO2
    REQUIRED
    IMPORTED_TARGET
    libgphoto2
)

set(CSPICE_ROOT "${CMAKE_SOURCE_DIR}/external/cspice")

add_library(CSPICE::cspice STATIC IMPORTED)

set_target_properties(CSPICE::cspice PROPERTIES
    IMPORTED_LOCATION
        "${CSPICE_ROOT}/lib/cspice.a"

    INTERFACE_INCLUDE_DIRECTORIES
        "${CSPICE_ROOT}/include"
)

target_link_libraries(sps-gravity-pi
    PRIVATE
        CSPICE::cspice
        m
)

# Main executable -----------------------------------
add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	Eigen3::Eigen
    PkgConfig::GPHOTO2
)

target_sources(${PROJECT_NAME} PRIVATE
    "src/main.cpp" 
 "include/cam/Camera_system.h" "src/cam/Camera_system.cpp" "include/gravity/n_body.h")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/kernels"
            "$<TARGET_FILE_DIR:sps-gravity-pi>/kernels"
)
