/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:41:00 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 15:44:07 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

int	count_arr_width(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	check_map_width(t_read *read)
{
	int w;
	int prev_w;

	w = 0;
	prev_w = w;
	while (read)
	{
		w = count_arr_width(read->arr);
		if (!w || (prev_w && w != prev_w))
			return (0);
		prev_w = w;
		read = read->next;
	}
	return (w);
}

int	check_map_height(t_read *read)
{
	int map_h;

	map_h = 0;
	while (read)
	{
		map_h++;
		read = read->next;
	}
	return (map_h);
}

int	get_map_size(t_read *read, t_fdf *fdf)
{
	int map_w;
	int map_h;

	map_h = check_map_height(read);
	map_w = check_map_width(read);
	if (!map_h || !map_w)
		abort_fdf();
	fdf->data->map_w = map_w;
	fdf->data->map_h = map_h;
	fdf->data->map_size = map_w * map_h;
	return (fdf->data->map_size);
}

int	*map_coord(t_read *read, t_fdf *fdf)
{
	int *map;
	int i;
	int j;

	i = 0;
	map = malloc(sizeof(int) * get_map_size(read, fdf));
	fdf->data->c_map = malloc(sizeof(int) * get_map_size(read, fdf));
	while (read)
	{
		j = 0;
		while (read->arr[j])
		{
			map_magic(read->arr[j++], &map[i], &(fdf->data->c_map[i]), fdf);
			free(read->arr[j - 1]);
			i++;
		}
		free(read->arr);
		free(read);
		read = read->next;
	}
	return (map);
}
