add_executable(matrix 
main.cpp)

set_target_properties(matrix PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(matrix PRIVATE
        /W4
    )
else()
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)
