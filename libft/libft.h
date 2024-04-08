/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:17:43 by zyeoh             #+#    #+#             */
/*   Updated: 2023/12/13 18:45:12 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);

void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);

void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);

char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dest, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					ft_tolower(int c);
int					ft_toupper(int c);

void				*ft_calloc(size_t count, size_t size);
char				**ft_split(const char *str, char c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char				*get_next_line(int fd);
char				*read_file(int fd, char *full_str);
char				*get_line(char *full_str);
char				*next_line(char *full_str);

# define HEX_BASE 16
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

# if defined(__linux__)
#  define PTR_NULL "(nil)"
# elif defined(__APPLE__)
#  define PTR_NULL "0x0"
# endif

typedef struct s_pflags_list
{
	int				invalid;
	int				out_len;
	int				w_len;
	int				pre_len;

	int				zero;
	int				minus;
	int				hash;
	int				space;
	int				plus;
	int				precision;
}					t_pflags;

/***********************************************************************/
// ft_printf.c
/**
 * @brief Replicates Printf, takes a string followed
 * by given arguments and outputs the specifier and
 * it's flags in the string. Invalid format terminates
 * @return The length of the output
 * @param str The string to output with its specifier and flags
 * @param ... The given arguments to output
 */
int					ft_printf(const char *str, ...);

/**
 * @brief Outputs the flag 'space', starting space padding,
 * the positive sign and the space padding on the right of the specifier.
 * @param flags The struct that holds the flags for printf
 */
void				ft_print_space(t_pflags *flags);

/**
 * @brief Outputs zero padding for the precision or the zero flag
 * @param flags The struct that holds the flags for printf
 * @param padding The number of zeros to output for padding
 */
void				ft_print_zeropadding(t_pflags *flags, int padding);

/**
 * @brief Calls the appropriate function to output based on the given character.
 * invalid format terminates
 * @param s The given specifier
 * @param flags The struct that holds the flags for ft_printf
 * @param args Holds the list of arguments given in ft_printf
 */
int					ft_print_args(const char s, t_pflags *flags, va_list args);

/**
 * @brief Parse through the flags after % and records it to flags
 * @param s The given pointer from ft_printf to parse through globally
 * @param flags The struct that holds the flags for ft_printf
 */
void				ft_print_getflags(const char **s, t_pflags *flags);

/***********************************************************************/
// ft_print_cs.c
/**
 * @brief Outputs a character in ft_printf, invalid format terminates
 * @param flags The struct that holds the flags for ft_printf
 * @param c The given ascii value to output
 */
void				ft_print_char(t_pflags *flags, int c);

/**
 * @brief Outputs a string in ft_printf, invalid format terminates
 * @param flags The struct that holds the flags for ft_printf
 * @param str The given string value to output,
	truncates if precision length is smaller
 */
void				ft_print_str(t_pflags *flags, char *str);

/**
 * @brief Outputs a percentage in ft_printf
 * @param flags The struct that holds the flags for ft_printf
 */
void				ft_print_percent(t_pflags *flags);

/***********************************************************************/
// ft_print_diu.c
/**
 * @brief Outputs an integer/denary in ft_printf, invalid format terminates
 * @param flags The struct that holds the flags for ft_printf
 * @param nbr The given value to output
 */
void				ft_print_int(t_pflags *flags, int nbr);

/**
 * @brief Outputs an unsigned integer in ft_printf, invalid format terminates
 * @param flags The struct that holds the flags for ft_printf
 * @param nbr The given value to output
 */
void				ft_print_uint(t_pflags *flags, unsigned int nbr);

/**
 * @brief Formats the given flags for denary, integer,
	unsigned int and hexadecimal.
 * @param flags The struct that holds the flags for ft_printf
 * @param nbr Checks if nbr sign to format the flags appropriately
 */
void				ft_formatflags_diux(t_pflags *flags, long long nbr);

/***********************************************************************/
// ft_print_xXp.c
/**
 * @brief Outputs the hexadecimal for both upper and lower case in ft_printf, ,
	invalid format terminates
 * @param flags The struct that holds the flags for printf
 * @param nbr The given value to convert to hexadecimal and output
 * @param baseset The string representing the baseset used to convert to
 * @param hashset The hexadecimal prefix
 */
void				ft_print_hex(t_pflags *flags, unsigned int nbr,
						char *baseset, char *hashset);

/**
 * @brief Outputs the hexadecimal to represent address, ,
	invalid format terminates
 * @param flags The struct that holds the flags for ft_printf
 * @param nbr The given value to convert to hexadecimal and output
 */
void				ft_print_ptr(t_pflags *flags, unsigned long long nbr);

/***********************************************************************/
// ft_printf_util.c
/**
 * @brief Calculates the number of digits for a number based on a base.
 * @return An int representing the number of digits
 * @param nbr The number to find the length from
 * @param base The base of the value.
 */
int					ft_numbase_ll_len(long long nbr, long base);

/**
 * @brief Calculates the number of digits for a unsigned number based on a base.
 * @return An int representing the number of digits
 * @param nbr The number to find the length from
 * @param base The base of the value.
 */
int					ft_numbase_ull_len(unsigned long long nbr, long base);

/**
 * @brief Outputs the value recursively in the format of the given baseset
 * @param nbr The value to convert and output
 * @param baseset The string representing the baseset used to convert to
 */
void				ft_putnbr_base(unsigned long long nbr, char const *baseset);

/**
 * @brief Returns the value converted to the given baseset
 * @return The string to represent the converted value
 * @param flags The struct that holds the flags for ft_printf
 * @param nbr The value to convert to the given baseset
 * @param baseset The string representing the baseset used to convert to
 */
char				*ft_custom_itoabase(t_pflags *flags, long long nbr,
						char *baseset);

/***********************************************************************/

#endif