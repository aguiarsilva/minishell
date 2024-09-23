# Target names
NAME = minishell
# Directories and source files
SRC = main.c \
executor/executor.c \
executor/executor_utils.c \
executor/test.c \
executor/exebuiltins.c \
builtins/builtins_utils.c \
builtins/echo.c \
error.c \
utils.c \
child_status.c \


OBJ = $(SRC:.c=.o)

# Libraries and their paths
LIBS = -Llib/libft -lft \
       -Llib/ft_printf -lftprintf

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
