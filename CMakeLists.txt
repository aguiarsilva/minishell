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
        builtins/pwd.c
        builtins/cd.c
        builtins/unset.c
        parsing/parsing.c
        lexer/lexer.c
        lexer/lexer_utils.c
        parsing/prompt_init.c
        parsing/build_lst.c
        executor/child_process_handler.c
        executor/parent_process_handler.c
        executor/redirections.c
        executor/pipe_utils.c
        executor/process_handler.c
        env_lst/env_lst.c
        parsing/redir_struct.c
        lexer/lexer.c
        printer.c
        env_lst/env_lst_utils.c
        builtins/export_builtin.c
        env_lst/env_lst_utils2.c
        parsing/parsing_utils.c
        parsing/parsing_free.c
        parsing/redir_utils.c
        parsing/signal_handling.c
        executor/execute_heredoc.c
        builtins/env.c
        builtins/export_builtin_utils.c
        parsing/signal_handling.c
        parsing/check_syntax.c
        builtins/exit.c
        parsing/expander.c
        parsing/expand_utils.c
        parsing/check_expand.c
        lexer/lexer_init.c
        lexer/lexer_utils2.c
        lexer/lexer_utils3.c
        parsing/redir_process.c
        parsing/signal_handling_utils.c
        env_lst/env_lst.c
        env_lst/env_lst_utils.c
        env_lst/env_lst_utils2.c
        lib/env_lst.h
        env_lst/env_lst_free.c
)

target_link_libraries(minishell PRIVATE libft ft_printf readline)