/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr_size_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 10:30:24 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 11:37:10 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	print_unbr_nosize(va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, unsigned int);
	return (n);
}

uintmax_t	print_unbr_sizeh(va_list ap)
{
	uintmax_t n;

	n = (unsigned short)(va_arg(ap, unsigned int));
	return (n);
}

uintmax_t	print_unbr_sizehh(va_list ap)
{
	uintmax_t n;

	n = (unsigned char)(va_arg(ap, unsigned int));
	return (n);
}

uintmax_t	print_unbr_sizel(va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, unsigned long int);
	return (n);
}

uintmax_t	print_unbr_sizell(va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, unsigned long long int);
	return (n);
}
