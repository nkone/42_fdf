/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 18:00:37 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/27 20:04:49 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include <stdio.h>
#include "ft_fdf.h"
#include "libft/libft.h"
#include "libft/ft_printf.h"
/*
** find brightness function for Xiaolin Wu's algo ✓
** Use it to plot ✓
** Figured how to convert rgb to one int ✓
** Create a struct to store rgb value ✓
** Create a function that takes in two points and draw a line ✓
** Organize the plot function. (moved out of main)
** Create a struct to store plotting points ✓
** Reduce parameters in plot function
** Create a parser ✓
** Create an init function ✓
** Create a color ramp ✓
** Create theme for color ramp✓
** Clean up color ramp function✓
** How to draw with linear gradent?✓
** Test out the color ramp with 42 map ✓
** Find a way to centralize the map with any size (somewhat lol)
** Make a menu ✓
** Fix button mapping
** Create help menu
** Create a reset button
** Handle error maps
** Create a prototype for shell built in ✓
** Create depth ✓
** Scaling buttons ...
** If you're gonna do it, do it right.
*/

void	plot_pixel(t_fdf *frame, int x, int y, int rgb)
{
	int i;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
	i = (x * frame->bits_per_pix / 8) + (y  * frame->size_line);
		frame->data_addr[i++] = rgb;
		frame->data_addr[i++] = rgb >> 8;
		frame->data_addr[i] = rgb >> 16;
	}
}
int		fdf_rgb(t_fdf fdf, double c)
{
//	printf("c value: %f\n", c);
	fdf.color.r *= c;
	fdf.color.g *= c;
	fdf.color.b *= c;
	fdf.color.rgb = fdf.color.r;
	fdf.color.rgb = (fdf.color.rgb << 8) + fdf.color.g;
	fdf.color.rgb = (fdf.color.rgb << 8) + fdf.color.b;
	return (fdf.color.rgb);
}

double ipart(double x)
{
	return floor(x);
}

double round(double x)
{
	return ipart(x + 0.5);
}

double fpart(double x)
{
	return x - floor(x);
}

double rfpart(double x)
{
	return 1 - fpart(x);
}

double curr_percent(double start, double curr, double end)
{
	double here;
	double distance;
	double where;
	
	distance = end - start;
	where = curr - start;
	here = (distance == 0.0) ? 1.0: (where / distance);

	return (here);
}

int	get_color(t_rgb start, t_rgb end, double percent, double brightness)
{
	t_rgb ret;
	
	ret.r = ((start.r * (1.0 - percent)) + (end.r * percent)) * brightness;
	ret.g = ((start.g * (1.0 - percent)) + (end.g * percent)) * brightness;
	ret.b = ((start.b * (1.0 - percent)) + (end.b * percent)) * brightness;
	ret.rgb = ret.r;
	ret.rgb = (ret.rgb << 8) + ret.g;
	ret.rgb = (ret.rgb << 8) + ret.b;
	return (ret.rgb);
}
	
	
void	plot_line_init(t_pt *p0, t_pt *p1, t_var *var)
{
	var->steep = fabs(p1->y - p0->y) > fabs(p1->x - p0->x);
	var->swap_d = false;
	var->swap = false;
	if (var->steep)
	{
		var->swap = true;
		ft_swap_double(&(p0->x), &(p0->y));
		ft_swap_double(&(p1->x), &(p1->y));
	}
	if (p0->x > p1->x)
	{
		if (!var->steep)
			var->swap = true;
		var->swap_d = true;
		ft_swap_double(&(p0->x), &(p1->x));
		ft_swap_double(&(p0->y), &(p1->y));
	}
	var->dx = p1->x - p0->x;
	var->dy = p1->y - p0->y;
	var->gradient = (var->dx == 0.0) ? 1.0 : (var->dy / var->dx);
}

void	plot_line_first_pt(t_fdf *fdf, t_var *var, t_pt p0)
{
	var->xend = round(p0.x);
	var->yend = p0.y + var->gradient * (var->xend - p0.x);
	var->xgap = rfpart(p0.x + 0.5);
	var->xpxl1 = var->xend;
	var->ypxl1 = ipart(var->yend);
	if (var->steep)
	{
		plot_pixel(fdf, var->ypxl1, var->xpxl1,
				get_color(p0.rgb, p0.rgb, 1.0, rfpart(var->yend) * var->xgap));
		plot_pixel(fdf, var->ypxl1 + 1, var->xpxl1,
				get_color(p0.rgb, p0.rgb, 1.0, fpart(var->yend) * var->xgap));
	}
	else
	{
		plot_pixel(fdf, var->xpxl1, var->ypxl1,
				get_color(p0.rgb, p0.rgb, 1.0, rfpart(var->yend) * var->xgap));
		plot_pixel(fdf, var->xpxl1 + 1, var->ypxl1,
				get_color(p0.rgb, p0.rgb, 1.0, fpart(var->yend) * var->xgap));
	}
}

void	plot_line_second_pt(t_fdf *fdf, t_var *var, t_pt p1)
{
	var->intery = var->yend + var->gradient;
	var->xend = round(p1.x);
	var->yend = p1.y + var->gradient * (var->xend - p1.x);
	var->xgap = fpart(p1.x + 0.5);
	var->xpxl2 = var->xend;
	var->ypxl2 = ipart(var->yend);
	if (var->steep)
	{
		plot_pixel(fdf, var->ypxl2, var->xpxl2,
				get_color(p1.rgb, p1.rgb, 1.0, rfpart(var->yend) * var->xgap));
		plot_pixel(fdf, var->ypxl2 + 1, var->xpxl2,
				get_color(p1.rgb, p1.rgb, 1.0, fpart(var->yend) * var->xgap));
	}
	else
	{
		plot_pixel(fdf, var->xpxl2, var->ypxl2,
				get_color(p1.rgb, p1.rgb, 1.0, rfpart(var->yend) * var->xgap));
		plot_pixel(fdf, var->xpxl2, var->ypxl2 + 1,
				get_color(p1.rgb, p1.rgb, 1.0, fpart(var->yend) * var->xgap));
	}
}

void	plot_line_main(t_fdf *fdf, t_var var, t_rgb p0, t_rgb p1)
{
	double start;
	double percent;

	start = var.xpxl1;
	if (var.steep)
	{
		while (var.xpxl1++ < var.xpxl2)
		{
			percent = (var.swap_d) ? curr_percent(var.xpxl2, var.xpxl1, start) :
				curr_percent(start, var.xpxl1, var.xpxl2);
			plot_pixel(fdf, ipart(var.intery), var.xpxl1, 
					get_color(p0, p1, percent, rfpart(var.intery)));
			plot_pixel(fdf, ipart(var.intery) + 1, var.xpxl1,
					get_color(p0, p1, percent, fpart(var.intery)));
			var.intery += var.gradient;
		}
	}
	else
	{
		while (var.xpxl1++ < var.xpxl2)
		{
			percent = (var.swap) ? curr_percent(var.xpxl2, var.xpxl1, start) :
				curr_percent(start, var.xpxl1, var.xpxl2);
			plot_pixel(fdf, var.xpxl1, ipart(var.intery),
					get_color(p0, p1, percent, rfpart(var.intery)));
			plot_pixel(fdf, var.xpxl1, ipart(var.intery) + 1,
					get_color(p0, p1, percent, fpart(var.intery)));
			var.intery += var.gradient;
		}
	}
}
t_rgb	apply_depth(double z, t_rgb rgb, t_fdf *fdf)
{
	double percent;

	percent = fdf->coef_m * z + fdf->coef_b;
	percent += fdf->cam.zoom/fabs(fdf->cam.depth_f * 5);
	if (percent >= 1.0)
		percent = 1.0;
	if (percent < 0.0)
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
	if (rgb->r < 0)
		rgb->r = 0;
	rgb->g += brightness;
	if (rgb->g > 255)
		rgb->g = 255;
	if (rgb->g < 0)
		rgb->g = 0;
	rgb->b += brightness;
	if (rgb->b > 255)
		rgb->b = 255;
	if (rgb->b < 0)
		rgb->b = 0;
	rgb->rgb = rgb->r;
	rgb->rgb = (rgb->rgb << 8) + rgb->g;
	rgb->rgb = (rgb->rgb << 8) + rgb->b;
}
void	plot_line(t_fdf *fdf, t_pt p0, t_pt p1)
{
	t_var var;
//	puts("start");
//	printf("p0 (%.1f, %.1f)\tp1(%.1f,%.1f)\n", p0.x, p0.y, p1.x, p1.y);
	plot_line_init(&p0, &p1, &var);
//	printf("p0 (%.1f, %.1f)\tp1(%.1f,%.1f)\nrgb(%d, %d, %d)\trgb(%d,%d,%d)\n", p0.x, p0.y, p1.x, p1.y, p0.rgb.r, p0.rgb.g, p0.rgb.b, p1.rgb.r, p1.rgb.g, p1.rgb.b);
	
	plot_line_first_pt(fdf, &var, p0);
	plot_line_second_pt(fdf, &var, p1);
	plot_line_main(fdf, var, p0.rgb, p1.rgb);
}


void	fdf_rot_x(double *y , int *z, double alpha)
{
	double prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

void	fdf_rot_y(double *x, int *z, double beta)
{
	double prev_x;

	prev_x = *x;
	*x = prev_x * cos(beta) + *z * sin(beta);
	*z = -prev_x * sin(beta) + *z * cos(beta);
}

void	fdf_rot_z(double *x, double *y, double eta)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(eta) - prev_y * sin(eta);
	*y = prev_x * sin(eta) + prev_y * cos(eta);
}
void	fdf_iso(double *x , double *y, int z)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(ISO_RAD);
	*y = (prev_x + prev_y) * sin(ISO_RAD) - z;
}

t_pt	get_point(t_pt p, t_fdf *fdf)
{
	p.x *= fdf->cam.zoom;
	p.y *= fdf->cam.zoom;
//	p.z *= fdf->cam.z_zoom;
	
	p.x -= (float)(fdf->data->map_w * fdf->cam.zoom) / 2;
	p.y -= (float)(fdf->data->map_h * fdf->cam.zoom) / 2;
//	fdf_rot_z(&p.x, &p.y, fdf->cam.eta);
	fdf_rot_x(&p.y, &p.z, fdf->cam.alpha);
	fdf_rot_y(&p.x, &p.z, fdf->cam.beta);
	fdf_rot_z(&p.x, &p.y, fdf->cam.eta);
	if (fdf->cam.projection == ISO)
		fdf_iso(&p.x, &p.y, p.z);
	p.x += (WIN_W / 2) + fdf->cam.x_offset;//+ (WIN_H / 10);
	p.y += (WIN_H / 2) + fdf->cam.y_offset;// + (fdf->data->map_h * 2;//- (WIN_W / 10);
//	printf("(%.1f, %.1f, %d)\n", p.x, p.y, p.z);
	return (p);
}

int get_color_index(int z, int size);
int count_ramp(t_ramp *ramp);


t_pt	gen_point(double x, double y, t_fdf *fdf)
{
	t_pt p;
	t_rgb *rgb;
	int idx;

	idx = y * fdf->data->map_w + x;
	p.x = x;
	p.y = y;
	p.z = fdf->data->map[idx] * fdf->cam.z_zoom;
	
	rgb = fdf->ramp[get_color_index(p.z, fdf->ramp_size)];
	p.rgb = *rgb;
	p.rgb = (fdf->cam.depth) ? apply_depth(p.z, *rgb, fdf) : *rgb;
	apply_brightness(&p.rgb, fdf->cam.brightness);
	return (p);
}

void	draw_bg(t_fdf *fdf)
{
	if (fdf->cam.after_img && fdf->cam.brightness < 0)
		ft_memset(fdf->data_addr, fdf->cam.brightness,
				WIN_W * WIN_H * (fdf->bits_per_pix /8));
	else
		ft_bzero(fdf->data_addr, WIN_W * WIN_H * (fdf->bits_per_pix /8));
}

void	draw_view_menu(t_fdf *fdf)
{
	double h;

	h = 7.5;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 50 + (12 * 4), WIN_H / h,
		FDF_WHITE, "VIEW");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 30,
		(fdf->cam.projection == ISO) ? FDF_RED: FDF_WHITE, "[ISO]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 5, WIN_H / h + 30,
		(fdf->cam.projection == ELEVATION)? FDF_RED : FDF_WHITE, "[ELEVATION]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 16) + 5, WIN_H / h + 30,
		(fdf->cam.projection == PARALLEL)? FDF_RED : FDF_WHITE, "[PARALLEL]");
}

void	draw_info_angle_menu(t_fdf *fdf)
{
	double	h;
	char	*buff;

	h = 4.7;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 50 + (12 * 4), WIN_H / h, FDF_WHITE, "INFO");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 30,
		FDF_WHITE, "Rotation angle x:     y:     z:");
	buff = ft_itoa(fdf->cam.alpha * 100);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 170, WIN_H / h + 30,
		(fdf->cam.alpha <= 0.0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
	buff = ft_itoa(fdf->cam.beta * 100);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 240, WIN_H / h + 30,
		(fdf->cam.beta <= 0.0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
	buff = ft_itoa(fdf->cam.eta * 100);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 310, WIN_H / h + 30,
		(fdf->cam.eta <= 0.0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
}

void	draw_info_min_max_menu(t_fdf *fdf)
{
	double h;
	char *buff;
	
	h = 4.7;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 60, FDF_WHITE, "Min:    Max:");
	buff = ft_itoa(fdf->min);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 40, WIN_H / h + 60,
		(fdf->min < 0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
	buff = ft_itoa(fdf->max);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 120, WIN_H / h + 60,
		(fdf->max < 0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	free(buff);
}

void	draw_theme_menu(t_fdf *fdf)
{
	double h;

	h = 2.35;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h,
		FDF_WHITE, "THEME");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 10, WIN_H / h - 50,
		(fdf->theme == DEFAULT) ? FDF_RED : FDF_WHITE, "|-[DEFAULT]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 10, WIN_H / h - 25,
		(fdf->theme == HOT) ? FDF_ORANGE: FDF_WHITE, "|-[HOT]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 10, WIN_H / h + 25,
		(fdf->theme == COLD) ? FDF_CORN_FLOWER_BLUE : FDF_WHITE, "|-[COLD]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 10, WIN_H / h + 50,
		(fdf->theme == CUSTOM) ? FDF_YELLOW : FDF_WHITE, "|-[CUSTOM]");
}

void	draw_depth_menu(t_fdf *fdf)
{
	double h;
	char *buff;

	h = 1.88;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h, FDF_WHITE, "DEPTH");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5) + 20, WIN_H / h,
		(fdf->cam.depth) ? FDF_RED: FDF_WHITE, "[ON]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 9) + 40, WIN_H / h,
		(!fdf->cam.depth) ? FDF_RED: FDF_WHITE, "[OFF]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 10, WIN_H / h + 50,
		FDF_WHITE, "[-] BRIGHTNESS [+]");
	buff = ft_itoa(fdf->cam.brightness);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 95, WIN_H / h + 70, FDF_WHITE, buff);
	free(buff);
}

void	draw_z_zoom_menu(t_fdf *fdf)
{
	double	h;
	char	*buff;

	h = 1.5;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 85, WIN_H / h, FDF_WHITE, "Z ZOOM x");
	buff = ft_itoa(fdf->cam.z_zoom);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 170, WIN_H /h,
		(fdf->cam.z_zoom <= 0.0) ? FDF_RED : FDF_GREEN_YELLOW, buff);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 25,
		(fdf->cam.z_zoom == 0.05) ? FDF_RED : FDF_WHITE, "[x0.05]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 7) + 5, WIN_H / h + 25,
		(fdf->cam.z_zoom == 0.5) ? FDF_RED : FDF_WHITE, "[x0.5]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 13) + 10, WIN_H / h + 25,
		(fdf->cam.z_zoom == 1.0) ? FDF_RED : FDF_WHITE, "[x1.0]");
	free(buff);
}

void	draw_z_accel_menu(t_fdf *fdf)
{
	double h;

	h = 1.5;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 75, WIN_H / h + 75, FDF_WHITE, "Z ACCEL +/-");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 100,
		(fdf->cam.z_accel == 0.05) ? FDF_RED : FDF_WHITE, "[0.05]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 7) + 5, WIN_H / h + 100,
		(fdf->cam.z_accel == 0.5) ? FDF_RED : FDF_WHITE, "[0.5]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 13) + 10, WIN_H / h + 100,
		(fdf->cam.z_accel == 1.0) ? FDF_RED : FDF_WHITE, "[1.0]");
}

void	draw_zoom_menu(t_fdf *fdf)
{
	double h;

	h = 1.25;
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + 75, WIN_H / h, FDF_WHITE, "ZOOM +/-");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H / h + 25,
		(fdf->cam.zoom_accel == 0.5) ? FDF_RED : FDF_WHITE, "[0.5]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 5), WIN_H / h + 25,
		(fdf->cam.zoom_accel == 1.0) ? FDF_RED : FDF_WHITE, "[1.0]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 10), WIN_H / h + 25,
		(fdf->cam.zoom_accel == 2.0) ? FDF_RED : FDF_WHITE, "[2.0]");
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30 + (12 * 15), WIN_H / h + 25,
		(fdf->cam.zoom_accel == 5.0) ? FDF_RED : FDF_WHITE, "[5.0]");
}
void	draw_after_img_menu(t_fdf *fdf)
{
	char *warning;
	int len;

	warning = "[ AFTER IMAGE MODE ENABLED ]";
	len = ft_strlen(warning);
	if (fdf->cam.after_img)
		mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 2 - (5 * len), 20, FDF_RED, warning);
	mlx_string_put(fdf->mlx, fdf->win,
		WIN_W / 30, WIN_H - 50,
		(fdf->cam.after_img) ? FDF_RED : FDF_WHITE, "AFTER IMAGE MODE");
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
}

void	draw_help_title(int fd, t_fdf *fdf)
{
	char *line;
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
	char *line;
	int y;

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
	char *line;
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
	char *line;
	int y;

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
	char *line;
	int y;
	int len;

	line = NULL;
	y = WIN_H / 1.6;
	while (y <= (WIN_H / 1.6 + (20 * 5)) && get_next_line(fd, &line) == 1)
	{
		len = ft_strlen(line);
		mlx_string_put(fdf->mlx, fdf->win, WIN_W / 1.9 - (5 * len), y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_description_brightness(int fd, t_fdf *fdf)
{
	char *line;
	int y;
	
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
	char *line;
	int y;

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
	char *line;
	int y;

	line = NULL;
	y = WIN_H / 1.4;
	while (y <= (WIN_H / 1.4 + (20 * 4)) && get_next_line(fd, &line) == 1)
	{
		mlx_string_put(fdf->mlx, fdf->win, WIN_W / 1.5, y, FDF_WHITE, line);
		free(line);
		y += 20;
	}
}

void	draw_help_menu(t_fdf *fdf)
{
	int fd;

	fd = open("help.txt", O_RDONLY);
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
	}
	close(fd);
	fdf->help = false;
	
}

int	draw(t_fdf *fdf, t_map *data)
{
	int x;
	int y;
	
	draw_bg(fdf);
	y = 0;
	while (y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			if (x != data->map_w - 1)
  			plot_line(fdf, get_point(gen_point(x, y, fdf), fdf),
  					get_point(gen_point(x+1, y, fdf), fdf));
			if (y != data->map_h - 1)
  			plot_line(fdf, get_point(gen_point(x, y, fdf), fdf),
  				get_point(gen_point(x, y+1, fdf), fdf));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_menu(fdf);
	return (0);
}	

void	print_map(int *coord, int size, int mod);
char	**ft_split(char *str);
void	get_coefficient(int *map, t_fdf *fdf);
int		*parse_1(int fd, t_fdf *fdf);


/*
** main shell function (prototype)
*/

void	shell_in(t_fdf *fdf)
{
	char *line;

	line = NULL;
	int fd = 0;
	while (1)
	{
		get_next_line(1, &line);
		fd = open(line, O_RDONLY);
		if (ft_strcmp(line, "quit") == 0)
		{
			free(line);
			break;
		}
		free(line);
		if (fd > 0)
		{
			free(fdf->data->map);
			fdf->data->map = parse_1(fd, fdf);
		}
		close(fd);
	}
	fdf->cam.zoom = -12.2123 * log(0.0000747893 * (fdf->data->map_size));
	if (fdf->cam.zoom <= 0.0)
		fdf->cam.zoom = 3.0;
	fdf->cam.depth_f = fdf->cam.zoom;
	get_coefficient(fdf->data->map, fdf);
}
int	key_control(int key, t_fdf *fdf)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_I || key == KEY_K)
	{
		fdf->cam.zoom += (key == KEY_I) ? 0.3 : -0.3;
		if (fdf->cam.zoom < 3.0)
			fdf->cam.zoom = 3.0;
	}
	else if (key == KEY_H)
		fdf->help = true;
	else if (key == KEY_L_ARROW)
		fdf->cam.x_offset -= 5;
	else if (key == KEY_R_ARROW)
		fdf->cam.x_offset += 5;
	else if (key == KEY_U_ARROW)
		fdf->cam.y_offset -= 5;
	else if (key == KEY_D_ARROW)
		fdf->cam.y_offset += 5;
	else if (key == KEY_S)
		shell_in(fdf);
	draw(fdf, fdf->data);
	if (fdf->help)
		draw_help_menu(fdf);
	return (0);
}

t_ramp *fdf_gen_color_ramp(t_fdf *fdf);
void	**fdf_index_color_ramp(t_ramp *ramp);
void	switch_fdf_theme(t_fdf *fdf, int theme)
{
	int i;

	i = 0;
	fdf->theme = theme;
	while (fdf->ramp[i])
		free(fdf->ramp[i++]);
	free(fdf->ramp);
	fdf->ramp_list = fdf_gen_color_ramp(fdf);
	fdf->ramp = fdf_index_color_ramp(fdf->ramp_list);
	fdf->ramp_size = count_ramp(fdf->ramp_list);
}
		
int		mouse_press(int button, int x, int y, t_fdf *fdf)
{
	fdf->mouse.x = x;
	fdf->mouse.y = y;
	if (button == MOUSE_LEFT_B)
	{
		fdf->mouse.left_b = true;
		if (x >= 50 && x <= 100 && y >= 50 && y <= 100)
			exit(0);
		else if (x >= 320 && x <= 420 && y >= 300 && y <= 350)
		{
			puts("View switched to: PARALLEL");
			fdf->cam.projection = PARALLEL;
			fdf->cam.alpha = 0.0;
			fdf->cam.beta = 0.0;
			fdf->cam.eta = 0.0;
		}
		else if (x >= 100 && x <= 150 && y >= 300 && y <= 350)
		{
			puts("View switched to: ISO");
			fdf->cam.projection = ISO;
			fdf->cam.alpha = 0.0;
			fdf->cam.beta = 0.0;
			fdf->cam.eta = 0.0;
		}
		else if (x >= 220 && x <= 300 && y >= 300 && y <= 350)
		{
			puts("View switched to: ELEVATION");
			fdf->cam.projection = ELEVATION;
			fdf->cam.alpha = -7.855;
			fdf->cam.beta = 0.0;
			fdf->cam.eta = 0.0;
		}
		else if (x >= 50 && x <= 150 && y >= 500 && y <= 540)
			switch_fdf_theme(fdf, DEFAULT);
		else if (x >= 50 && x <= 100 && y >= 550 && y <= 590)
			switch_fdf_theme(fdf, HOT);	
		else if (x >= 50 && x <= 100 && y >= 600 && y <= 640)
			switch_fdf_theme(fdf, COLD);
		else if (x >= 50 && x <= 100 && y >= 1000 && y <= 1050)
			fdf->cam.z_zoom = 0.05;
		else if (x >= 150 && x <= 200 && y >= 1000 && y <= 1050)
			fdf->cam.z_zoom = 0.5;
		else if (x >= 250 && x <= 350 && y >= 1000 && y <= 1050)
			fdf->cam.z_zoom = 1.0;
		else if (x >= 50 && x <= 100 && y >= 930 && y <= 980)
			fdf->cam.z_accel = 0.05;
		else if (x >= 150 && x <= 200 && y >= 930 && y <= 980)
			fdf->cam.z_accel = 0.5;
		else if (x >= 250 && x <= 350 && y >= 930 && y <= 980)
			fdf->cam.z_accel = 1.0;
		else if (x >= 110 && x <= 130 && y >= 840 && y <= 880)
			fdf->cam.brightness -= 5;
		else if (x >= 230 && x <= 250 && y >= 840 && y <= 880)
			fdf->cam.brightness += 5;
		else if (x >= 150 && x <= 170 && y >= 700 && y <= 800)
			fdf->cam.depth = true;
		else if (x >= 250 && x <= 300 && y >= 700 && y <= 800)
			fdf->cam.depth = false;
	}
	if (button == MOUSE_RIGHT_B)
		fdf->mouse.right_b = true;
	if (!fdf->mouse.right_b && button == MOUSE_SCROLL_UP)
		fdf->cam.z_zoom += fdf->cam.z_accel;
	if (!fdf->mouse.right_b && button == MOUSE_SCROLL_DOWN)
		fdf->cam.z_zoom -= fdf->cam.z_accel;
	if (fdf->mouse.right_b && button ==  MOUSE_SCROLL_UP)
		fdf->cam.zoom += fdf->cam.zoom_accel;
	if (fdf->mouse.right_b && button == MOUSE_SCROLL_DOWN)
		fdf->cam.zoom -= fdf->cam.zoom_accel;
	draw(fdf, fdf->data);
	if (fdf->help)
		draw_help_menu(fdf);
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

int		abort_fdf(void)
{
	if (errno == 0)
		ft_printf(FDF_ABORT_MESSAGE);
	else
		perror("Error:");
	exit(1);
	return (1);
}

t_map	*fdf_init_data_struct(void)
{
	t_map *data;

	(!(data = ft_memalloc(sizeof(t_map)))) && abort_fdf();
	data->map = NULL;
	data->map_w = 0;
	data->map_h = 0;

	return (data);
}



void	int_to_rgb(t_rgb *ret, int color)
{
	ret->r = color/(256 * 256);
	ret->g = (color / 256) % 256;
	ret->b = color % 256;
	ret->rgb = color;
}


t_ramp	*create_ramp_node(t_rgb rgb)
{
	t_ramp *ramp;
	
	ramp = ft_memalloc(sizeof(t_ramp));
	ramp->r = rgb.r;
	ramp->g = rgb.g;
	ramp->b = rgb.b;
	ramp->next = NULL;
	return (ramp);
}

void	append_ramp_node(t_ramp **ramp, t_rgb rgb)
{
	t_ramp *cursor;

	cursor = *ramp;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = create_ramp_node(rgb);
}

int	get_color_index(int z, int size)
{
	int idx_steps;
	int mid_idx;

	//using 1000 as arbitrary range
	idx_steps = 1000 / size;
	mid_idx = size/2;
	if (!idx_steps)
		idx_steps = 1;
	mid_idx += (z / idx_steps);
	if (mid_idx < 0)
		mid_idx = 0;
	if (mid_idx >= size)
		mid_idx = size - 1;
	return (mid_idx);
}

void	color_node(t_rgb start, int steps, t_rgb end, t_rgb *rgb)
{
	int diff;
	
	diff = abs(start.r - end.r) / (steps); 
	rgb->r += (start.r <= end.r) ? diff : -diff;
	diff = abs(start.g - end.g) / (steps); 
	rgb->g += (start.g <= end.g) ? diff : -diff;
	diff = abs(start.b - end.b) / (steps); 
	rgb->b += (start.b <= end.b) ? diff : -diff;
}

void	color_ramp(t_ramp **ramp, int c_start, int steps, int c_end)
{
	t_rgb	start;
	t_rgb	end;
	t_rgb	rgb;
	int		temp;

	temp = steps - 1;
	int_to_rgb(&start, c_start);
	int_to_rgb(&end, c_end);
	rgb.r = start.r;
	rgb.g = start.g;
	rgb.b = start.b;
	*ramp = (!*ramp) ? create_ramp_node(start) : *ramp;
	while (temp--)
	{
		color_node(start, steps, end, &rgb);
		append_ramp_node(ramp, rgb);
	}
	append_ramp_node(ramp, end);
}


/*
** Middle color is lemon chiffon
*/

void	fdf_theme_default(t_ramp **ramp)
{
	color_ramp(ramp, FDF_BLACK, 10, FDF_MIDNIGHT_BLUE);
	color_ramp(ramp, FDF_MIDNIGHT_BLUE, 10, FDF_MEDIUM_BLUE);
	color_ramp(ramp, FDF_MEDIUM_BLUE, 10, FDF_DEEP_SKY_BLUE);
	color_ramp(ramp, FDF_DEEP_SKY_BLUE, 10, FDF_LIGHT_BLUE); 
	color_ramp(ramp, FDF_LIGHT_BLUE, 10, FDF_AZURE); 
//	color_ramp(ramp, FDF_AZURE, 10, FDF_POWDER_BLUE); 
//	color_ramp(ramp, FDF_POWDER_BLUE, 10, FDF_YELLOW_GREEN);
	color_ramp(ramp, FDF_AZURE, 10, FDF_MOCCASIN); 
	color_ramp(ramp, FDF_MOCCASIN, 10, FDF_YELLOW_GREEN);
	color_ramp(ramp, FDF_YELLOW_GREEN, 10, FDF_FOREST_GREEN);
	color_ramp(ramp, FDF_FOREST_GREEN, 10, FDF_MAROON);
	color_ramp(ramp, FDF_MAROON, 10, FDF_SIENNA);
	color_ramp(ramp, FDF_SIENNA, 10, FDF_SNOW);
	color_ramp(ramp, FDF_SNOW, 10, FDF_BLACK);
}

/*
** Middle color is wheat
*/

void	fdf_theme_hot(t_ramp **ramp)
{
	color_ramp(ramp, FDF_DARK_RED, 10, FDF_CRIMSON);
	color_ramp(ramp, FDF_CRIMSON, 10, FDF_CORAL);
	color_ramp(ramp, FDF_CORAL, 10, FDF_LIGHT_SALMON);
	color_ramp(ramp, FDF_CORAL, 10, FDF_ORANGE);
	color_ramp(ramp, FDF_ORANGE, 10, FDF_GOLD);
	color_ramp(ramp, FDF_GOLD, 10, FDF_WHEAT);
	color_ramp(ramp, FDF_WHEAT, 10, FDF_LEMON_CHIFFON);
	color_ramp(ramp, FDF_LEMON_CHIFFON, 10, FDF_LIGHT_PINK);
	color_ramp(ramp, FDF_LIGHT_PINK, 10, FDF_PINK);
	color_ramp(ramp, FDF_PINK, 10, FDF_HOT_PINK);
	color_ramp(ramp, FDF_HOT_PINK, 10, FDF_DEEP_PINK);
	color_ramp(ramp, FDF_DEEP_PINK, 10, FDF_MEDIUM_VIOLET_RED);
}

void	fdf_theme_cold(t_ramp **ramp)
{
	color_ramp(ramp, FDF_BLACK, 10, FDF_DARK_SLATE_GRAY);
	color_ramp(ramp, FDF_DARK_SLATE_GRAY, 10, FDF_SLATE_GRAY);
	color_ramp(ramp, FDF_SLATE_GRAY, 10, FDF_LIGHT_STEEL_BLUE);
	color_ramp(ramp, FDF_LIGHT_STEEL_BLUE, 10, FDF_LIGHT_SKY_BLUE);
	color_ramp(ramp, FDF_LIGHT_SKY_BLUE, 10, FDF_LIGHT_BLUE);
	color_ramp(ramp, FDF_LIGHT_BLUE, 10, FDF_AZURE);
	color_ramp(ramp, FDF_AZURE, 10, FDF_HONEYDEW);
	color_ramp(ramp, FDF_HONEYDEW, 10, FDF_PALE_GREEN);
	color_ramp(ramp, FDF_PALE_GREEN, 10, FDF_LAWN_GREEN);
	color_ramp(ramp, FDF_LAWN_GREEN, 10, FDF_LIME_GREEN);
	color_ramp(ramp, FDF_LIME_GREEN, 10, FDF_OLIVE_DRAB);
	color_ramp(ramp, FDF_OLIVE_DRAB, 10, FDF_DARK_OLIVE_GREEN);
}

void	fdf_theme_custom(t_ramp **ramp)
{
	color_ramp(ramp, FDF_BLACK, 121, FDF_WHITE);
}

t_ramp *fdf_gen_color_ramp(t_fdf *fdf)
{
	t_ramp *ramp;

	ramp = NULL;
	if (fdf->theme == DEFAULT)
		fdf_theme_default(&ramp);
	else if (fdf->theme == HOT)
		fdf_theme_hot(&ramp);
	else if (fdf->theme == COLD)
		fdf_theme_cold(&ramp);
	else if (fdf->theme == CUSTOM)
		fdf_theme_custom(&ramp);
	return (ramp);
}

void	print_ramp(t_ramp *ramp)
{
	int i = 0;

	while(ramp)
	{
		printf("i: %d r: %d g: %d b: %d\n", i++, ramp->r, ramp->g, ramp->b);
		ramp=ramp->next;
	}
}

int		count_ramp(t_ramp *ramp)
{
	int c;

	c = 0;
	if (!ramp)
		return (0);
	while (ramp)
	{
		c++;
		ramp = ramp->next;
	}
	return (c);
}

void	**fdf_index_color_ramp(t_ramp *ramp)
{
	void	**map;
	int		size;
	int		i;

	i = 0;
	size = count_ramp(ramp);
	(!(map = ft_memalloc(sizeof(t_ramp) * size))) && abort_fdf();
	while(ramp)
	{
		map[i++] = ramp;
		ramp = ramp->next;
	}
	map[i] = NULL;
	return (map);
}

void	free_color_ramp(t_ramp *ramp)
{
	t_ramp *temp;

	temp = ramp;
	while (ramp)
	{
		temp = ramp->next;
		free(ramp);
		ramp = temp;
	}
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

t_mouse mouse_init(void)
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
	frame->theme = CUSTOM;
	frame->ramp_list = fdf_gen_color_ramp(frame);
	frame->ramp = fdf_index_color_ramp(frame->ramp_list);
	frame->ramp_size = count_ramp(frame->ramp_list);
	frame->mouse = mouse_init();
	frame->help = false;
	return (frame);
}

void	switch_camera_settings(t_fdf *fdf)
{
	fdf->cam.projection = PARALLEL;
	fdf->cam.zoom = 100;
	fdf->cam.z_zoom = 2;
	fdf->cam.alpha = 1.0;
	fdf->cam.beta = 1.0;
	fdf->cam.eta = 1.0;
}

void	print_camera_settings(t_fdf *fdf)
{

	printf("CAMERA'S SETTINGS:\n");
	printf("ZOOM: %.1f\n", fdf->cam.zoom);
	printf("Z_ZOOM: %.1f\n", fdf->cam.z_zoom);
	printf("ALPHA: %.1f\n", fdf->cam.alpha);
	printf("BETA: %.1f\n", fdf->cam.beta);
	printf("ETA: %.1f\n", fdf->cam.eta);
	switch (fdf->cam.projection) {
		case (ISO):
			printf("PROJECTION: ISO\n"); break;
		case (PARALLEL):
			printf("PROJECTION: PARALLEL\n"); break;
		default: printf("PROJECTION: DEFAULT\n"); break;
	}
}

void gradient_test(t_fdf *fdf)
{
	t_pt p0;
	t_pt p1;
	int gaps = 50;
	int length = 300;
	
	p0.x = 50;
	p0.y = 50;
	p1.x = p0.x + length;
	p1.y = 50;
	// Default theme
	int_to_rgb(&p0.rgb, FDF_BLACK);
	int_to_rgb(&p1.rgb, FDF_MIDNIGHT_BLUE);
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_MIDNIGHT_BLUE);
	int_to_rgb(&p1.rgb, FDF_MEDIUM_BLUE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_MEDIUM_BLUE);
	int_to_rgb(&p1.rgb, FDF_DEEP_SKY_BLUE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_DEEP_SKY_BLUE);
	int_to_rgb(&p1.rgb, FDF_LIGHT_BLUE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LIGHT_BLUE);
	int_to_rgb(&p1.rgb, FDF_AZURE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_AZURE);
	int_to_rgb(&p1.rgb, FDF_LEMON_CHIFFON);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LEMON_CHIFFON);
	int_to_rgb(&p1.rgb, FDF_YELLOW_GREEN);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_YELLOW_GREEN);
	int_to_rgb(&p1.rgb, FDF_FOREST_GREEN);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_FOREST_GREEN);
	int_to_rgb(&p1.rgb, FDF_MAROON);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_MAROON);
	int_to_rgb(&p1.rgb, FDF_SIENNA);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_SIENNA);
	int_to_rgb(&p1.rgb, FDF_SNOW);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_SNOW);
	int_to_rgb(&p1.rgb, FDF_BLACK);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	
	// Single linear
	p0.y = 700, p1.y = 700;
	p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_BLACK);
	int_to_rgb(&p1.rgb, FDF_MIDNIGHT_BLUE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_MIDNIGHT_BLUE);
	int_to_rgb(&p1.rgb, FDF_MEDIUM_BLUE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_MEDIUM_BLUE);
	int_to_rgb(&p1.rgb, FDF_DEEP_SKY_BLUE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_DEEP_SKY_BLUE);
	int_to_rgb(&p1.rgb, FDF_LIGHT_BLUE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LIGHT_BLUE);
	int_to_rgb(&p1.rgb, FDF_AZURE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_AZURE);
	int_to_rgb(&p1.rgb, FDF_LEMON_CHIFFON);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LEMON_CHIFFON);
	int_to_rgb(&p1.rgb, FDF_YELLOW_GREEN);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_YELLOW_GREEN);
	int_to_rgb(&p1.rgb, FDF_FOREST_GREEN);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_FOREST_GREEN);
	int_to_rgb(&p1.rgb, FDF_MAROON);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_MAROON);
	int_to_rgb(&p1.rgb, FDF_SIENNA);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_SIENNA);
	int_to_rgb(&p1.rgb, FDF_SNOW);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_SNOW);
	int_to_rgb(&p1.rgb, FDF_BLACK);
	plot_line(fdf, p0, p1);


	// Hot Theme
	p0.x = 800;
	p0.y = 50;
	p1.x = p0.x + length;
	p1.y = 50;
	int_to_rgb(&p0.rgb, FDF_DARK_RED);
	int_to_rgb(&p1.rgb, FDF_CRIMSON);
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_CRIMSON);
	int_to_rgb(&p1.rgb, FDF_CORAL);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_CORAL);
	int_to_rgb(&p1.rgb, FDF_LIGHT_SALMON);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);	
	int_to_rgb(&p0.rgb, FDF_LIGHT_SALMON);
	int_to_rgb(&p1.rgb, FDF_ORANGE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);	
	int_to_rgb(&p0.rgb, FDF_ORANGE);
	int_to_rgb(&p1.rgb, FDF_GOLD);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_GOLD);
	int_to_rgb(&p1.rgb, FDF_WHEAT);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_WHEAT);
	int_to_rgb(&p1.rgb, FDF_LEMON_CHIFFON);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LEMON_CHIFFON);
	int_to_rgb(&p1.rgb, FDF_LIGHT_PINK);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LIGHT_PINK);
	int_to_rgb(&p1.rgb, FDF_PINK);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_PINK);
	int_to_rgb(&p1.rgb, FDF_HOT_PINK);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_HOT_PINK);
	int_to_rgb(&p1.rgb, FDF_DEEP_PINK);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_DEEP_PINK);
	int_to_rgb(&p1.rgb, FDF_MEDIUM_VIOLET_RED);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);

	// Single linear	
	p0.y = 800, p1.y = 800;
	p0.x = 50;
	p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_DARK_RED);
	int_to_rgb(&p1.rgb, FDF_CRIMSON);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_CRIMSON);
	int_to_rgb(&p1.rgb, FDF_CORAL);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_CORAL);
	int_to_rgb(&p1.rgb, FDF_LIGHT_SALMON);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LIGHT_SALMON);
	int_to_rgb(&p1.rgb, FDF_ORANGE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_ORANGE);
	int_to_rgb(&p1.rgb, FDF_GOLD);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_GOLD);
	int_to_rgb(&p1.rgb, FDF_WHEAT);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_WHEAT);
	int_to_rgb(&p1.rgb, FDF_LEMON_CHIFFON);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LEMON_CHIFFON);
	int_to_rgb(&p1.rgb, FDF_LIGHT_PINK);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LIGHT_PINK);
	int_to_rgb(&p1.rgb, FDF_PINK);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_PINK);
	int_to_rgb(&p1.rgb, FDF_HOT_PINK);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_HOT_PINK);
	int_to_rgb(&p1.rgb, FDF_DEEP_PINK);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_DEEP_PINK);
	int_to_rgb(&p1.rgb, FDF_MEDIUM_VIOLET_RED);
	plot_line(fdf, p0, p1);

	// Cold theme
	p0.x = 1550;
	p0.y = 50;
	p1.x = p0.x + length;
	p1.y = 50;	
	int_to_rgb(&p0.rgb, FDF_BLACK);
	int_to_rgb(&p1.rgb, FDF_DARK_SLATE_GRAY);
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_DARK_SLATE_GRAY);
	int_to_rgb(&p1.rgb, FDF_SLATE_GRAY);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_SLATE_GRAY);
	int_to_rgb(&p1.rgb, FDF_LIGHT_STEEL_BLUE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LIGHT_STEEL_BLUE);
	int_to_rgb(&p1.rgb, FDF_LIGHT_SKY_BLUE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LIGHT_SKY_BLUE);
	int_to_rgb(&p1.rgb, FDF_LIGHT_BLUE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LIGHT_BLUE);
	int_to_rgb(&p1.rgb, FDF_AZURE);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_AZURE);
	int_to_rgb(&p1.rgb, FDF_HONEYDEW);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_HONEYDEW);
	int_to_rgb(&p1.rgb, FDF_PALE_GREEN);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_PALE_GREEN);
	int_to_rgb(&p1.rgb, FDF_LAWN_GREEN);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LAWN_GREEN);
	int_to_rgb(&p1.rgb, FDF_LIME_GREEN);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_LIME_GREEN);
	int_to_rgb(&p1.rgb, FDF_OLIVE_DRAB);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);
	int_to_rgb(&p0.rgb, FDF_OLIVE_DRAB);
	int_to_rgb(&p1.rgb, FDF_DARK_OLIVE_GREEN);
	p0.y += gaps, p1.y += gaps;
	plot_line(fdf, p0, p1);

	// Single Linear
	p0.y = 900, p1.y = 900;
	p0.x = 50;
	p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_BLACK);
	int_to_rgb(&p1.rgb, FDF_DARK_SLATE_GRAY);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_DARK_SLATE_GRAY);
	int_to_rgb(&p1.rgb, FDF_SLATE_GRAY);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_SLATE_GRAY);
	int_to_rgb(&p1.rgb, FDF_LIGHT_STEEL_BLUE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LIGHT_STEEL_BLUE);
	int_to_rgb(&p1.rgb, FDF_LIGHT_SKY_BLUE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LIGHT_SKY_BLUE);
	int_to_rgb(&p1.rgb, FDF_LIGHT_BLUE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LIGHT_BLUE);
	int_to_rgb(&p1.rgb, FDF_AZURE);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_AZURE);
	int_to_rgb(&p1.rgb, FDF_HONEYDEW);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_HONEYDEW);
	int_to_rgb(&p1.rgb, FDF_PALE_GREEN);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_PALE_GREEN);
	int_to_rgb(&p1.rgb, FDF_LAWN_GREEN);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LAWN_GREEN);
	int_to_rgb(&p1.rgb, FDF_LIME_GREEN);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_LIME_GREEN);
	int_to_rgb(&p1.rgb, FDF_OLIVE_DRAB);
	plot_line(fdf, p0, p1);
	p0.x = p1.x, p1.x = p0.x + length / 2;
	int_to_rgb(&p0.rgb, FDF_OLIVE_DRAB);
	int_to_rgb(&p1.rgb, FDF_DARK_OLIVE_GREEN);
	plot_line(fdf, p0, p1);
};

void	print_arr(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++)
	{
		printf("%s ", arr[i]);
		free(arr[i]);
	}
	free(arr);
	printf("total: %d", i);
	puts("");
}

int	count_arr_width(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	check_map_width(t_read *read)
{
	int w;
	int prev_w;

	w = 0;
	prev_w = w;
	while (read)
	{
		w = count_arr_width(read->arr);
		if (!w || (prev_w && w != prev_w))
			return (0);
		prev_w = w;
		read = read->next;
	}
	return (w);
}

int	check_map_height (t_read *read)
{
	int map_h;

	map_h = 0;
	while (read)
	{
		map_h++;
		read = read->next;
	}
	return (map_h);
}

int		get_map_size(t_read *read, t_fdf *fdf)
{
	int map_w;
	int map_h;

	map_h = check_map_height(read);
	map_w = check_map_width(read);
	if (!map_h || !map_w)
		abort_fdf();
	fdf->data->map_w = map_w;
	fdf->data->map_h = map_h;
	fdf->data->map_size = map_w * map_h;
	return (fdf->data->map_size);
}

int		*map_coord(t_read *read, t_fdf *fdf)
{
	int *map;
	int i;
	int j;

	i = 0;
	map = malloc(sizeof(int) * get_map_size(read, fdf));
	while (read)
	{
		j = 0;
		while (read->arr[j])
		{
			map[i++] = ft_atoi(read->arr[j++]);
			free(read->arr[j - 1]);
		}
		free(read->arr);
		free(read);
		read = read->next;
	}
	return (map);
}
		
void	print_link_arr(t_read *read)
{
	t_read *temp;

	while (read)
	{
		temp = read;
		print_arr(read->arr);
		read = read->next;
		free(temp);
	}
}
void create_arr_node(t_read **head, char **block)
{
	*head = malloc(sizeof(t_read));
	(*head)->arr = block;
	(*head)->next = NULL;
}

void link_arr_node(t_read **head, char **block)
{
	t_read *cursor;

	if (!*head)
		create_arr_node(head, block);
	else
	{
		cursor = *head;
		while (cursor->next)
			cursor = cursor->next;
		create_arr_node(&(cursor->next), block);
	}
}
		
int  *parse_1(int fd, t_fdf *fdf)
{
	char *line;
	char **arr;
	int	 *map;
	t_read *read;

	line = NULL;
	arr = NULL;
	read = NULL;
	map = NULL;

	while (get_next_line(fd, &line) == 1)
	{
		arr = ft_strsplit(line, ' ');
		link_arr_node(&read, arr);
		free(line);
	}
	if (read)
		map = map_coord(read, fdf);	
	else
		abort_fdf();
	return (map);
}

int		get_z_range(int *map, int size)
{
	int i;
	int max;
	int min;
	int range;

	i = 0;
	max = map[i];
	min = map[i];
	while (i++ < size - 1)
	{
		if (map[i] > max)
			max = map[i];
		if (map[i] < min)
			min = map[i];
	}
	printf("i: %d\n", i);
	range = max - min;
	return (range);
}

void	extract_min_max(int *map, int *min, int *max, int size)
{
	int i;

	i = 0;
	*max = map[i];
	*min = map[i];
	while (i++ < size - 1)
	{
		if (map[i] > *max)
			*max = map[i];
		if (map[i] < *min)
			*min = map[i];
	}
}

void	get_coefficient(int *map, t_fdf *fdf)
{
	int		max;
	int		min;
	
	extract_min_max(map, &min, &max, fdf->data->map_size);
	fdf->coef_m = (0.0 - 1.0) / (min - max);
	fdf->coef_b = 1.0 - (fdf->coef_m * max);
	fdf->min = min;
	fdf->max = max;
}
	
	
int main(int argc, char *argv[])
{
	t_fdf *fdf;
	fdf = fdf_init();
	char *path;
	path = argv[argc-1];
	
	if (argc == 2)
	{
		int fd;
		fd = open(argv[1], O_RDONLY);
		printf("fd: %d\n", fd);
		if (fd < 0)
		{
			perror("Error");
			return (-1);
		}
		fdf->data->map = parse_1(fd, fdf);
		close(fd);
	}
	fdf->cam.zoom = -12.2123 * log(0.0000747893 * (fdf->data->map_size));
	if (fdf->cam.zoom <= 0.0)
		fdf->cam.zoom = 3.0;
	fdf->cam.depth_f = fdf->cam.zoom;
	get_coefficient(fdf->data->map, fdf);
	draw(fdf, fdf->data);
	
//	gradient_test(fdf);
//	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0 , 0);
	draw_menu(fdf);
	mlx_hook(fdf->win, 2, 0, key_control, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win, 5, 0,mouse_release, fdf);
	mlx_hook(fdf->win, 6, 0,mouse_move, fdf);
	if (fdf->help)
		draw_help_menu(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

