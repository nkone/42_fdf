/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr_size_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 10:31:43 by phtruong          #+#    #+#             */
/*   Updated: 2019/05/26 10:31:55 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	print_unbr_sizelf(va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, unsigned int);
	return (n);
}

uintmax_t	print_unbr_sizej(va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, uintmax_t);
	return (n);
}

uintmax_t	print_unbr_sizez(va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, size_t);
	return (n);
}

uintmax_t	print_unbr_sizet(va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, ssize_t);
	return (n);
}
