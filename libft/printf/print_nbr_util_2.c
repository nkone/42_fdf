/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_util_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:47:34 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/26 13:35:51 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			flag_to_index(int flag)
{
	int i;

	i = 0;
	while (flag)
	{
		flag >>= 1;
		i++;
		if (!flag)
			break ;
	}
	return (i);
}

int			get_nbr_len(uintmax_t n)
{
	int len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

intmax_t	print_nbr_getsize_arg(t_print *p)
{
	intmax_t	n;
	va_list		ap;
	int			tmp;

	tmp = p->argv;
	va_copy(ap, p->ap);
	while (tmp-- > 0)
		n = g_signed_tab[flag_to_index(p->size)](ap);
	va_end(ap);
	return (n);
}
