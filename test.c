/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 18:00:37 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/06 20:02:49 by phtruong         ###   ########.fr       */
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
** Organize the plot function.
** Create a struct to store plotting points ✓
** Reduce parameters in plot function
** Create a parser
** Create an init function
** If you're gonna do it, do it right.
*/
void	plot_pixel(t_fdf *f, double x, double y, int rgb)
{
	mlx_pixel_put(f->mlx, f->win, x, y, rgb);
}
int		fdf_rgb(t_fdf fdf, double c)
{
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

void	plot_line(t_fdf *fdf, t_pt p0, t_pt p1)
{
	bool steep = fabs(p1.y - p0.y) > fabs(p1.x - p0.x);
	if (steep)
	{
		ft_swap_double(&p0.x, &p0.y);
		ft_swap_double(&p1.x, &p1.y);
	}
	if (p0.x > p1.x)
	{
		ft_swap_double(&p0.x, &p1.x);
		ft_swap_double(&p0.y, &p1.y);
	}
	double dx = p1.x - p0.x;
	double dy = p1.y - p0.y;
	double gradient;
	if (dx == 0.0)
		gradient = 1.0;
	else
		gradient = dy / dx;

	// Handle first end point
	
	double xend = round(p0.x);
	double yend = p0.y + gradient * (xend - p0.x);
	double xgap = rfpart(p0.x + 0.5);
	double xpxl1 = xend;
	double ypxl1 = ipart(yend);
	if (steep)
	{
		plot_pixel(fdf, ypxl1, xpxl1, fdf_rgb(*fdf, rfpart(yend) * xgap));
		plot_pixel(fdf, ypxl1 + 1, xpxl1, fdf_rgb(*fdf, fpart(yend) * xgap));	
	}
	else
	{
		plot_pixel(fdf, xpxl1, ypxl1, fdf_rgb(*fdf, rfpart(yend) * xgap));
		plot_pixel(fdf, xpxl1, ypxl1 + 1, fdf_rgb(*fdf, fpart(yend) *xgap));
	}

	//Handle second end point
	
	double intery = yend + gradient; // first y-intersection for the main loop
	xend = round(p1.x);
	yend = p1.y + gradient * (xend - p1.x);
	xgap = fpart(p1.x + 0.5);
	double xpxl2 = xend;
	double ypxl2 = ipart(yend);

	if (steep)
	{
		plot_pixel(fdf, ypxl2, xpxl2, fdf_rgb(*fdf, rfpart(yend) *xgap));
		plot_pixel(fdf, ypxl2 + 1, xpxl2, fdf_rgb(*fdf, fpart(yend) * xgap));
	}
	else
	{
		plot_pixel(fdf, xpxl2, ypxl2, fdf_rgb(*fdf, rfpart(yend) * xgap));
		plot_pixel(fdf, xpxl2, ypxl2 + 1, fdf_rgb(*fdf, fpart(yend) * xgap));
	}

	double x;
	x = 0.0;
	if (steep)
	{
		x = xpxl1;
		while (x++ < xpxl2)
		{
			plot_pixel(fdf, ipart(intery), x, fdf_rgb(*fdf, rfpart(intery)));
			plot_pixel(fdf, ipart(intery) + 1, x, fdf_rgb(*fdf, fpart(intery)));
			intery += gradient;
		}
	}
	else
	{
		x = xpxl1;
		while (x++ < xpxl2)
		{
			plot_pixel(fdf, x, ipart(intery), fdf_rgb(*fdf, rfpart(intery)));
			plot_pixel(fdf, x, ipart(intery) + 1, fdf_rgb(*fdf, fpart(intery)));
			intery += gradient;
		}
	}
}

void	fdf_color(t_fdf **fdf)
{
	(*fdf)->color.r = 255;
	(*fdf)->color.g = 0;
	(*fdf)->color.b = 120;
//	(*fdf)->color.r *= (*fdf)->color.c;
//	(*fdf)->color.g *= (*fdf)->color.c;
//	(*fdf)->color.b *= (*fdf)->color.c;
//	(*fdf)->color.rgb = (*fdf)->color.r;
//	(*fdf)->color.rgb = ((*fdf)->color.rgb << 8) + (*fdf)->color.g;
//	(*fdf)->color.rgb = ((*fdf)->color.rgb << 8) + (*fdf)->color.b;
}

void	fdf_rot_x(double *y , double *z, double alpha)
{
	double prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

void	fdf_rot_y(double *x, double *z, double beta)
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
	p.z *= fdf->cam.z_zoom;
	fdf_rot_x(&p.y, &p.z, fdf->cam.alpha);
	fdf_rot_y(&p.x, &p.z, fdf->cam.beta);
	fdf_rot_z(&p.x, &p.y, fdf->cam.eta);
	if (projection == ISO)
		fdf_iso(&p.x, &p.y, p.z);
	p.x += (WIN_W / 2);
	p.y += (WIN_H / 2);
	return (p);
}

t_pt	gen_point(double x, double y, int *coord, int width)
{
	t_pt p;
	int idx;

	idx = y * width + x;
	p.x = x;
	p.y = y;
	p.z = coord[idx];
	return (p);
}

void	draw(t_fdf *fdf, int *map)
{
	int x;
	int y = 0;
	int width = fdf->map_w;
	int height = fdf->map_h; 
	mlx_clear_window(fdf->mlx, fdf->win);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (x != width - 1)
  			plot_line(fdf, get_point(gen_point(x, y, map, width), fdf),
  					get_point(gen_point(x + 1, y, map, width), fdf));
			if (y != height - 1)
  			plot_line(fdf, get_point(gen_point(x, y, map, width), fdf),
  				get_point(gen_point(x, y + 1, map, width), fdf));
			x++;
		}
		y++;
	}
}	

void	print_map(int *coord, int size, int mod);
char	**ft_split(char *str);
int	key_control(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	if (key == KEY_ESC)
		exit(0);
/*	else if (key == KEY_I || key == KEY_K)
	{
		fdf->cam.zoom += (key == KEY_I) ? 1 : -1;
		if (fdf->cam.zoom < 10)
			fdf->cam.zoom = 10;
	}
	else if (key == KEY_PLUS || key == KEY_MINUS)
		fdf->cam.z_zoom += (key == KEY_PLUS) ? 0.1 : -0.1;
	else if (key == KEY_L_SQ_BRKT)
	{
		fdf->cam.beta = 0;
		fdf->cam.alpha = 0;
		fdf->cam.eta = 0;
		projection = ISO;
	}
	else if (key == KEY_R_SQ_BRKT)
	{
		fdf->cam.beta = 0;
		fdf->cam.alpha = 0;
		fdf->cam.eta = 0;
		projection = PARALLEL;
	}
	else if (key == KEY_L_ARROW)
		fdf->cam.beta += 0.05;
	else if (key == KEY_R_ARROW)
		fdf->cam.beta -= 0.05;
	else if (key == KEY_U_ARROW)
		fdf->cam.alpha += 0.05;
	else if (key == KEY_D_ARROW)
		fdf->cam.alpha -= 0.05;
	else if (key == KEY_NUM_7)
		fdf->cam.eta += 0.05;
	else if (key == KEY_NUM_9)
		fdf->cam.eta -= 0.05;*/
	draw(fdf, fdf->map);
	return (0);
}

int		fdf_read(const char *path)
{
	int ret;

	ret = open(path, O_RDONLY);
	if (ret < 0)
	{
		ft_printf("%s\n", strerror(errno));
		exit(1);
	}
	printf("ret: %d\n", ret);
	return (ret);
}

int		is_space(char c) {
	return ((c >= 9 && c <= 13) || (c == ' '));
}

int		count_words(char *s) {
	int wd = 0;
	if (!s)
		return (0);
	while (*s) {
		while (is_space(*s)) s++;
		if (*s && !is_space(*s)) wd++;
		while (*s && !is_space(*s)) s++;
		if (!*s)
			break;
		s++;
	}
	return (wd);
}

char **ft_split(char *str) {
	int count = count_words(str);
	char **arr = (char **)malloc(sizeof(char *)* count + 1);
	if (!arr)
		return (NULL);
	arr[count] = NULL;
	for (int i = 0; i < count; i++) {
		while (is_space(*str)) str++;
		char *pstr = str;
		while (*str && !is_space(*str)) str++;
		int len = (int)(str - pstr);
		arr[i] = (char *)malloc(sizeof(char)*len + 1);
		if (!arr[i])
			return (NULL);
		for (int j = 0; j < len; j++)
			arr[i][j] = *pstr++;
		arr[i][len] = '\0';
	}
	return (arr);
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

t_fdf	*init_fdf(void)
{
	t_fdf *frame;

	frame = NULL;
	(!(frame = malloc(sizeof(t_fdf)))) && abort_fdf();
	(!(frame->mlx = mlx_init())) && abort_fdf();
	(!(frame->win = mlx_new_window(frame->mlx, WIN_W, WIN_H, "42 FDF"))) &&
	   abort_fdf();
	(!(frame->img = mlx_new_image(frame->mlx, WIN_W, WIN_H))) && abort_fdf();
	(!(frame->data_addr =
				mlx_get_data_addr(frame->img, &(frame->bits_per_pix),
				&(frame->size_line), &(frame->endian)))) && abort_fdf();
	return (frame);
}

	
int main(int argc, char *argv[])
{
//	print_map(map_data->map, 209);
	int i = 0;
	i = 0;
	
/*	int coord[] = 
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0,10,10, 0, 0,10,10, 0, 0, 0,10,10,10,10,10, 5, 0, 0,
		0, 0,10,10, 0, 0,10,10, 0, 0, 0,10,10,10,10,10,10, 0, 0,
		0, 0,10,10, 0, 0,10,10, 0, 0, 0, 0, 0, 0, 0,10,10, 0, 0,
		0, 0,10,10,10,10,10,10, 0, 0, 0, 5,10,10,10,10,10, 0, 0,
		0, 0, 0,10,10,10,10,10, 0, 0, 0,10,10, 0, 0, 0, 0, 0, 45,
		0, 0, 0, 0, 0, 0,10,10, 0, 0, 0,10,10, 5, 5, 5,10, 0, 60,
		0, 0, 0, 0, 0, 0,10,10, 0, 0, 0,10,10,10,10,10,10, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
*/
	t_fdf *fdf;
	fdf = init_fdf();
	char *path;
	path = argv[argc-1];
	path = NULL;
//	fdf->data = malloc(sizeof(t_map));
//	t_map *data;
	
//	data = fdf_map(r);
//	fdf->data = fdf_map(r);
//	fdf_color(&fdf);
//	int *map;
//	map = dup_coord(fdf->data->map, fdf_total(r));
//	print_map(map, fdf_total(r), fdf->data->width);
//	draw(fdf, coord);
//	mlx_hook(fdf->win, 2, 0, key_control, fdf);
	mlx_loop(fdf->mlx);
//	//fdf->test = coord;
	return (0);
}

