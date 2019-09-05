/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:30:57 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/04 23:15:20 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	plot_line_init(t_pt *p0, t_pt *p1, t_var *var)
{
	var->steep = fabs(p1->y - p0->y) > fabs(p1->x - p0->x);
	var->swap_d = false;
	var->swap = false;
	if (var->steep)
	{
		var->swap = true;
		ft_swap_double(&(p0->x), &(p0->y));
		ft_swap_double(&(p1->x), &(p1->y));
	}
	if (p0->x > p1->x)
	{
		if (!var->steep)
			var->swap = true;
		var->swap_d = true;
		ft_swap_double(&(p0->x), &(p1->x));
		ft_swap_double(&(p0->y), &(p1->y));
	}
	var->dx = p1->x - p0->x;
	var->dy = p1->y - p0->y;
	var->gradient = (var->dx == 0.0) ? 1.0 : (var->dy / var->dx);
}

void	plot_line_first_pt(t_fdf *fdf, t_var *var, t_pt p0)
{
	double p;

	p = 0.0;
	var->xend = ft_round(p0.x);
	var->yend = p0.y + var->gradient * (var->xend - p0.x);
	var->xgap = rfpart(p0.x + 0.5);
	var->xpxl1 = var->xend;
	var->ypxl1 = ipart(var->yend);
/*	
	if (var->steep)
	{
		p = (var->swap_d) ? 1.0 : 0.0;
		plot_pixel(fdf, var->ypxl1, var->xpxl1,
				get_color(p0.rgb, p0.rgb, p, rfpart(var->yend) * var->xgap));
		plot_pixel(fdf, var->ypxl1 + 1, var->xpxl1,
				get_color(p0.rgb, p0.rgb, p, fpart(var->yend) * var->xgap));
	}
	else
	{
		p = (var->swap) ? 1.0 : 0.0;
		plot_pixel(fdf, var->xpxl1, var->ypxl1,
				get_color(p0.rgb, p0.rgb, p, rfpart(var->yend) * var->xgap));
		plot_pixel(fdf, var->xpxl1 + 1, var->ypxl1,
				get_color(p0.rgb, p0.rgb, p, fpart(var->yend) * var->xgap));
	}
*/

	(void)fdf;
}

void	plot_line_second_pt(t_fdf *fdf, t_var *var, t_pt p1)
{
	double p;

	p = 0.0;

	var->intery = var->yend + var->gradient;
	var->xend = ft_round(p1.x);
	var->yend = p1.y + var->gradient * (var->xend - p1.x);
	var->xgap = fpart(p1.x + 0.5);
	var->xpxl2 = var->xend;
	var->ypxl2 = ipart(var->yend);
/*
	if (var->steep)
	{
		p = (var->swap_d) ? 1.0 : 1.0;
		plot_pixel(fdf, var->ypxl2, var->xpxl2,
				get_color(p1.rgb, p1.rgb, p, rfpart(var->yend) * var->xgap));
		plot_pixel(fdf, var->ypxl2 + 1, var->xpxl2,
				get_color(p1.rgb, p1.rgb, p, fpart(var->yend) * var->xgap));
	}
	else
	{
		p = (var->swap) ? 1.0 : 1.0;
		plot_pixel(fdf, var->xpxl2, var->ypxl2,
				get_color(p1.rgb, p1.rgb, p, rfpart(var->yend) * var->xgap));
		plot_pixel(fdf, var->xpxl2, var->ypxl2 + 1,
				get_color(p1.rgb, p1.rgb, p, fpart(var->yend) * var->xgap));
	}
*/
	(void)fdf;
}
