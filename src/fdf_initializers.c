/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_initializers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 20:38:47 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/04 18:57:25 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

t_map	*fdf_init_data_struct(void)
{
	t_map *data;

	(!(data = ft_memalloc(sizeof(t_map)))) && abort_fdf();
	data->map = NULL;
	data->map_w = 0;
	data->map_h = 0;
	data->map_color = false;
	return (data);
}

t_cam	fdf_cam_init(void)
{
	t_cam cam;

	cam.zoom = 50.0;
	cam.zoom_accel = 0.5;
	cam.z_zoom = 1.0;
	cam.z_accel = 0.05;
	cam.alpha = 0.0;
	cam.beta = 0.0;
	cam.eta = 0.0;
	cam.brightness = 0;
	cam.depth = false;
	cam.after_img = false;
	cam.x_offset = 0;
	cam.y_offset = 0;
	cam.projection = ISO;
	return (cam);
}

t_mouse	mouse_init(void)
{
	t_mouse mouse;

	mouse.x = 0;
	mouse.y = 0;
	mouse.prev_x = 0;
	mouse.prev_y = 0;
	mouse.left_b = false;
	mouse.right_b = false;
	return (mouse);
}

t_fdf	*fdf_init(void)
{
	t_fdf *frame;

	frame = NULL;
	(!(frame = ft_memalloc(sizeof(t_fdf)))) && abort_fdf();
	frame->cam = fdf_cam_init();
	(!(frame->mlx = mlx_init())) && abort_fdf();
	(!(frame->win = mlx_new_window(frame->mlx, WIN_W, WIN_H, "42 FDF"))) &&
		abort_fdf();
	(!(frame->img = mlx_new_image(frame->mlx, WIN_W, WIN_H))) && abort_fdf();
	(!(frame->data_addr =
		mlx_get_data_addr(frame->img, &(frame->bits_per_pix),
		&(frame->size_line), &(frame->endian)))) && abort_fdf();
	frame->data = fdf_init_data_struct();
	frame->theme = DEFAULT;
	frame->ramp_list = fdf_gen_color_ramp(frame);
	frame->ramp = fdf_index_color_ramp(frame->ramp_list);
	frame->ramp_size = count_ramp(frame->ramp_list);
	frame->mouse = mouse_init();
	frame->help = false;
	frame->multi_fdf = false;
	frame->fdf_queue = NULL;
	return (frame);
}
