/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr_util_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 12:54:35 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 11:36:31 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_uintmax(uintmax_t n)
{
	if (n >= 10)
	{
		print_uintmax(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n % 10 + '0');
}

uintmax_t	print_unbr_getsize(t_print *p)
{
	uintmax_t n;

	n = g_usigned_tab[flag_to_index(p->size)](p->ap);
	return (n);
}

uintmax_t	print_unbr_getsize_arg(t_print *p)
{
	va_list		ap;
	int			tmp;
	uintmax_t	n;

	tmp = p->argv;
	va_copy(ap, p->ap);
	while (tmp--)
		n = g_usigned_tab[flag_to_index(p->size)](ap);
	va_end(ap);
	return (n);
}

void		process_sp_plus_flag_unbr(t_print *p)
{
	if (p->flag & _F_PLUS)
		return ;
	else if (p->flag & _F_SPACE)
		return ;
}

int			get_unbr_space(t_print *p, uintmax_t n, int pads)
{
	int space;
	int len;

	len = get_nbr_len(n);
	space = 0;
	if (p->flag & _F_PCN)
	{
		if (pads)
			space = (p->width > (pads + len)) ? (p->width - (pads + len)) : 0;
		else if (n)
			space = (p->width >= len) ? (p->width - len) : 0;
		else if (!n)
			space = (p->width >= p->pcn) ? (p->width - p->pcn) : 0;
	}
	else
		space = (p->width > len) ? (p->width - len) : 0;
	return (space);
}
