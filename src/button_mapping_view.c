/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_button_mapping.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:07:17 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/01 14:40:44 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static void	handle_view_button_2(int x, int y, t_fdf *fdf)
{
	double h;

	h = 7.5;
	if (x >= WIN_W / 30 + 201 && x <= WIN_W / 30 + 293 &&
		y >= WIN_H / h + 37 && y <= WIN_H / h + 50)
	{
		ft_printf("View switched to: PARALLEL\n");
		fdf->cam.projection = PARALLEL;
		fdf->cam.alpha = 0.0;
		fdf->cam.beta = 0.0;
		fdf->cam.eta = 0.0;
	}
}

void		handle_view_button(int x, int y, t_fdf *fdf)
{
	double h;

	h = 7.5;
	if (x >= WIN_W / 30 + 3 && x <= WIN_W / 30 + 48 &&
		y >= WIN_H / h + 37 && y <= WIN_H / h + 50)
	{
		ft_printf("View switched to: ISO\n");
		fdf->cam.projection = ISO;
		fdf->cam.alpha = 0.0;
		fdf->cam.beta = 0.0;
		fdf->cam.eta = 0.0;
	}
	if (x >= WIN_W / 30 + 69 && x <= WIN_W / 30 + 171 &&
		y >= WIN_H / h + 37 && y <= WIN_H / h + 50)
	{
		ft_printf("View switched to: ELEVATION\n");
		fdf->cam.projection = ELEVATION;
		fdf->cam.alpha = -7.855;
		fdf->cam.beta = 0.0;
		fdf->cam.eta = 0.0;
	}
	handle_view_button_2(x, y, fdf);
}
