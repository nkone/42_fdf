/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_size_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:42:50 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/23 20:22:49 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	print_nbr_nosize(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, int);
	return (n);
}

intmax_t	print_nbr_sizeh(va_list ap)
{
	intmax_t n;

	n = (short)(va_arg(ap, int));
	return (n);
}

intmax_t	print_nbr_sizehh(va_list ap)
{
	intmax_t n;

	n = (char)(va_arg(ap, int));
	return (n);
}

intmax_t	print_nbr_sizel(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, long int);
	return (n);
}

intmax_t	print_nbr_sizell(va_list ap)
{
	intmax_t n;

	n = va_arg(ap, long long int);
	return (n);
}
