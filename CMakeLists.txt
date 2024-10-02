cmake_minimum_required(VERSION 3.5)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(otus-cpp-pro-2024-08-usoltsevpetr VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)
option(WITH_GOOGLE_TEST "Whether to build Google test" ON)

add_subdirectory(googletest-1.15.2)

# add_subdirectory(hw01)
# add_subdirectory(hw02)
# add_subdirectory(hw03)
add_subdirectory(hw04)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT usoltsev05@mail.ru)
include(CPack)
