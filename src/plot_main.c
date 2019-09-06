/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:35:19 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/05 20:55:59 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"
// main brightness issue comes from the brightness calculation

static void	plot_main_steep(t_fdf *fdf, t_var var, t_rgb p0, t_rgb p1)
{
	int		start;
	double	percent;

	start = var.xpxl1;
	while (var.xpxl1++ < var.xpxl2)
	{
		percent = (var.swap_d) ? curr_percent(var.xpxl2, var.xpxl1, start) : // color swap...
			curr_percent(start, var.xpxl1, var.xpxl2);
		if (fdf->cam.anti_alias == false)
		{	
			plot_pixel(fdf, ipart(var.intery), var.xpxl1,
					get_color(p0, p1, percent, 1.0));// setting rfpart(var.intery) to 1.0 solves brightness issue
			plot_pixel(fdf, ipart(var.intery) + 1, var.xpxl1,
					get_color(p0, p1, percent, 1.0));
		}
		else
		{
			plot_pixel(fdf, ipart(var.intery), var.xpxl1,
					get_color(p0, p1, percent, rfpart(var.intery))); 
			plot_pixel(fdf, ipart(var.intery) + 1, var.xpxl1,
					get_color(p0, p1, percent, fpart(var.intery)));
		}
		var.intery += var.gradient;
	}
}

static void	plot_main_not_steep(t_fdf *fdf, t_var var, t_rgb p0, t_rgb p1)
{
	double start;
	double percent;

	start = var.xpxl1;
	while (var.xpxl1++ < var.xpxl2)
	{
		percent = (var.swap) ? curr_percent(var.xpxl2, var.xpxl1, start) : // color swap...
			curr_percent(start, var.xpxl1, var.xpxl2);
		if (fdf->cam.anti_alias == false)
		{
			plot_pixel(fdf, var.xpxl1, ipart(var.intery),
					get_color(p0, p1, percent, 1.0));
			plot_pixel(fdf, var.xpxl1, ipart(var.intery) + 1,
					get_color(p0, p1, percent, 1.0));
		}
		else
		{
			plot_pixel(fdf, var.xpxl1, ipart(var.intery),
					get_color(p0, p1, percent, rfpart(var.intery)));
			plot_pixel(fdf, var.xpxl1, ipart(var.intery) + 1,
					get_color(p0, p1, percent, fpart(var.intery)));
		}
		var.intery += var.gradient;
	}
}

static void	plot_line_main(t_fdf *fdf, t_var var, t_rgb p0, t_rgb p1)
{
	if (var.steep)
		plot_main_steep(fdf, var, p0, p1);
	else
		plot_main_not_steep(fdf, var, p0, p1);
}

void		plot_line(t_fdf *fdf, t_pt p0, t_pt p1)
{
	t_var var;

	ft_bzero(&var, sizeof(t_var));
//	ft_printf("p0: rgb(%x) p1: rgb(%x))\n", p0.rgb.rgb, p1.rgb.rgb); // for debugging color
	plot_line_init(&p0, &p1, &var);
	plot_line_first_pt(fdf, &var, p0);
	plot_line_second_pt(fdf, &var, p1);
	plot_line_main(fdf, var, p0.rgb, p1.rgb);
	
	// this whole chunk is from rosetta code for algo seems to produce same brightness effect

	/*
	var.swap = false;
	var.dx = (double)p1.x - (double)p0.x;
	var.dy = (double)p1.y - (double)p0.y;
	if (fabs(var.dx) > fabs(var.dy))
	{
		if (p1.x < p0.x)
		{
			var.swap = true;
			ft_swap(&p0.x, &p1.x);
			ft_swap(&p0.y, &p1.y);
		}
		var.gradient = var.dy / var.dx;
		var.xend = ft_round(p0.x);
		var.yend = p0.y + var.gradient * (var.xend - p0.x);
		var.xgap = rfpart(p0.x + 0.5);
		var.xpxl1 = var.xend;
		// point 1
		plot_pixel(fdf, var.xpxl2, var.ypxl2, get_color(p0.rgb, p1.rgb, 1.0, rfpart(var.yend) * var.xgap));
		plot_pixel(fdf, var.xpxl2, var.ypxl2 + 1, get_color(p0.rgb, p1.rgb, 1.0, fpart(var.yend) * var.xgap));
		var.intery = var.yend + var.gradient;
		
		var.xend = ft_round(p1.x);
		var.yend = p1.y + var.gradient * (var.xend - p1.x);
		var.xgap = fpart(p1.x + 0.5);
		var.xpxl2 = var.xend;
		var.ypxl2 = ipart(var.yend);
		// point 2
		plot_pixel(fdf, var.xpxl2, var.ypxl2, get_color(p0.rgb, p1.rgb, 1.0, rfpart(var.yend) * var.xgap));
		plot_pixel(fdf, var.xpxl2, var.ypxl2 + 1, get_color(p0.rgb, p1.rgb, 1.0, fpart(var.yend) * var.xgap));
		int x;
		for (x = var.xpxl1+1; x < var.xpxl2; x++)
		{ 
			double percent = (var.swap) ? curr_percent(var.xpxl2, x, var.xpxl1) : // color swap...
				curr_percent(var.xpxl1, x, var.xpxl2);
			plot_pixel(fdf, x, ipart(var.intery), get_color(p0.rgb, p1.rgb, percent, rfpart(var.intery)));
			plot_pixel(fdf, x, ipart(var.intery) + 1, get_color(p0.rgb, p1.rgb, percent, fpart(var.intery)));
			var.intery += var.gradient;
		}
	}
	else
	{
		if (p1.y < p0.y)
		{
			var.swap = true;
			ft_swap(&p0.x, &p1.x); 
			ft_swap(&p0.y, &p1.y);
		}
		var.gradient = var.dx / var.dy;
		var.yend = ft_round(p0.y);
		var.xend = p0.x + var.gradient * (var.yend - p0.y);
		var.ygap = rfpart(p0.y + 0.5);
		var.ypxl1 = var.yend;
		var.xpxl1 = ipart(var.xend);
		plot_pixel(fdf, var.xpxl1, var.ypxl1, get_color(p0.rgb, p1.rgb, 1.0, rfpart(var.xend) * var.ygap));
		plot_pixel(fdf, var.xpxl1 + 1, var.ypxl1, get_color(p0.rgb, p1.rgb, 1.0, fpart(var.xend) * var.ygap));
		var.interx = var.xend + var.gradient;
		
		var.yend = ft_round(p1.y);
		var.xend = p1.x + var.gradient * (var.yend - p1.y);
		var.ygap = fpart(p1.y + 0.5);
		var.ypxl2 = var.yend;
		var.xpxl2 = ipart(var.xend);	
		plot_pixel(fdf, var.xpxl2, var.ypxl2, get_color(p0.rgb, p1.rgb, 1.0, rfpart(var.xend) * var.ygap));
		plot_pixel(fdf, var.xpxl2 + 1, var.ypxl2, get_color(p0.rgb, p1.rgb, 1.0, fpart(var.xend) * var.ygap));
		int y;

		for (y = var.ypxl1 + 1; y < var.ypxl2; y++)
		{
			double percent = (var.swap) ? curr_percent(var.ypxl2, y, var.ypxl1) : // color swap...
				curr_percent(var.ypxl1, y, var.ypxl2);
			plot_pixel(fdf, ipart(var.interx), y, get_color(p0.rgb, p1.rgb, percent, rfpart(var.interx)));
			plot_pixel(fdf, ipart(var.interx) + 1, y,  get_color(p0.rgb, p1.rgb, percent, fpart(var.interx)));
			var.interx += var.gradient;	
		}
	}
	*/
}
