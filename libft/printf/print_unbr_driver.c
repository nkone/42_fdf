/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr_driver.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 14:31:12 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/26 17:51:46 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unbr_case1(t_print *p, uintmax_t n)
{
	process_sp_plus_flag_unbr(p);
	(!n && !p->pcn && p->flag & _F_PCN) ? 0 : print_uintmax(n);
}

void	print_unbr_case2(t_print *p, uintmax_t n, int space)
{
	char c;

	c = (p->flag & _F_ZERO) ? '0' : ' ';
	(p->flag & _F_PCN) && (c = ' ');
	if (p->flag & _F_PCN && !p->pcn && !n)
	{
		(!(p->flag & _F_MINUS)) && put_nchar(c, space);
		process_sp_plus_flag_unbr(p);
		(p->flag & _F_MINUS) && put_nchar(c, space);
		return ;
	}
	if (p->flag & _F_ZERO && !(p->flag & _F_PCN))
		process_sp_plus_flag_unbr(p);
	(!(p->flag & _F_MINUS)) && put_nchar(c, space);
	if (!(p->flag & _F_ZERO))
		process_sp_plus_flag_unbr(p);
	else if (p->flag & _F_ZERO && p->flag & _F_PCN)
		process_sp_plus_flag_unbr(p);
	(!n && !p->pcn && p->flag & _F_PCN) ? 0 : print_uintmax(n);
	(p->flag & _F_MINUS) && put_nchar(' ', space);
}

void	print_unbr_case3(t_print *p, uintmax_t n, int pads)
{
	process_sp_plus_flag_unbr(p);
	put_nchar('0', pads);
	(!n && !p->pcn && p->flag & _F_PCN) ? 0 : print_uintmax(n);
}

void	print_unbr_case4(t_print *p, uintmax_t n, int space, int pads)
{
	(!(p->flag & _F_MINUS)) && put_nchar(' ', space);
	process_sp_plus_flag_unbr(p);
	put_nchar('0', pads);
	(!n && !p->pcn && p->flag & _F_PCN) ? 0 : print_uintmax(n);
	(p->flag & _F_MINUS) && put_nchar(' ', space);
}

void	print_unbr_driver(t_print *p, uintmax_t n, int space, int pads)
{
	if (!space && !pads)
		print_unbr_case1(p, n);
	else if (space && !pads)
		print_unbr_case2(p, n, space);
	else if (!space && pads)
		print_unbr_case3(p, n, pads);
	else if (space && pads)
		print_unbr_case4(p, n, space, pads);
}
