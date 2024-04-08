/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:20:25 by zyeoh             #+#    #+#             */
/*   Updated: 2023/12/11 16:13:00 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char(t_pflags *flags, int c)
{
	if (flags->hash || flags->plus || flags->zero || flags->precision
		|| flags->space)
	{
		flags->invalid = 1;
		return ;
	}
	flags->out_len++;
	ft_print_space(flags);
	ft_putchar_fd(c, STDOUT_FILENO);
	while (flags->w_len > 0 && flags->minus)
	{
		flags->out_len += write(STDOUT_FILENO, " ", 1);
		flags->w_len--;
	}
}

void	ft_print_str(t_pflags *flags, char *str)
{
	if (flags->hash || flags->plus || flags->space)
	{
		flags->invalid = 1;
		return ;
	}
	if (!str)
		str = "(null)";
	flags->out_len = ft_strlen(str);
	if (flags->precision && flags->out_len > flags->pre_len)
		flags->out_len = flags->pre_len;
	flags->pre_len = flags->out_len;
	ft_print_space(flags);
	write(STDOUT_FILENO, str, flags->pre_len);
	while (flags->w_len > 0 && flags->minus)
	{
		flags->out_len += write(STDOUT_FILENO, " ", 1);
		flags->w_len--;
	}
}

void	ft_print_percent(t_pflags *flags)
{
	flags->pre_len = 0;
	flags->precision = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->out_len++;
	ft_print_space(flags);
	write(STDOUT_FILENO, "%", 1);
	ft_print_space(flags);
}
