/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_util_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:43:10 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/26 18:20:59 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_nbr_plus_flag(intmax_t n)
{
	if (n < 0)
		ft_putchar('-');
	else
		ft_putchar('+');
	return (1);
}

int		print_nbr_sp_flag(intmax_t n)
{
	if (n < 0)
		ft_putchar('-');
	else
		ft_putchar(' ');
	return (1);
}

void	process_sp_plus_flag(t_print *p, intmax_t n)
{
	if (p->flag & _F_PLUS)
		print_nbr_plus_flag(n);
	else if (p->flag & _F_SPACE)
		print_nbr_sp_flag(n);
	else if (p->flag & _F_ZERO && n < 0)
		ft_putchar('-');
	else if (p->flag & _F_PCN && n < 0)
		ft_putchar('-');
	else if (p->flag && n < 0)
		ft_putchar('-');
}

void	print_nbr_prototype(t_print *p, intmax_t n)
{
	if (n < 0 && !(p->flag))
		ft_putchar('-');
	n = (n < 0) ? -n : n;
	(!n && !p->pcn && p->flag & _F_PCN) ? 0 : print_uintmax(n);
}

int		get_nbr_space(t_print *p, intmax_t n, int pads)
{
	int space;
	int len;

	len = (n < 0) ? get_nbr_len(-n) : get_nbr_len(n);
	space = 0;
	if (p->width > 0)
		(n < 0 || p->flag & _F_PLUS || p->flag & _F_SPACE) && p->width--;
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
