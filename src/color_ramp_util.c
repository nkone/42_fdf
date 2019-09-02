/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ramp_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:34:26 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 15:46:57 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

int		count_ramp(t_ramp *ramp)
{
	int c;

	c = 0;
	if (!ramp)
		return (0);
	while (ramp)
	{
		c++;
		ramp = ramp->next;
	}
	return (c);
}

void	**fdf_index_color_ramp(t_ramp *ramp)
{
	void	**map;
	int		size;
	int		i;

	i = 0;
	size = count_ramp(ramp);
	(!(map = ft_memalloc(sizeof(t_ramp) * size))) && abort_fdf();
	while (ramp)
	{
		map[i++] = ramp;
		ramp = ramp->next;
	}
	map[i] = NULL;
	return (map);
}

void	free_color_ramp(t_ramp *ramp)
{
	t_ramp *temp;

	temp = ramp;
	while (ramp)
	{
		temp = ramp->next;
		free(ramp);
		ramp = temp;
	}
}

int		get_color_index(int z, int size)
{
	int idx_steps;
	int mid_idx;

	idx_steps = 1000 / size;
	mid_idx = size / 2;
	if (!idx_steps)
		idx_steps = 1;
	mid_idx += (z / idx_steps);
	if (mid_idx < 0)
		mid_idx = 0;
	if (mid_idx >= size)
		mid_idx = size - 1;
	return (mid_idx);
}
