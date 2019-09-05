/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu_driver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:34:17 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/04 21:50:23 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	draw_bg(t_fdf *fdf)
{
	if (fdf->cam.after_img && fdf->cam.brightness < 0)
		ft_memset(fdf->data_addr, fdf->cam.brightness,
				WIN_W * WIN_H * (fdf->bits_per_pix / 8));
	else	
		ft_bzero(fdf->data_addr, WIN_W * WIN_H * (fdf->bits_per_pix / 8));

}

void	draw_menu(t_fdf *fdf)
{
	draw_view_menu(fdf);
	draw_info_angle_menu(fdf);
	draw_info_min_max_menu(fdf);
	draw_theme_menu(fdf);
	draw_depth_menu(fdf);
	draw_z_zoom_menu(fdf);
	draw_z_accel_menu(fdf);
	draw_zoom_menu(fdf);
	draw_after_img_menu(fdf);
	draw_utility_menu(fdf);
}
