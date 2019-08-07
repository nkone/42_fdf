/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_main_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:10:57 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 13:25:49 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_float(t_print *p)
{
	long double	n;
	t_float		f;

	n = (p->argv) ? get_float_arg(p) : get_float(p, p->ap);
	f.pcn = (p->flag & _F_PCN) ? p->pcn : D_FPREC;
	init_float(&f);
	f.sign = (n < 0) ? -1 : 1;
	n = (n < 0) ? -n : n;
	f.whole = (uint64_t)n;
	f.rem = (n - f.whole) * pow10(f.pcn);
	f.frac = (uint64_t)f.rem;
	f.diff = f.rem - f.frac;
	print_float_rounding(n, &f);
	print_float_(p, f);
}

void	print_void_pointer(t_print *p)
{
	uintmax_t	n;
	int			len;
	int			space;
	int			pads;

	n = (uintmax_t)va_arg(p->ap, void *);
	len = get_unbr_len_base(n, 16);
	(!n && p->flag & _F_PCN && !p->pcn) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_unbr_sp_base(p, n, pads, 16) - 2;
	(space < 0) && (space = 0);
	p->done += (space + pads);
	if (p->done >= INT_MAX)
		return ;
	p->done += len;
	print_vp_driver(p, n, space, pads);
}
