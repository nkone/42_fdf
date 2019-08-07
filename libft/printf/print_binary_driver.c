/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_binary_driver.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:44:23 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/27 14:34:09 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_base2_case1(t_print *p, uintmax_t n)
{
	print_unbr_prototype(p, n, 2);
}

void	print_base2_case2(t_print *p, uintmax_t n, int space)
{
	char c;

	c = ' ';
	if (p->flag & _F_PCN || p->flag & _F_MINUS)
		c = ' ';
	else if (p->flag & _F_ZERO)
		c = '0';
	(!(p->flag & _F_MINUS)) && put_nchar(c, space);
	print_unbr_prototype(p, n, 2);
	(p->flag & _F_MINUS) && put_nchar(c, space);
}

void	print_base2_case3(t_print *p, uintmax_t n, int pads)
{
	put_nchar('0', pads);
	print_unbr_prototype(p, n, 2);
}

void	print_base2_case4(t_print *p, uintmax_t n, int space, int pads)
{
	(!(p->flag & _F_MINUS)) && put_nchar(' ', space);
	put_nchar('0', pads);
	print_unbr_prototype(p, n, 2);
	(p->flag & _F_MINUS) && put_nchar(' ', space);
}

void	print_base2_driver(t_print *p, uintmax_t n, int space, int pads)
{
	if (!space && !pads)
		print_base2_case1(p, n);
	else if (space && !pads)
		print_base2_case2(p, n, space);
	else if (!space && pads)
		print_base2_case3(p, n, pads);
	else if (space && pads)
		print_base2_case4(p, n, space, pads);
}
