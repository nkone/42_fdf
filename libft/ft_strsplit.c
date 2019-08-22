/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 09:57:51 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/21 19:46:26 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
** Allocates with malloc() and returns an array of "fresh" strings
** (all ending with '\0', including the array itself) obtained by splitting
** s using the character c as a delimiter. If the allocation fails,
** the function returns NULL. Example:
** ft_strplit("*hello*fellow***students*", '*') returns
** ["hello", "fellow", "students"]
** RETURN VALUES
** Array of "fresh" strings result from the split.
*/

#include "libft.h"

static int	wordcount(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			len++;
		while (*s && *s != c)
			s++;
	}
	return (len);
}

char		**ft_strsplit(const char *s, char c)
{
	char		**arr;
	const char	*ps;
	int			wc;
	int			i;
	int			j;

	wc = wordcount(s, c);
	arr = malloc(sizeof(char *) * (wc + 1));
	arr[wc] = NULL;
	i = -1;
	while (++i < wc)
	{
		j = -1;
		while (*s == c)
			s++;
		ps = s;
		while (*s && *s != c)
			s++;
		arr[i] = malloc(sizeof(char) * ((s - ps) + 1));
		while (++j < (s - ps))
			arr[i][j] = ps[j];
		arr[i][j] = '\0';
	}
	return (arr);
}
