add_executable(alloc 
main.cpp)

set_target_properties(alloc PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(alloc PRIVATE
        /W4
    )
else()
    target_compile_options(alloc PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS alloc RUNTIME DESTINATION bin)
