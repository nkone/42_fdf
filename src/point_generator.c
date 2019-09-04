/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:25:13 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/04 14:36:00 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

t_pt	get_point(t_pt p, t_fdf *fdf)
{
	p.x *= fdf->cam.zoom;
	p.y *= fdf->cam.zoom;
	p.x -= (float)(fdf->data->map_w * fdf->cam.zoom) / 2;
	p.y -= (float)(fdf->data->map_h * fdf->cam.zoom) / 2;
	fdf_rot_x(&p.y, &p.z, fdf->cam.alpha);
	fdf_rot_y(&p.x, &p.z, fdf->cam.beta);
	fdf_rot_z(&p.x, &p.y, fdf->cam.eta);
	if (fdf->cam.projection == ISO)
		fdf_iso(&p.x, &p.y, p.z);
	p.x += (WIN_W / 2) + fdf->cam.x_offset;
	p.y += (WIN_H / 2) + fdf->cam.y_offset;
	return (p);
}

t_pt	gen_point(double x, double y, t_fdf *fdf)
{
	t_pt	p;
	t_rgb	*rgb;
	int		idx;

	idx = y * fdf->data->map_w + x;
	p.x = x;
	p.y = y;
	p.z = fdf->data->map[idx] * fdf->cam.z_zoom;
	if (fdf->data->map_color)
		int_to_rgb(&p.rgb, fdf->data->c_map[idx]);
	else
	{
		rgb = fdf->ramp[get_color_index(p.z, fdf->ramp_size)];
		p.rgb = *rgb;
	}
	p.rgb = (fdf->cam.depth) ? apply_depth(p.z, p.rgb, fdf) : p.rgb;
	apply_brightness(&p.rgb, fdf->cam.brightness);
	return (p);
}

int		draw(t_fdf *fdf, t_map *data)
{
	int	x;
	int	y;

	draw_bg(fdf);
	y = 0;
	while (y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			if (x != data->map_w - 1)
				plot_line(fdf, get_point(gen_point(x, y, fdf), fdf),
					get_point(gen_point(x + 1, y, fdf), fdf));
			if (y != data->map_h - 1)
				plot_line(fdf, get_point(gen_point(x, y, fdf), fdf),
				get_point(gen_point(x, y + 1, fdf), fdf));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_menu(fdf);
	return (0);
}

void	draw_multi_fdf(t_fdf *fdf, t_files *fdf_queue)
{
	int fd;

	if (!fdf_queue)
	{
		ft_printf("Queue has reached NULL pointer:\n");
		return ;
	}
	fd = open(fdf_queue->path, O_RDONLY);
	if (fd > 0)
	{
		fdf->data->map_color = false;
		ft_printf("drawing: %s\n", fdf_queue->name);
		free(fdf->data->map);
		free(fdf->data->c_map);
		fdf->data->map = parse_fdf(fd, fdf);
		close(fd);
		extract_min_max(fdf->data->map,
				&fdf->min, &fdf->max, fdf->data->map_size);
		draw(fdf, fdf->data);
	}
	else
		abort_fdf();
}
