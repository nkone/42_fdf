/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float_driver.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:45:08 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 13:26:40 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_float(t_float *f)
{
	f->whole = 0;
	f->frac = 0;
	f->space = 0;
	f->pads = 0;
	f->sign = 0;
	f->rem = 0.0;
	f->diff = 0.0;
}

void	print_float_(t_print *p, t_float f)
{
	int len;

	len = get_nbr_len(f.whole);
	!(p->flag & _F_PCN) && (len += (D_FPREC + 1));
	(p->flag & _F_PCN && p->pcn) && (len += p->pcn + 1);
	(p->flag & _F_PLUS || p->flag & _F_SPACE || f.sign == -1) && len++;
	(!f.pcn && p->flag & _F_HASH) && len++;
	f.space = (p->width > len) ? (p->width - len) : 0;
	p->done += f.space;
	if (p->done >= INT_MAX)
		return ;
	print_float_driver(p, f);
	p->done += len;
}

void	print_float_rounding(long double n, t_float *f)
{
	if (f->diff > 0.5)
	{
		f->frac++;
		if (f->frac >= pow10(f->pcn))
		{
			f->frac = 0;
			f->whole++;
		}
	}
	else if (f->diff < 0.5)
		f->diff = f->diff;
	else if (f->frac == 0 || f->frac & 1)
		f->frac++;
	if (!f->pcn)
	{
		f->diff = n - (long double)f->whole;
		(!(f->diff < 0.5 || f->diff > 0.5) && f->whole & 1) && (f->whole++);
	}
}

void	print_float_driver(t_print *p, t_float f)
{
	(!(p->flag & _F_MINUS) && !(p->flag & _F_ZERO)) && put_nchar(' ', f.space);
	(f.sign == -1) && ft_putchar('-');
	(f.sign == 1 && p->flag & _F_PLUS) && ft_putchar('+');
	(f.sign == 1 && p->flag & _F_SPACE && !(p->flag & _F_PLUS))
		&& ft_putchar(' ');
	(!(p->flag & _F_MINUS) && p->flag & _F_ZERO) && put_nchar('0', f.space);
	print_uintmax(f.whole);
	(f.pcn) && ft_putchar('.');
	(!f.pcn && p->flag & _F_HASH) && ft_putchar('.');
	(f.pcn) && put_nchar('0', (f.pcn - get_nbr_len(f.frac)));
	if (f.pcn)
		print_uintmax(f.frac);
	(p->flag & _F_MINUS) && put_nchar(' ', f.space);
}
