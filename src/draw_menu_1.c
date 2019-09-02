/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:28:41 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/01 14:52:56 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	draw_view_menu(t_fdf *fdf)
{
	double h;

	h = 7.5;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 50 + (12 * 4), WIN_H / h,
		FDF_WHITE, "VIEW");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 30,
		(fdf->cam.projection == ISO) ? FDF_RED : FDF_WHITE, "[ISO]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 5, WIN_H / h + 30,
		(fdf->cam.projection == ELEVATION) ?
		FDF_RED : FDF_WHITE, "[ELEVATION]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 16) + 5, WIN_H / h + 30,
		(fdf->cam.projection == PARALLEL) ? FDF_RED : FDF_WHITE, "[PARALLEL]");
}

void	draw_info_angle_menu(t_fdf *fdf)
{
	double	h;
	char	*buff;

	h = 4.7;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 50 + (12 * 4), WIN_H / h, FDF_WHITE, "INFO");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 30,
		FDF_WHITE, "Rotation angle x:     y:     z:");
	buff = ft_itoa(fdf->cam.alpha * 100);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 170, WIN_H / h + 30,
		(fdf->cam.alpha <= 0.0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
	buff = ft_itoa(fdf->cam.beta * 100);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 240, WIN_H / h + 30,
		(fdf->cam.beta <= 0.0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
	buff = ft_itoa(fdf->cam.eta * 100);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 310, WIN_H / h + 30,
		(fdf->cam.eta <= 0.0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
}

void	draw_info_min_max_menu(t_fdf *fdf)
{
	double	h;
	char	*buff;

	h = 4.7;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 60, FDF_WHITE, "Min:    Max:");
	buff = ft_itoa(fdf->min);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 40, WIN_H / h + 60,
		(fdf->min < 0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
	buff = ft_itoa(fdf->max);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 120, WIN_H / h + 60,
		(fdf->max < 0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
}

void	draw_theme_menu(t_fdf *fdf)
{
	double h;

	h = 2.35;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h,
		FDF_WHITE, "THEME");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 10, WIN_H / h - 50,
		(fdf->theme == DEFAULT && fdf->data->map_color == false) ?
		FDF_RED : FDF_WHITE, "|-[DEFAULT]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 10, WIN_H / h - 25,
		(fdf->theme == HOT && fdf->data->map_color == false) ?
		FDF_ORANGE : FDF_WHITE, "|-[HOT]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 10, WIN_H / h + 25,
		(fdf->theme == COLD && fdf->data->map_color == false) ?
		FDF_CORN_FLOWER_BLUE : FDF_WHITE, "|-[COLD]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 10, WIN_H / h + 50,
		(fdf->theme == CUSTOM && fdf->data->map_color == false)
		? FDF_YELLOW : FDF_WHITE, "|-[CUSTOM]");
}

void	draw_depth_menu(t_fdf *fdf)
{
	double	h;
	char	*buff;

	h = 1.88;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h, FDF_WHITE, "DEPTH");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 20, WIN_H / h,
		(fdf->cam.depth) ? FDF_GREEN_YELLOW : FDF_WHITE, "[ON]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 9) + 40, WIN_H / h,
		(!fdf->cam.depth) ? FDF_RED : FDF_WHITE, "[OFF]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 10, WIN_H / h + 50,
		FDF_WHITE, "[-] BRIGHTNESS [+]");
	buff = ft_itoa(fdf->cam.brightness);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 95, WIN_H / h + 70, FDF_WHITE, buff);
	free(buff);
}
