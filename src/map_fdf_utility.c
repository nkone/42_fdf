/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fdf_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:57:07 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 21:10:10 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static int	valid_base(char c, int base)
{
	int i;

	i = 0;
	while (i < base)
	{
		if (c == LOWER_BASE[i] || c == UPPER_BASE[i])
			return (i);
		i++;
	}
	return (-1);
}

static int	skip_prefix(const char *str, int base)
{
	if (base == 16)
	{
		if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
			return (2);
	}
	return (0);
}

static int	fdf_atoi_base(const char *str, int base)
{
	long int	n;
	int			i;

	i = 0;
	i += skip_prefix(str, base);
	n = 0;
	while (valid_base(str[i], base) != -1)
		n = n * base + valid_base(str[i++], base);
	return ((int)(n));
}

void		map_magic(const char *str, int *map, int *color, t_fdf *fdf)
{
	char **arr;

	arr = ft_strsplit(str, ',');
	if (!arr[1])
	{
		*map = ft_atoi(arr[0]);
		*color = FDF_WHITE;
		free(arr[0]);
		free(arr);
		return ;
	}
	*map = ft_atoi(arr[0]);
	*color = fdf_atoi_base(arr[1], 16);
	free(arr[0]);
	free(arr[1]);
	free(arr);
	fdf->data->map_color = true;
}
