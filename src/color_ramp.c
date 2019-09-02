/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ramp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:31:18 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:01:26 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	int_to_rgb(t_rgb *ret, int color)
{
	ret->r = color / (256 * 256);
	ret->g = (color / 256) % 256;
	ret->b = color % 256;
	ret->rgb = color;
}

t_ramp	*create_ramp_node(t_rgb rgb)
{
	t_ramp *ramp;

	ramp = ft_memalloc(sizeof(t_ramp));
	ramp->r = rgb.r;
	ramp->g = rgb.g;
	ramp->b = rgb.b;
	ramp->next = NULL;
	return (ramp);
}

void	append_ramp_node(t_ramp **ramp, t_rgb rgb)
{
	t_ramp *cursor;

	cursor = *ramp;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = create_ramp_node(rgb);
}

void	color_node(t_rgb start, int steps, t_rgb end, t_rgb *rgb)
{
	int diff;

	diff = abs(start.r - end.r) / (steps);
	rgb->r += (start.r <= end.r) ? diff : -diff;
	diff = abs(start.g - end.g) / (steps);
	rgb->g += (start.g <= end.g) ? diff : -diff;
	diff = abs(start.b - end.b) / (steps);
	rgb->b += (start.b <= end.b) ? diff : -diff;
}

void	color_ramp(t_ramp **ramp, int c_start, int steps, int c_end)
{
	t_rgb	start;
	t_rgb	end;
	t_rgb	rgb;
	int		temp;

	temp = steps - 1;
	int_to_rgb(&start, c_start);
	int_to_rgb(&end, c_end);
	rgb.r = start.r;
	rgb.g = start.g;
	rgb.b = start.b;
	*ramp = (!*ramp) ? create_ramp_node(start) : *ramp;
	while (temp--)
	{
		color_node(start, steps, end, &rgb);
		append_ramp_node(ramp, rgb);
	}
	append_ramp_node(ramp, end);
}
