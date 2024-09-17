cmake_minimum_required(VERSION 3.25)
project(minishell C)
set(CMAKE_C_STANDARD 99)

# Add the libft library
add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libft/libft.a)

# Add the printf library
add_library(ft_printf STATIC IMPORTED)
set_target_properties(ft_printf PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/ft_printf/libftprintf.a)

add_executable(minishell
        main.c
        executor.c
        executor_utils.c
        error.c
        child_status.c
        #test
)

target_link_libraries(minishell PRIVATE libft ft_printf)