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
        executor/child_status.c
        utils.c
        executor/executor.c
        executor/executor_utils.c
        executor/exebuiltins.c
        builtins/echo.c
        builtins/builtins_utils.c
        builtins/export_builtin.c
        parsing/cleanup.c
        parsing/parsing.c
        lexer/lexer.c
        lexer/lexer_utils.c
        parsing/prompt_init.c
        parsing/token.c
        parsing/utils_list.c
        parsing/check.c
        parsing/handle_quotes.c
        executor/child_process_handler.c
        executor/parent_process_handler.c
        executor/redirections.c
        executor/pipe_utils.c
        executor/process_handler.c
        env_list.c
        parsing/redir_token.c
        lexer/lexer.c
        printer.c
        env_list_utils.c
        builtins/export_builtin.c
        env_utils.c
        builtins/pwd.c
        builtins/cd.c

)

target_link_libraries(minishell PRIVATE libft ft_printf readline)