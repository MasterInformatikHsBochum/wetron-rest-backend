cmake_minimum_required(VERSION 3.0)
project(WeTronRestBackend)

include(ExternalProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(pistache.io
    GIT_REPOSITORY https://github.com/oktal/pistache
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(
    ${EXTERNAL_INSTALL_LOCATION}/include
)
link_directories(
    ${EXTERNAL_INSTALL_LOCATION}/lib
)

add_executable(wetron-rest-backend
    main.cpp
)
add_dependencies(wetron-rest-backend
    pistache.io
)
target_link_libraries(wetron-rest-backend
    libnet_static.a
    pthread
)
