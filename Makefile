CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -fsanitize=address -g
INCLUDES = -I ./inc/ -I$(LIBFT_DIR)

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;38;5;166m
# SRCS
SRCDIR = srcs/
SRCS_FIL = \
			main_w_readline.c \
			create/create_node.c \
			create/piping.c \
			execute/variables.c \
			execute/handle_quotes_n_expansion.c \
			execute/handle_quotes_n_expansion2.c \
			execute/lst_functions.c \
			execute/exit_status.c \
			execute/execute.c \
			execute/execute_execve.c \
			execute/execute_builtins.c \
			free.c \
			utils/utils1.c \
			utils/utils2.c \

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
