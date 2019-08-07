/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr_util_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:38:42 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 11:32:20 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unbr_base_up(uintmax_t n, uint8_t base)
{
	if (n >= base)
		print_unbr_base_up(n / base, base);
	ft_putchar(UPPER_BASE[n % base]);
}
