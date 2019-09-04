/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:14:52 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/02 20:10:47 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static int	read_fdf(const char *file, t_fdf *fdf)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		abort_fdf();
	else
	{
		fdf->data->map = parse_fdf(fd, fdf);
		close(fd);
		fdf_zoom_magic(fdf);
	}
	return (0);
}

int			main(int argc, char *argv[])
{
	t_fdf	*fdf;

	fdf = NULL;
	if (argc != 2)
	{
		ft_printf(FDF_USAGE);
		return (0);
	}
	fdf = fdf_init();
	read_fdf(argv[1], fdf);
	draw(fdf, fdf->data);
	draw_menu(fdf);
	mlx_hook(fdf->win, 2, 0, key_control, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win, 6, 0, mouse_move, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
