/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr_util_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:59:35 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 13:03:46 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unbr_base_lo(uintmax_t n, uint8_t base)
{
	if (n >= base)
		print_unbr_base_lo(n / base, base);
	ft_putchar(LOWER_BASE[n % base]);
}

void	print_unbr_prototype(t_print *p, uintmax_t n, uint8_t base)
{
	if (p->type == 7 || p->type == 8 || p->type == 9)
		(!n && p->flag & _F_PCN && !p->pcn) ? 0 : print_unbr_base_lo(n, base);
	else if (p->type == 10)
		(!n && p->flag & _F_PCN && !p->pcn) ? 0 : print_unbr_base_up(n, base);
}

int		get_unbr_sp_base(t_print *p, uintmax_t n, int pads, uint8_t base)
{
	int space;
	int len;

	len = get_unbr_len_base(n, base);
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

int		get_unbr_len_base(uintmax_t n, uint8_t base)
{
	int len;

	if (base < 2 || base > 16)
		return (0);
	if (!n)
		return (1);
	len = 1;
	while (n /= base)
		len++;
	return (len);
}

void	process_hash_flag(t_print *p, uint8_t base)
{
	if (!(p->flag & _F_HASH))
		return ;
	else if (p->flag & _F_HASH && (base == 8))
		p->done += ft_putchar('0');
	else if (p->flag & _F_HASH && (base == 16) && p->type == 9)
		p->done += ft_putstr("0x");
	else if (p->flag & _F_HASH && (base == 16) && p->type == 10)
		p->done += ft_putstr("0X");
}
