/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xXp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:26:51 by zyeoh             #+#    #+#             */
/*   Updated: 2023/12/11 16:13:55 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_hex(t_pflags *flags, unsigned int nbr, char *baseset,
		char *hashset)
{
	char	*number;
	int		nbr_len;

	if (flags->plus || flags->space)
	{
		flags->invalid = 1;
		return ;
	}
	number = ft_custom_itoabase(flags, nbr, baseset);
	nbr_len = ft_strlen(number);
	flags->out_len = nbr_len;
	ft_formatflags_diux(flags, nbr);
	if (flags->hash && flags->pre_len > nbr_len)
		flags->out_len += flags->pre_len - nbr_len;
	ft_print_space(flags);
	if (flags->hash && nbr != 0)
		write(STDOUT_FILENO, hashset, 2);
	if (flags->hash && flags->pre_len > nbr_len)
		flags->out_len -= flags->pre_len - nbr_len;
	ft_print_zeropadding(flags, nbr_len);
	ft_putstr_fd(number, STDOUT_FILENO);
	while (flags->w_len-- > 0 && flags->minus)
		flags->out_len += write(STDOUT_FILENO, " ", 1);
	free(number);
}

void	ft_print_ptr(t_pflags *flags, unsigned long long nbr)
{
	if (flags->plus || flags->space || flags->hash || flags->zero
		|| flags->pre_len)
	{
		flags->invalid = 1;
		return ;
	}
	if (!nbr && *PTR_NULL == '(')
	{
		flags->out_len = ft_strlen(PTR_NULL);
		ft_print_space(flags);
		write(STDOUT_FILENO, PTR_NULL, ft_strlen(PTR_NULL));
	}
	else
	{
		flags->out_len = ft_numbase_ull_len(nbr, HEX_BASE) + 2;
		if (nbr == 0 && flags->precision)
			flags->out_len--;
		ft_print_space(flags);
		write(STDOUT_FILENO, "0x", 2);
		ft_print_zeropadding(flags, flags->out_len);
		if (nbr || !flags->precision)
			ft_putnbr_base(nbr, "0123456789abcdef");
	}
	while (flags->w_len-- > 0 && flags->minus)
		flags->out_len += write(STDOUT_FILENO, " ", 1);
}
