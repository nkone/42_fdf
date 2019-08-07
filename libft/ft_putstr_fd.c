/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:05:37 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 11:43:28 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
** Outputs the char c to the file descriptor fd.
*/

#include "libft.h"

ssize_t	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return (-1);
	return (write(fd, s, ft_strlen(s)));
}
