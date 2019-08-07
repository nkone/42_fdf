/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:03:34 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/19 13:27:04 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
** Outputs the integer n to the standard output
*/

#include "libft.h"

ssize_t	ft_putnbr(int n)
{
	return (ft_putnbr_fd(n, 1));
}
