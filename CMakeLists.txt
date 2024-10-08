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
        error.c
        child_status.c
        utils.c
        executor/executor.c
        executor/executor_utils.c
        executor/exebuiltins.c
        executor/test.c
        builtins/echo.c
        builtins/builtins_utils.c
        parsing/cleanup.c
        parsing/parsing.c
        parsing/parsing_utils.c
        parsing/prompt_init.c
        parsing/token.c
        parsing/utils_list.c
        parsing/check.c
        executor/file_handler.c
        executor/child_process_handler.c
        executor/parent_process_handler.c

)

target_link_libraries(minishell PRIVATE libft ft_printf readline)