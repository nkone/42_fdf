/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_info_wrapper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:09:03 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/01 17:05:56 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static void	shell_zoom_info(t_fdf *fdf)
{
	ft_printf(
			"============================\n"
			"\tZoom info\n"
			"============================\n"
			"ZOOM: %.1f\n"
			"ZOOM ACCEL: %.1f\n"
			"Z ZOOM: %.1f\n"
			"Z ACCEL: %.1f\n", fdf->cam.zoom, fdf->cam.zoom_accel,
			fdf->cam.z_zoom, fdf->cam.z_accel);
}

static void	shell_camera_info(t_fdf *fdf)
{
	ft_printf(
			"===========================\n"
			"\tCAMERA SETTINGS\n"
			"===========================\n"
			"Angle| x: %s%.2f "P_NC"y: %s%.2f "P_NC"z: %s%.2f\n"P_NC
			"Brightness: %s%d\n"P_NC
			"Depth: %s%s\n"P_NC
			"After Image Mode: %s%s\n"P_NC,
			(fdf->cam.alpha < 0.0) ? P_RED : P_GREEN, fdf->cam.alpha,
			(fdf->cam.beta < 0.0) ? P_RED : P_GREEN, fdf->cam.beta,
			(fdf->cam.eta < 0.0) ? P_RED : P_GREEN, fdf->cam.eta,
			(fdf->cam.brightness > 0) ? P_RED : P_GREEN, fdf->cam.brightness,
			(fdf->cam.depth) ? P_GREEN : P_RED,
			(fdf->cam.depth) ? "ON" : "OFF",
			(fdf->cam.after_img) ? P_RED : P_RED,
			(fdf->cam.after_img) ? "Enabled" : "Disabled");
}

static void	shell_map_info(t_fdf *fdf)
{
	ft_printf(
			"===========================\n"
			"\tMAP INFO\n"
			"===========================\n"
			"size (width x height): %d x %d\n"
			"[z] min: %d max: %d\n",
			fdf->data->map_w, fdf->data->map_h, fdf->min, fdf->max);
}

void		shell_info_wrapper(t_fdf *fdf)
{
	shell_zoom_info(fdf);
	shell_camera_info(fdf);
	shell_map_info(fdf);
}
