/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_diu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:16:37 by zyeoh             #+#    #+#             */
/*   Updated: 2023/12/11 16:13:20 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_int(t_pflags *flags, int nbr)
{
	char	*number;
	int		nbr_len;

	if (flags->hash)
	{
		flags->invalid = 1;
		return ;
	}
	number = ft_custom_itoabase(flags, nbr, "0123456789");
	nbr_len = ft_strlen(number);
	flags->out_len = nbr_len;
	ft_formatflags_diux(flags, nbr);
	if (nbr < 0)
		flags->w_len--;
	ft_print_space(flags);
	if (nbr < 0)
		flags->out_len += write(STDOUT_FILENO, "-", 1);
	ft_print_zeropadding(flags, nbr_len);
	ft_putstr_fd(number, STDOUT_FILENO);
	while (flags->w_len > 0 && flags->minus)
	{
		flags->out_len += write(STDOUT_FILENO, " ", 1);
		flags->w_len--;
	}
	free(number);
}

void	ft_print_uint(t_pflags *flags, unsigned int nbr)
{
	char	*number;
	int		nbr_len;

	if (flags->hash || flags->plus)
	{
		flags->invalid = 1;
		return ;
	}
	number = ft_custom_itoabase(flags, nbr, "0123456789");
	nbr_len = ft_strlen(number);
	flags->out_len = nbr_len;
	ft_formatflags_diux(flags, nbr);
	ft_print_space(flags);
	ft_print_zeropadding(flags, nbr_len);
	ft_putstr_fd(number, STDOUT_FILENO);
	while (flags->w_len > 0 && flags->minus)
	{
		flags->out_len += write(STDOUT_FILENO, " ", 1);
		flags->w_len--;
	}
	free(number);
}

void	ft_formatflags_diux(t_pflags *flags, long long nbr)
{
	if (flags->precision)
		flags->zero = 0;
	if (nbr < 0)
	{
		flags->plus = 0;
		flags->space = 0;
	}
	if (flags->plus == 1)
		flags->out_len++;
	if (flags->hash && nbr != 0)
		flags->out_len += 2;
}
