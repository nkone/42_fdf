/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_help_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:38:43 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/09 11:59:30 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	draw_help_description_brightness(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;

	line = NULL;
	y = WIN_H / 1.3;
	while (y <= (WIN_H / 1.3 + (20 * 4)) && get_next_line(fd, &line) == 1)
	{
		mlx_string_put(fdf->mlx, fdf->win, WIN_W / 2.5, y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_description_z_zoom(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;

	line = NULL;
	y = WIN_H / 1.6;
	while (y <= (WIN_H / 1.6 + (20 * 3)) && get_next_line(fd, &line) == 1)
	{
		mlx_string_put(fdf->mlx, fdf->win, WIN_W / 1.5, y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_description_z_accel(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;

	line = NULL;
	y = WIN_H / 1.4;
	while (y <= (WIN_H / 1.4 + (20 * 4)) && get_next_line(fd, &line) == 1)
	{
		mlx_string_put(fdf->mlx, fdf->win, WIN_W / 1.5, y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_button(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;

	line = NULL;
	y = WIN_H / 3;
	while (y <= (WIN_H / 3 + (20 * 14)) && get_next_line(fd, &line) == 1)
	{
		mlx_string_put(fdf->mlx, fdf->win, WIN_W / 2, y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_utility(int fd, t_fdf *fdf)
{
	char *line;

	line = NULL;
	get_next_line(fd, &line);
	mlx_string_put(fdf->mlx, fdf->win, WIN_W / 30, WIN_H / 30, FDF_WHITE, line);
	free(line);
}
