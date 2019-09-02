/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_magic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:49:24 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:06:40 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	extract_min_max(int *map, int *min, int *max, int size)
{
	int i;

	i = 0;
	*max = map[i];
	*min = map[i];
	while (i++ < size - 1)
	{
		if (map[i] > *max)
			*max = map[i];
		if (map[i] < *min)
			*min = map[i];
	}
}

void	get_coefficient(int *map, t_fdf *fdf)
{
	int		max;
	int		min;

	extract_min_max(map, &min, &max, fdf->data->map_size);
	fdf->coef_m = (0.0 - 1.0) / (min - max);
	fdf->coef_b = 1.0 - (fdf->coef_m * max);
	fdf->min = min;
	fdf->max = max;
}

void	fdf_zoom_magic(t_fdf *fdf)
{
	fdf->cam.zoom = -12.2123 * log(0.0000747893 * (fdf->data->map_size));
	if (fdf->cam.zoom <= 0.0)
		fdf->cam.zoom = 3.0;
	fdf->cam.depth_f = fdf->cam.zoom;
	get_coefficient(fdf->data->map, fdf);
}
