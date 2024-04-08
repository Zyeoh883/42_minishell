NAME = libft.a
CC = gcc
RM = rm -rf
MKDIR = mkdir -p
CFLAGS = -Wall -Wextra -Werror

RED = \033[0;91m
GREEN = \033[92m
RESET = \033[0m

SRCS_FILES = ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c\
	get_next_line.c\
	ft_print_cs.c\
	ft_print_diu.c\
	ft_print_util.c\
	ft_print_xXp.c\
	ft_printf.c\

BONUS_FILES = ft_lstadd_back.c\
	ft_lstadd_front.c\
	ft_lstclear.c\
	ft_lstdelone.c\
	ft_lstiter.c\
	ft_lstlast.c\
	ft_lstmap.c\
	ft_lstnew.c\
	ft_lstsize.c\

SRCS_DIR = srcs/
OBJS_DIR = objs/
INC_DIR = .

OBJS = $(addprefix $(OBJS_DIR), $(SRCS_FILES:.c=.o))
BONUS_OBJS = $(addprefix $(OBJS_DIR), $(BONUS_FILES:.c=.o))

LIBR = ranlib
LIBC = ar rcs

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@$(LIBC) $(NAME) $(OBJS)
	@echo "$(GREEN)libft compiled!$(RESET)"

bonus: $(OBJS) $(BONUS_OBJS)
	@$(LIBC) $(NAME) $(BONUS_OBJS)
	@echo "$(GREEN)libft bonus compiled and added!$(RESET)"

clean:
	@$(RM) ${OBJS_DIR}
	@echo "$(RED)libft objects cleaned!$(RESET)"

fclean:
	@$(RM) ${OBJS_DIR}
	@$(RM) ${NAME}
	@echo "$(RED)libft cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus