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
        builtins/builtins_utils.c
        builtins/cd.c
        builtins/echo.c
        builtins/env.c
        builtins/exit.c
        builtins/export_builtin.c
        builtins/export_builtin.c
        builtins/export_builtin_utils.c
        builtins/pwd.c
        builtins/unset.c
        env_lst/env_lst.c
        env_lst/env_lst.c
        env_lst/env_lst_free.c
        env_lst/env_lst_utils.c
        env_lst/env_lst_utils.c
        env_lst/env_lst_utils2.c
        env_lst/env_lst_utils2.c
        error.c
        executor/child_process_handler.c
        executor/child_status.c
        executor/exebuiltins.c
        executor/execute_heredoc.c
        executor/executor.c
        executor/executor_utils.c
        executor/file_handler.c
        executor/parent_process_handler.c
        executor/pipe_utils.c
        executor/process_handler.c
        executor/redirections.c
        executor/redirections_utils.c
        lexer/lexer.c
        lexer/lexer_error.c
        lexer/lexer_init.c
        lexer/lexer_utils.c
        lexer/lexer_utils2.c
        lexer/lexer_utils3.c
        lib/env_lst.h
        main.c
        parsing/build_lst.c
        parsing/check_expand.c
        parsing/check_syntax.c
        parsing/expand_utils.c
        parsing/expander.c
        parsing/parsing.c
        parsing/parsing_free.c
        parsing/parsing_free2.c
        parsing/parsing_utils.c
        parsing/prompt_init.c
        parsing/redir_process.c
        parsing/redir_struct.c
        parsing/redir_utils.c
        parsing/signal_handling.c
        parsing/signal_handling.c
        parsing/signal_handling_utils.c
        printer.c
        utils.c
        parsing/parsing_free2.c
        lexer/remove_quotes.c
)

target_link_libraries(minishell PRIVATE libft ft_printf readline)