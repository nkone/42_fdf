/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_help_driver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:42:59 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/01 15:35:40 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	draw_help_menu(t_fdf *fdf)
{
	int fd;

	fd = open(FDF_HELP_PATH, O_RDONLY);
	ft_memset(fdf->data_addr, 25, WIN_W * WIN_H * (fdf->bits_per_pix / 8));
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	if (fd > 0)
	{
		draw_help_title(fd, fdf);
		draw_help_mouse(fd, fdf);
		draw_help_description_view(fd, fdf);
		draw_help_description_theme(fd, fdf);
		draw_help_description_depth(fd, fdf);
		draw_help_description_brightness(fd, fdf);
		draw_help_description_z_zoom(fd, fdf);
		draw_help_description_z_accel(fd, fdf);
		draw_help_button(fd, fdf);
		draw_help_utility(fd, fdf);
	}
	else
		perror("Check for help file in read_me folder");
	close(fd);
}
