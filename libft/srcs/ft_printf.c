/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:41:32 by zyeoh             #+#    #+#             */
/*   Updated: 2023/12/11 16:13:57 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_space(t_pflags *flags)
{
	if (flags->space)
	{
		write(STDOUT_FILENO, " ", 1);
		flags->out_len++;
		flags->space = 0;
		flags->plus = 0;
	}
	if (flags->precision && flags->pre_len > flags->out_len)
		flags->w_len -= flags->pre_len;
	else
		flags->w_len -= flags->out_len;
	while (flags->w_len > 0 && !flags->zero && !flags->minus)
	{
		flags->out_len += write(STDOUT_FILENO, " ", 1);
		flags->w_len--;
	}
	if (flags->plus == 1)
	{
		write(STDOUT_FILENO, "+", 1);
		flags->plus = 0;
	}
}

void	ft_print_zeropadding(t_pflags *flags, int padding)
{
	while (flags->precision && padding < flags->pre_len)
	{
		write(STDOUT_FILENO, "0", 1);
		flags->out_len++;
		flags->pre_len--;
	}
	while (flags->w_len > 0 && flags->zero)
	{
		write(STDOUT_FILENO, "0", 1);
		flags->out_len++;
		flags->w_len--;
	}
}

int	ft_print_args(const char s, t_pflags *flags, va_list args)
{
	if ((flags->hash + flags->space + flags->plus > 1 || (flags->zero
				&& flags->minus) || flags->precision > 1) && s != '%')
	{
		flags->invalid = 1;
		return (0);
	}
	if (s == 'c')
		ft_print_char(flags, va_arg(args, int));
	else if (s == 's')
		ft_print_str(flags, va_arg(args, char *));
	else if (s == 'p')
		ft_print_ptr(flags, va_arg(args, unsigned long long int));
	else if (s == 'd' || s == 'i')
		ft_print_int(flags, va_arg(args, int));
	else if (s == 'u')
		ft_print_uint(flags, va_arg(args, unsigned int));
	else if (s == 'x')
		ft_print_hex(flags, va_arg(args, unsigned int), HEX_LOWER, "0x");
	else if (s == 'X')
		ft_print_hex(flags, va_arg(args, unsigned int), HEX_UPPER, "0X");
	else if (s == '%')
		ft_print_percent(flags);
	else
		flags->invalid = 1;
	return (flags->out_len);
}

void	ft_print_getflags(const char **s, t_pflags *flags)
{
	ft_bzero(flags, sizeof(t_pflags));
	while (*++*s && (**s == '0' || **s == '-' || **s == '#' || **s == ' '
			|| **s == '+'))
	{
		if (**s == '0' && flags->zero == 0)
			flags->zero = 1;
		else if (**s == '-' && flags->minus == 0)
			flags->minus = 1;
		else if (**s == '#' && flags->hash == 0)
			flags->hash = 1;
		else if (**s == ' ' && flags->space == 0)
			flags->space = 1;
		else if (**s == '+' && flags->plus == 0)
			flags->plus = 1;
	}
	while (**s && (ft_isdigit(**s) || **s == '.'))
	{
		if (!flags->w_len && !flags->precision)
			flags->w_len = ft_atoi(*s);
		if (**s == '.')
			flags->precision++;
		else if (flags->precision && !flags->pre_len)
			flags->pre_len = ft_atoi(*s);
		++*s;
	}
}

int	ft_printf(const char *str, ...)
{
	int			index;
	int			len;
	va_list		args;
	t_pflags	flags;

	ft_bzero(&flags, sizeof(t_pflags));
	va_start(args, str);
	len = 0;
	while (str && *str && flags.invalid == 0)
	{
		index = -1;
		while (str[++index] && str[index] != '%')
			len++;
		write(STDOUT_FILENO, str, index);
		str += index;
		if (*str == '%')
		{
			ft_print_getflags(&str, &flags);
			len += ft_print_args(*str, &flags, args);
			str++;
		}
	}
	va_end(args);
	return (len);
}
