add_executable(print_ip 
main.cpp)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
else()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)
