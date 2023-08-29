cmake_minimum_required(VERSION 3.6)

include(GNUInstallDirs)

file(GLOB_RECURSE of_libs
     LIST_DIRECTORIES false
     ${SRC_PREFIX}/*.a)

list(FILTER of_libs EXCLUDE REGEX "/emscripten/")

file(GLOB_RECURSE of_includes
     LIST_DIRECTORIES false
     ${SRC_PREFIX}/libs/openFrameworks/of*.h)

file(GLOB_RECURSE of_inlines
     LIST_DIRECTORIES false
     ${SRC_PREFIX}/libs/openFrameworks/of*.inl)

file(GLOB of_dep_include_dirs
     LIST_DIRECTORIES true
     ${SRC_PREFIX}/libs/*/${CMAKE_INSTALL_INCLUDEDIR})

file(COPY ${of_libs}
     DESTINATION ${DST_PREFIX}/${CMAKE_INSTALL_LIBDIR})

file(COPY ${of_includes} ${of_inlines}
     DESTINATION ${DST_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})

file(COPY ${of_dep_include_dirs}
     DESTINATION ${DST_PREFIX})
