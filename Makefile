CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99	#-fsanitize=address -g
INCLUDES = -I ./inc/ -I$(LIBFT_DIR)

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;38;5;166m
# SRCS
SRCDIR = srcs/
SRCS_FIL = \
			create/create_node.c \
			create/piping.c \
			create/variables.c \
			create/lst_functions.c \
			execute/execute.c \
			utils/utils1.c \
			utils/utils2.c \
			main_w_readline.c \
			free.c \
			builtins.c \
			readline.c \
			\
			tokenize/tokenize.c \
			tokenize/tokenize_utils.c \
			tokenize/is_token_valid.c \
			tokenize/is_valid_utils.c \
			tokenize/validate_tokens.c \
			tokenize/format_token.c \
			tokenize/here_doc.c

SRCS = $(addprefix $(SRCDIR), $(SRCS_FIL))

# OBS
OBJDIR = objs/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

# LIBRARIES
LIBFT_DIR = libft/
LIBFT.A = $(LIBFT_DIR)libft.a

NAME = minishell

all:  $(OBJDIR) $(NAME)

bonus: all

$(OBJDIR):
		@mkdir -p $(OBJDIR) $(addprefix $(OBJDIR), $(dir $(SRCS_FIL)))

$(NAME): $(OBJS)
		@make -C $(LIBFT_DIR)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline && echo "$(GREEN)$(NAME) was created$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c
		@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) && echo "$(GREEN)object files were created$(RESET)"


RM = rm -rf

clean:
		@ $(RM) $(OBJDIR) && echo "$(ORANGE)object files were deleted$(RESET)"
		@make clean -C ${LIBFT_DIR} && echo "$(ORANGE)libft object files were deleted$(RESET)"

fclean: clean
		@$(RM) $(NAME) && echo "$(ORANGE)$(NAME)was deleted$(RESET)"
		@make fclean -C $(LIBFT_DIR) && echo "$(ORANGE)libft.a was deleted$(RESET)"

re: fclean all


.PHONY: all clean fclean re bonus
# ^ .PHONY -> informs computer that above phrases are not files
