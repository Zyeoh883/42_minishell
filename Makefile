NAME = minishell
BONUS_NAME = 
LIBFT = libft.a
CC = gcc
RM = rm -rf
MKDIR = mkdir -p
FSAN = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror ${FSAN}

RED = \033[0;91m
GREEN = \033[92m
RESET = \033[0m

SRCS_FILES = main.c \
			execute.c \
			create_node.c \

LIBS = -lreadline -L/usr/local/opt/readline/lib
SRCS_DIR = srcs/
LIBFT_DIR = libft
INC_DIR = inc
OBJS_DIR = objs/
INCLUDES = -I$(INC_DIR) -I/usr/local/opt/readline/include/*

OBJS = $(addprefix $(OBJS_DIR), $(SRCS_FILES:.c=.o))

LIBR = $(LIBFT_DIR)/libft.a

all: $(OBJS_DIR) libft $(NAME)

bonus: all

$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT:lib%.a=%) $(LIBS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

libft:
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS_DIR) $(BONUS_OBJS_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)$(NAME) objects cleaned!$(RESET)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(RED)$(NAME) cleaned!$(RESET)"

re: fclean all

.PHONY: all bonus libft clean fclean re
