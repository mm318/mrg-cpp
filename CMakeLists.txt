# ========================================================
# ===================== CMake Settings ===================
# ========================================================
cmake_minimum_required(VERSION 3.3)

include(ExternalProject)
include(GNUInstallDirs)
include(ProcessorCount)

ProcessorCount(NUM_CPUS)
if(NUM_CPUS EQUAL 0)
    set(NUM_CPUS 1)
endif()

# ========================================================
# ===================== User Settings ====================
# ========================================================

project(mrg-cpp)

# ---------------------- App name  -----------------------
set(APP_NAME mrg_axon_model)

# --------------------- Source Files ---------------------
set(${APP_NAME}_SOURCE_FILES
    src/MRG_main.cpp
    src/MRG_init.cpp
    src/MRG_ode.cpp
    src/ofApp.cpp
    src/utils/utils.cpp
)

# ========================================================


# ===============================================================
# ==================== External Dependencies ====================
# ===============================================================

find_package(PkgConfig) 
pkg_check_modules(GLIB REQUIRED glib-2.0) 
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(CAIRO REQUIRED cairo)

ExternalProject_Add(armadillo
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/external_libs/armadillo-9.200.5"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>
                    "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}"
)

ExternalProject_Add(sundials
    URL "${CMAKE_SOURCE_DIR}/external_libs/sundials-4.0.2.tar.gz"
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
)

ExternalProject_Add(openframeworks
    URL "${CMAKE_SOURCE_DIR}/external_libs/of_v0.11.2_linux64gcc6_release"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND <SOURCE_DIR>/scripts/linux/compileOF.sh -j${NUM_CPUS}
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ${CMAKE_COMMAND}
                    -DSRC_PREFIX=<SOURCE_DIR>
                    -DDST_PREFIX=${CMAKE_BINARY_DIR}
                    -P ${CMAKE_SOURCE_DIR}/external_libs/install_openframeworks.cmake
)

link_directories("${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

# ===============================================================


# =======================================================
# ==================== Build Project ====================
# =======================================================

add_executable(${APP_NAME}
    ${${APP_NAME}_SOURCE_FILES}
)

target_include_directories(${APP_NAME} BEFORE
    PRIVATE "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}"
            ${GLIB_INCLUDE_DIRS}
            ${GSTREAMER_INCLUDE_DIRS}
            ${CAIRO_INCLUDE_DIRS}
)

target_link_libraries(${APP_NAME}
    libsundials_cvode.a
    libsundials_sunlinsoldense.a
    libsundials_sunmatrixdense.a
    libsundials_nvecserial.a
    libopenFrameworks.a
    GLEW
    GLU
    GL
    glut
    glfw
    openal
    libPocoUtil.a
    libPocoFoundation.a
    fontconfig
    freetype
    freeimage
    X11
    ${GSTREAMER_LIBRARIES}
    ${CAIRO_LIBRARIES}
    ${GLIB_LIBRARIES}
    uriparser
    boost_filesystem
    boost_system
    pthread
)

add_dependencies(${APP_NAME} armadillo sundials openframeworks)

set_target_properties(${APP_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

file(COPY reference/activateF.txt DESTINATION bin/)

# =======================================================
