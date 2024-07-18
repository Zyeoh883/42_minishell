# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) #-fsanitize=address -g #-std=c99
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
			abstract_syntax_tree/free_ast/free_ast.c \
			\
			create/create_node.c \
			create/variables.c \
			create/var_lst_functions.c \
			\
			execute/execute.c \
			execute/execute_simple_cmd.c \
			execute/setup_redir.c \
			execute/execute_pipes.c \
			execute/execute_subshell.c \
			execute/execute_and_or.c \
			execute/execute_execve.c \
			execute/exit_status.c \
			execute/execute_utils.c \
				\
				execute/builtins/execute_builtins.c \
				execute/builtins/execute_export.c \
				execute/builtins/execute_builtins_utils.c \
				execute/builtins/execute_cd.c \
				execute/builtins/execute_unset.c \
				execute/builtins/execute_echo.c \
				execute/builtins/execute_assignment.c \
				\
				execute/handle_quotes_n_expansion/trim_quotes_n_expand.c \
				execute/handle_quotes_n_expansion/trim_quotes_n_expand_utils.c \
				execute/handle_quotes_n_expansion/ft_split_cmd_str_after_expansion.c \
				execute/handle_quotes_n_expansion/expand_str.c \
				execute/handle_quotes_n_expansion/new_method.c \
				\
				execute/wildcard/trim_quotes_n_expand_asterisk_args.c \
				execute/wildcard/trim_quotes_n_expand_asterisk_redirs.c \
				execute/wildcard/expand_asterisk_utils.c \
				execute/wildcard/tokenize_asterisk.c \
				execute/wildcard/get_directory_entries.c \
			\
			utils/free.c \
			utils/utils1.c \
			utils/extra.c \
			\
			main.c \
			readline.c \
			\
			# utils/utils2.c \

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
