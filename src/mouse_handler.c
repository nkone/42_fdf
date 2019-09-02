/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:24:32 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:04:49 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	handle_mouse_left_b(int x, int y, t_fdf *fdf)
{
	fdf->mouse.left_b = true;
	handle_view_button(x, y, fdf);
	handle_theme_button(x, y, fdf);
	handle_depth_button(x, y, fdf);
	handle_brightness_button(x, y, fdf);
	handle_z_zoom_button(x, y, fdf);
	handle_z_accel_button(x, y, fdf);
	handle_zoom_button(x, y, fdf);
	handle_extra_button(x, y, fdf);
}

void	handle_mouse_right_b(int button, t_fdf *fdf)
{
	if (!fdf->mouse.right_b && button == MOUSE_SCROLL_UP)
		fdf->cam.z_zoom += fdf->cam.z_accel;
	if (!fdf->mouse.right_b && button == MOUSE_SCROLL_DOWN)
		fdf->cam.z_zoom -= fdf->cam.z_accel;
	if (fdf->mouse.right_b && button == MOUSE_SCROLL_UP)
		fdf->cam.zoom += fdf->cam.zoom_accel;
	if (fdf->mouse.right_b && button == MOUSE_SCROLL_DOWN)
		fdf->cam.zoom -= fdf->cam.zoom_accel;
}

int		mouse_press(int button, int x, int y, t_fdf *fdf)
{
	fdf->mouse.x = x;
	fdf->mouse.y = y;
	fdf->help = false;
	if (button == MOUSE_LEFT_B)
		handle_mouse_left_b(x, y, fdf);
	if (button == MOUSE_RIGHT_B)
		fdf->mouse.right_b = true;
	handle_mouse_right_b(button, fdf);
	draw(fdf, fdf->data);
	return (0);
}

int		mouse_release(int button, int x, int y, t_fdf *fdf)
{
	fdf->mouse.x = x;
	fdf->mouse.y = y;
	if (button == MOUSE_LEFT_B)
		fdf->mouse.left_b = false;
	if (button == MOUSE_RIGHT_B)
		fdf->mouse.right_b = false;
	return (0);
}

int		mouse_move(int x, int y, t_fdf *fdf)
{
	if (fdf->mouse.left_b == false && fdf->mouse.right_b == false)
		return (0);
	fdf->mouse.prev_x = fdf->mouse.x;
	fdf->mouse.prev_y = fdf->mouse.y;
	fdf->mouse.x = x;
	fdf->mouse.y = y;
	if (fdf->mouse.left_b)
	{
		fdf->cam.beta += (x - fdf->mouse.prev_x) * 0.002;
		fdf->cam.alpha += (y - fdf->mouse.prev_y) * 0.002;
	}
	if (fdf->mouse.right_b)
		fdf->cam.eta -= (x - fdf->mouse.prev_x) * 0.002;
	draw(fdf, fdf->data);
	return (0);
}
