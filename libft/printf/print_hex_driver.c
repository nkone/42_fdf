/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_driver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:04:42 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/28 21:17:37 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_base16_case1(t_print *p, uintmax_t n)
{
	if (!n)
		print_unbr_prototype(p, n, 16);
	else
	{
		process_hash_flag(p, 16);
		print_unbr_prototype(p, n, 16);
	}
}

void	print_base16_case2(t_print *p, uintmax_t n, int space)
{
	char c;

	c = (p->flag & _F_ZERO && !(p->flag & _F_PCN || p->flag & _F_MINUS)) ?
		'0' : ' ';
	if (!n)
	{
		(!(p->flag & _F_MINUS)) && put_nchar(c, space);
		print_unbr_prototype(p, n, 16);
	}
	else
	{
		if (c == ' ')
			(!(p->flag & _F_MINUS)) && put_nchar(c, space);
		process_hash_flag(p, 16);
		if (c == '0')
			(!(p->flag & _F_MINUS)) && put_nchar(c, space);
		print_unbr_prototype(p, n, 16);
	}
	(p->flag & _F_MINUS) && put_nchar(c, space);
}

void	print_base16_case3(t_print *p, uintmax_t n, int pads)
{
	if (n)
		process_hash_flag(p, 16);
	put_nchar('0', pads);
	print_unbr_prototype(p, n, 16);
}

void	print_base16_case4(t_print *p, uintmax_t n, int space, int pads)
{
	(!(p->flag & _F_MINUS)) && put_nchar(' ', space);
	if (n)
		process_hash_flag(p, 16);
	put_nchar('0', pads);
	print_unbr_prototype(p, n, 16);
	(p->flag & _F_MINUS) && put_nchar(' ', space);
}

void	print_base16_driver(t_print *p, uintmax_t n, int space, int pads)
{
	if (!space && !pads)
		print_base16_case1(p, n);
	else if (space && !pads)
		print_base16_case2(p, n, space);
	else if (!space && pads)
		print_base16_case3(p, n, pads);
	else if (space && pads)
		print_base16_case4(p, n, space, pads);
}
