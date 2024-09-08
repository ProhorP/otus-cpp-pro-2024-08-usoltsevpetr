add_executable(ip_filter main.cpp)
add_library(IpV4 IpV4.cpp)

target_link_libraries(ip_filter PRIVATE
    IpV4
)

set_target_properties(ip_filter IpV4 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(WITH_GOOGLE_TEST)

    add_executable(tests
        tests.cpp
    )

    # Link test target against gtest libraries
    target_link_libraries(
        tests PRIVATE
        IpV4
        gtest
        gtest_main
    )

    set_target_properties(tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
endif()

if(MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(IpV4 PRIVATE
        /W4
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(tests PRIVATE
            /W4
        )
    endif()
else()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(IpV4 PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(tests PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(tests tests)
endif()

