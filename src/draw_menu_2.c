/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:31:39 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:02:16 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	draw_z_zoom_menu(t_fdf *fdf)
{
	double	h;
	char	*buff;

	h = 1.5;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 85, WIN_H / h, FDF_WHITE, "Z ZOOM x");
	buff = ft_itoa(fdf->cam.z_zoom);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 170, WIN_H / h,
		(fdf->cam.z_zoom <= 0.0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 25,
		(fdf->cam.z_zoom == 0.05) ? FDF_RED : FDF_WHITE, "[x0.05]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 7) + 5, WIN_H / h + 25,
		(fdf->cam.z_zoom == 0.5) ? FDF_RED : FDF_WHITE, "[x0.5]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 13) + 10, WIN_H / h + 25,
		(fdf->cam.z_zoom == 1.0) ? FDF_RED : FDF_WHITE, "[x1.0]");
	free(buff);
}

void	draw_z_accel_menu(t_fdf *fdf)
{
	double h;

	h = 1.4;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 75, WIN_H / h, FDF_WHITE, "Z ACCEL +/-");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 25,
		(fdf->cam.z_accel == 0.05) ? FDF_RED : FDF_WHITE, "[0.05]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 7) + 5, WIN_H / h + 25,
		(fdf->cam.z_accel == 0.5) ? FDF_RED : FDF_WHITE, "[0.5]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 13) + 10, WIN_H / h + 25,
		(fdf->cam.z_accel == 1.0) ? FDF_RED : FDF_WHITE, "[1.0]");
}

void	draw_zoom_menu(t_fdf *fdf)
{
	double h;

	h = 1.25;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 50, WIN_H / h, FDF_WHITE, "ZOOM ACCEL +/-");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 25,
		(fdf->cam.zoom_accel == 0.5) ? FDF_RED : FDF_WHITE, "[0.5]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5), WIN_H / h + 25,
		(fdf->cam.zoom_accel == 1.0) ? FDF_RED : FDF_WHITE, "[1.0]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 10), WIN_H / h + 25,
		(fdf->cam.zoom_accel == 2.0) ? FDF_RED : FDF_WHITE, "[2.0]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 15), WIN_H / h + 25,
		(fdf->cam.zoom_accel == 5.0) ? FDF_RED : FDF_WHITE, "[5.0]");
}

void	draw_after_img_menu(t_fdf *fdf)
{
	char	*warning;
	int		len;

	warning = "[ AFTER IMAGE MODE ENABLED ]";
	len = ft_strlen(warning);
	if (fdf->cam.after_img)
		mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 2 - (5 * len), 20, FDF_RED, warning);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H - 50,
		(fdf->cam.after_img) ? FDF_RED : FDF_WHITE, "AFTER IMAGE MODE");
}

void	draw_utility_menu(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / 30, FDF_RED, "[ESC]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W - 200, WIN_H / 30, FDF_WHITE, "Press h for help");
}
