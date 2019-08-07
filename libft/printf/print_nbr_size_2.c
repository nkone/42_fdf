/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_size_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:41:06 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/23 20:23:06 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	print_nbr_sizelf(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, int);
	return (n);
}

intmax_t	print_nbr_sizej(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, intmax_t);
	return (n);
}

intmax_t	print_nbr_sizez(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, size_t);
	return (n);
}

intmax_t	print_nbr_sizet(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, ssize_t);
	return (n);
}

intmax_t	print_nbr_getsize(t_print *p)
{
	intmax_t n;

	n = g_signed_tab[flag_to_index(p->size)](p->ap);
	return (n);
}
