# Target names
NAME = minishell
# Directories and source files
SRC = main.c \
executor/process_handler.c \
executor/child_process_handler.c \
executor/parent_process_handler.c \
executor/child_status.c \
executor/file_handler.c \
executor/exebuiltins.c \
executor/pipe_utils.c \
executor/executor.c \
executor/execute_heredoc.c \
executor/executor_utils.c \
executor/redirections.c \
executor/redirections_utils.c \
builtins/builtins_utils.c \
builtins/cd.c \
builtins/echo.c \
builtins/export_builtin.c \
builtins/export_builtin_utils.c \
builtins/pwd.c \
builtins/env.c \
builtins/unset.c \
builtins/exit.c \
parsing/check_expand.c \
parsing/expand_utils.c \
parsing/expander.c \
parsing/parsing.c \
parsing/parsing_free.c \
parsing/parsing_free2.c \
parsing/parsing_utils.c \
parsing/build_lst.c \
parsing/redir_copy_utils.c \
parsing/redir_process.c \
parsing/redir_struct.c \
parsing/redir_utils.c \
parsing/signal_handling.c \
parsing/signal_handling_utils.c \
parsing/check_syntax.c \
lexer/lexer.c \
lexer/lexer_error.c \
lexer/lexer_utils.c \
lexer/lexer_utils2.c \
lexer/lexer_utils3.c \
lexer/lexer_init.c \
lexer/remove_quotes.c \
env_lst/env_lst.c \
env_lst/env_lst_free.c \
env_lst/env_lst_utils.c \
env_lst/env_lst_utils2.c \
error.c \
utils.c \
string_utils.c \
printer.c \

OBJ = $(SRC:.c=.o)

# Libraries and their paths
LIBS = -Llib/libft -lft \
       -Llib/ft_printf -lftprintf \
       -lreadline -lhistory  # Add readline and history libraries

# Compiler and compilation flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# ANSI escape codes for colored output
BLUE = \033[0;34m
RESET = \033[0m

# Default target: build the main executable
all: $(NAME)
	@echo $(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

# Rule to build the main executable
$(NAME): $(OBJ)
	@make -C lib/libft
	@make -C lib/ft_printf
	@echo "$(BLUE)$(CC) -o $(NAME) $(OBJ) $(LIBS)$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

# Pattern rule to compile .c files to .o files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Debug target: clean and rebuild with debug information
debug: CFLAGS += -g
debug: fclean all

# Test target: build with only the -g flag for memory leak testing
test: CFLAGS := -g
test: $(OBJ)
	@make -C lib/libft
	@make -C lib/ft_printf
	@echo "$(BLUE)$(CC) -o $(NAME) $(OBJ) $(LIBS)$(RESET)"
	@$(CC) -o $(NAME) $(OBJ) $(LIBS)

# Valgrind test target: build with -g and run with valgrind
val: CFLAGS := -g
val: $(OBJ)
	@make -C lib/libft
	@make -C lib/ft_printf
	@echo "$(BLUE)$(CC) -o $(NAME) $(OBJ) $(LIBS)$(RESET)"
	@$(CC) -o $(NAME) $(OBJ) $(LIBS)
	@echo "$(BLUE)Running $(NAME) with valgrind...$(RESET)"
	@valgrind --suppressions=readline.supp --leak-check=full -s ./$(NAME)


# Clean target: remove object files
clean:
	@make clean -C lib/libft
	@make clean -C lib/ft_printf
	@rm -f $(OBJ)

# Full clean target: clean and remove the main executable
fclean: clean
	@make fclean -C lib/libft
	@make fclean -C lib/ft_printf
	@rm -f $(NAME)

# Rebuild target: full clean and build all
re: fclean all

# Declare the list of phony targets
.PHONY: all clean fclean re debug test

# Debug target without changing the CFLAGS again
debug: all
