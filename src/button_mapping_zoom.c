/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_mapping_zoom.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:15:08 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/04 21:41:32 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	handle_z_zoom_button(int x, int y, t_fdf *fdf)
{
	double h;

	h = 1.5;
	if (x >= WIN_W / 30 + 3 && x <= WIN_W / 30 + 67 &&
		y >= WIN_H / h + 31 && y <= WIN_H / h + 45)
		fdf->cam.z_zoom = 0.05;
	if (x >= WIN_W / 30 + 92 && x <= WIN_W / 30 + 145 &&
		y >= WIN_H / h + 31 && y <= WIN_H / h + 45)
		fdf->cam.z_zoom = 0.5;
	if (x >= WIN_W / 30 + 169 && x <= WIN_W / 30 + 223 &&
		y >= WIN_H / h + 31 && y <= WIN_H / h + 45)
		fdf->cam.z_zoom = 1.0;
}

void	handle_z_accel_button(int x, int y, t_fdf *fdf)
{
	double h;

	h = 1.4;
	if (x >= WIN_W / 30 + 3 && x <= WIN_W / 30 + 57 &&
		y >= WIN_H / h + 30 && y <= WIN_H / h + 45)
		fdf->cam.z_accel = 0.05;
	if (x >= WIN_W / 30 + 90 && x <= WIN_W / 30 + 135 &&
		y >= WIN_H / h + 30 && y <= WIN_H / h + 45)
		fdf->cam.z_accel = 0.5;
	if (x >= WIN_W / 30 + 170 && x <= WIN_W / 30 + 213 &&
		y >= WIN_H / h + 30 && y <= WIN_H / h + 45)
		fdf->cam.z_accel = 1.0;
}

void	handle_zoom_button(int x, int y, t_fdf *fdf)
{
	double h;

	h = 1.25;
	if (x >= WIN_W / 30 + 3 && x <= WIN_W / 30 + 49 &&
		y >= WIN_H / h + 30 && y <= WIN_H / h + 45)
		fdf->cam.zoom_accel = 0.1;
	if (x >= WIN_W / 30 + 63 && x <= WIN_W / 30 + 107 &&
		y >= WIN_H / h + 30 && y <= WIN_H / h + 45)
		fdf->cam.zoom_accel = 1.0;
	if (x >= WIN_W / 30 + 125 && x <= WIN_W / 30 + 167 &&
		y >= WIN_H / h + 30 && y <= WIN_H / h + 45)
		fdf->cam.zoom_accel = 2.0;
	if (x >= WIN_W / 30 + 185 && x <= WIN_W / 30 + 226 &&
		y >= WIN_H / h + 30 && y <= WIN_H / h + 45)
		fdf->cam.zoom_accel = 5.0;
}
