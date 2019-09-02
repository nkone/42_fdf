/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:30:54 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/27 20:06:24 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	plot_line_main(t_fdf *fdf, t_var var, t_rgb p0, t_rgb p1)
{
	double start;
	double percent;

	start = var.xpxl1;
	if (var.steep)
	{
		while (var.xpxl1++ < var.xpxl2)
		{
			percent = (var.swap_d) ? curr_percent(var.xpxl2, var.xpxl1, start) :
				curr_percent(start, var.xpxl1, var.xpxl2);
			plot_pixel(fdf, ipart(var.intery), var.xpxl1, 
					get_color(p0, p1, percent, rfpart(var.intery)));
			plot_pixel(fdf, ipart(var.intery) + 1, var.xpxl1,
					get_color(p0, p1, percent, fpart(var.intery)));
			var.intery += var.gradient;
		}
	}
	else
	{
		while (var.xpxl1++ < var.xpxl2)
		{
			percent = (var.swap) ? curr_percent(var.xpxl2, var.xpxl1, start) :
				curr_percent(start, var.xpxl1, var.xpxl2);
			plot_pixel(fdf, var.xpxl1, ipart(var.intery),
					get_color(p0, p1, percent, rfpart(var.intery)));
			plot_pixel(fdf, var.xpxl1, ipart(var.intery) + 1,
					get_color(p0, p1, percent, fpart(var.intery)));
			var.intery += var.gradient;
		}
	}
}
