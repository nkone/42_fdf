/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:17:47 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/06 15:21:21 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	plot_pixel(t_fdf *frame, int x, int y, int rgb)
{
	int i;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		i = (x * frame->bits_per_pix / 8) + (y * frame->size_line);
		frame->data_addr[i++] = rgb;
		frame->data_addr[i++] = rgb >> 8;
		frame->data_addr[i] = rgb >> 16;
	}
}

t_rgb	apply_depth(int z, t_rgb rgb, t_fdf *fdf)
{
	double percent;

	percent = fdf->coef_m * z + fdf->coef_b;
	percent += fdf->cam.zoom / fabs(fdf->cam.depth_f * 4);
	if (percent >= 1.0)
		percent = 1.0;
	else if (percent < 0.0)
		percent = 0.0;
	rgb.r *= percent;
	rgb.g *= percent;
	rgb.b *= percent;
	rgb.rgb = rgb.r;
	rgb.rgb = (rgb.rgb << 8) + rgb.g;
	rgb.rgb = (rgb.rgb << 8) + rgb.b;
	return (rgb);
}

void	apply_brightness(t_rgb *rgb, int brightness)
{
	rgb->r += brightness;
	if (rgb->r > 255)
		rgb->r = 255;
	else if (rgb->r < 0)
		rgb->r = 0;
	rgb->g += brightness;
	if (rgb->g > 255)
		rgb->g = 255;
	else if (rgb->g < 0)
		rgb->g = 0;
	rgb->b += brightness;
	if (rgb->b > 255)
		rgb->b = 255;
	else if (rgb->b < 0)
		rgb->b = 0;
	rgb->rgb = rgb->r;
	rgb->rgb = (rgb->rgb << 8) + rgb->g;
	rgb->rgb = (rgb->rgb << 8) + rgb->b;
}

int		get_color(t_rgb start, t_rgb end, double percent, double brightness)
{
	t_rgb ret;

	brightness += 0.2; // offset this so it's 20% brighter
	(brightness > 1.0) && (brightness = 1.0);
//	printf("bright: %f\t percent: %f\t", brightness, percent);
//	printf("rgb_start(%d,%d,%d)\t", start.r, start.g, start.b);
//	printf("rgb_end(%d,%d,%d)\t", end.r, end.g, end.b);
	ret.r = ((start.r * (1.0 - percent)) + (end.r * percent)) * brightness;
	ret.g = ((start.g * (1.0 - percent)) + (end.g * percent)) * brightness;
	ret.b = ((start.b * (1.0 - percent)) + (end.b * percent)) * brightness;
//	printf("rgb_ret(%d, %d, %d)\n", ret.r, ret.g, ret.b);
	ret.rgb = ret.r;
	ret.rgb = (ret.rgb << 8) + ret.g;
	ret.rgb = (ret.rgb << 8) + ret.b;
	return (ret.rgb);
}
