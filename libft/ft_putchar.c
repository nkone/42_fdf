/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:44:54 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 11:42:10 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
** Outputs the character c to the standard output.
*/

#include "libft.h"

ssize_t	ft_putchar(char c)
{
	return (ft_putchar_fd(c, 1));
}
