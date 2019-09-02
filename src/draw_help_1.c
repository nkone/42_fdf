/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_help_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:36:20 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:01:40 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	draw_help_title(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;
	int		len;

	line = NULL;
	y = 25;
	while (y <= (25 + (20 * 7)) && get_next_line(fd, &line) == 1)
	{
		len = ft_strlen(line);
		mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 2 - (5 * len), y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_mouse(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;

	line = NULL;
	y = WIN_H / 3;
	while (y <= (WIN_H / 3 + (20 * 10)) && get_next_line(fd, &line) == 1)
	{
		mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 15, y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_description_view(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;

	line = NULL;
	y = WIN_H / 1.7;
	while (y <= (WIN_H / 1.7 + (20 * 11)) && get_next_line(fd, &line) == 1)
	{
		mlx_string_put(fdf->mlx, fdf->win, WIN_W / 15, y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_description_theme(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;

	line = NULL;
	y = WIN_H / 1.25;
	while (y <= (WIN_H / 1.25 + (20 * 7)) && get_next_line(fd, &line) == 1)
	{
		mlx_string_put(fdf->mlx, fdf->win, WIN_W / 15, y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_description_depth(int fd, t_fdf *fdf)
{
	char	*line;
	int		y;
	int		len;

	line = NULL;
	y = WIN_H / 1.6;
	while (y <= (WIN_H / 1.6 + (20 * 5)) && get_next_line(fd, &line) == 1)
	{
		len = ft_strlen(line);
		mlx_string_put(fdf->mlx,
			fdf->win, WIN_W / 1.9 - (5 * len), y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}
