/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:35:19 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/04 22:44:49 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"
// main brightness issue comes from the brightness calculation

static void	plot_main_steep(t_fdf *fdf, t_var var, t_rgb p0, t_rgb p1)
{
	double start;
	double percent;

	start = var.xpxl1;
	while (var.xpxl1++ < var.xpxl2)
	{
		percent = (var.swap_d) ? curr_percent(var.xpxl2, var.xpxl1, start) :
			curr_percent(start, var.xpxl1, var.xpxl2);
		plot_pixel(fdf, ipart(var.intery), var.xpxl1,
				get_color(p0, p1, percent, 1.0));//rfpart(var.intery))); // setting rfpart(var.intery) to 1.0 solves brightness issue
		plot_pixel(fdf, ipart(var.intery) + 1, var.xpxl1,
				get_color(p0, p1, percent, 1.0));//fpart(var.intery)));
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
		percent = (var.swap) ? curr_percent(var.xpxl2, var.xpxl1, start) :
			curr_percent(start, var.xpxl1, var.xpxl2);
		plot_pixel(fdf, var.xpxl1, ipart(var.intery),
				get_color(p0, p1, percent, 1.0));//rfpart(var.intery)));
		plot_pixel(fdf, var.xpxl1, ipart(var.intery) + 1,
				get_color(p0, p1, percent, 1.0));//fpart(var.intery)));
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
//	ft_printf("p0: rgb(%x) p1: rgb(%x))\n", p0.rgb.rgb, p1.rgb.rgb);
	plot_line_init(&p0, &p1, &var);
	plot_line_first_pt(fdf, &var, p0);
	plot_line_second_pt(fdf, &var, p1);
	plot_line_main(fdf, var, p0.rgb, p1.rgb);
}
