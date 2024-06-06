# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -fsanitize=address -g #-std=c99 
INCLUDES = -Iinc -I$(LIBFT_DIR) -I$(READLINE_DIR)

# Output executable
NAME = minishell

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;38;5;166m

# Source files
SRCDIR = srcs/

SRCS_FIL = \
			tokenize/tokenize.c \
			tokenize/tokenize_utils.c \
			tokenize/is_token_valid.c \
			tokenize/is_valid_utils.c \
			tokenize/validate_tokens.c \
			tokenize/format_token.c \
			tokenize/here_doc.c \
			\
			abstract_syntax_tree/create_ast.c \
			abstract_syntax_tree/create_ast_utils.c \
			abstract_syntax_tree/print_ast.c \
			\
			create/create_node.c \
			\
			execute/variables.c \
			execute/handle_quotes_n_expansion.c \
			execute/handle_quotes_n_expansion2.c \
			execute/lst_functions.c \
			execute/exit_status.c \
			execute/execute.c \
			execute/execute_execve.c \
			execute/execute_builtins.c \
			utils/free.c \
			utils/utils1.c \
			utils/extra.c \
			utils/utils2.c \
			\
			main.c \
			readline.c \
			\

SRCS = $(addprefix $(SRCDIR), $(SRCS_FIL))

# Object files
OBJDIR = objs/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

# Libraries
LIBFT_DIR = libft/
LIBFT_A = $(LIBFT_DIR)libft.a

READLINE_DIR = readline
READLINE_LIB = -L$(READLINE_DIR) -lreadline -lncurses -lhistory

# Build targets
all: $(OBJDIR) $(NAME)

bonus: all

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(addprefix $(OBJDIR), $(dir $(SRCS_FIL)))

$(NAME): $(OBJS)
	@make -C $(READLINE_DIR) > /dev/null
	@make -C $(LIBFT_DIR)
	@$(CC) $(LIBFT_A) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft $(READLINE_LIB) && echo "$(GREEN)$(NAME) was created$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ && echo "$(GREEN)object files were created$(RESET)"

# Cleanup
RM = rm -rf

clean:
	@$(RM) $(OBJDIR) && echo "$(ORANGE)object files were deleted$(RESET)"
	@make clean -C $(LIBFT_DIR) && echo "$(ORANGE)libft object files were deleted$(RESET)"
	@make clean -C $(READLINE_DIR) > /dev/null && echo "$(ORANGE)readline object files were deleted$(RESET)"

fclean: clean
	@$(RM) $(NAME) && echo "$(ORANGE)$(NAME) was deleted$(RESET)"
	@make fclean -C $(LIBFT_DIR) && echo "$(ORANGE)libft.a was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
