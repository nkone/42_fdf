/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:59:49 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 18:23:25 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	const unsigned char *ps1;
	const unsigned char *ps2;
	int					result;

	ps1 = (const unsigned char *)s1;
	ps2 = (const unsigned char *)s2;
	if (ps1 == ps2)
		return (0);
	while ((result = ft_tolower(*ps1) - ft_tolower(*ps2++)) == 0)
		if (*ps1++ == '\0')
			break ;
	return (result);
}
