/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_main_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:07:31 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 11:38:27 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_nbr(t_print *p)
{
	intmax_t	n;
	int			len;
	int			space;
	int			pads;

	n = (p->argv) ? print_nbr_getsize_arg(p) : print_nbr_getsize(p);
	len = (n < 0) ? get_nbr_len(-n) : get_nbr_len(n);
	(!n && !p->pcn && p->flag & _F_PCN) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_nbr_space(p, n, pads);
	p->done += (space + pads + len);
	if (p->done >= INT_MAX)
		return ;
	if (n < 0)
		p->done++;
	else if (n >= 0 && (p->flag & _F_PLUS || p->flag & _F_SPACE))
		p->done++;
	print_nbr_driver(p, n, space, pads);
}

void	print_unbr(t_print *p)
{
	uintmax_t	n;
	int			len;
	int			space;
	int			pads;

	n = (p->argv) ? print_unbr_getsize_arg(p) : print_unbr_getsize(p);
	len = get_nbr_len(n);
	(!n && !p->pcn && p->flag & _F_PCN) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_unbr_space(p, n, pads);
	p->done += (space + pads);
	if (p->done >= INT_MAX)
		return ;
	p->done += len;
	print_unbr_driver(p, n, space, pads);
}

void	print_unbr_base2(t_print *p)
{
	uintmax_t	n;
	int			len;
	int			space;
	int			pads;

	n = (p->argv) ? print_unbr_getsize_arg(p) : print_unbr_getsize(p);
	len = get_unbr_len_base(n, 2);
	(!n && !p->pcn && p->flag & _F_PCN) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_unbr_sp_base(p, n, pads, 2);
	p->done += (space + pads);
	if (p->done >= INT_MAX)
		return ;
	p->done += len;
	print_base2_driver(p, n, space, pads);
}

void	print_unbr_base8(t_print *p)
{
	uintmax_t	n;
	int			len;
	int			space;
	int			pads;

	n = (p->argv) ? print_unbr_getsize_arg(p) : print_unbr_getsize(p);
	len = get_unbr_len_base(n, 8);
	(!n && !p->pcn && p->flag & _F_PCN) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_unbr_sp_base(p, n, pads, 8);
	if (!n && p->flag & _F_PCN && p->flag & _F_HASH && !p->pcn && space)
		space--;
	(n && p->flag & _F_HASH && space && !pads) && space--;
	p->done += (space + pads);
	if (p->done >= INT_MAX)
		return ;
	p->done += len;
	print_base8_driver(p, n, space, pads);
}

void	print_unbr_base16(t_print *p)
{
	uintmax_t	n;
	int			len;
	int			space;
	int			pads;

	n = (p->argv) ? print_unbr_getsize_arg(p) : print_unbr_getsize(p);
	len = get_unbr_len_base(n, 16);
	(!n && !p->pcn && p->flag & _F_PCN) && (len = 0);
	pads = (p->pcn > len) ? (p->pcn - len) : 0;
	space = get_unbr_sp_base(p, n, pads, 16);
	(p->flag & _F_HASH && n) && (space -= 2);
	(space < 0) && (space = 0);
	p->done += (space + pads);
	if (p->done >= INT_MAX)
		return ;
	p->done += len;
	print_base16_driver(p, n, space, pads);
}
