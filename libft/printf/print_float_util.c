/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_float_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:51:19 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 14:39:17 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	get_float(t_print *p, va_list ap)
{
	long double n;

	n = (p->size & _S_LF) ? va_arg(ap, long double) : va_arg(ap, double);
	return (n);
}

long double	get_float_arg(t_print *p)
{
	va_list		ap;
	int			tmp;
	long double	n;

	tmp = p->argv;
	va_copy(ap, p->ap);
	while (tmp--)
		n = (p->size & _S_LF) ? va_arg(ap, long double) : va_arg(ap, double);
	va_end(ap);
	return (n);
}

uintmax_t	pow10(int8_t n)
{
	uintmax_t i;

	i = 1;
	while (n--)
		i *= 10;
	return (i);
}
