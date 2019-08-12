/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 18:00:37 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/12 15:29:19 by phtruong         ###   ########.fr       */
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
** Create a color ramp ✓
** Create theme for color ramp
** Clean up color ramp function
** If you're gonna do it, do it right.
*/
void	plot_pixel(t_fdf *frame, int x, int y, int rgb)
{
	int i;

	printf("(%d, %d) @ rgb: %d\n", x, y, rgb);
	if (x < WIN_W && y >= 0 && y < WIN_H)
	{
	i = (x * frame->bits_per_pix / 8) + (y  * frame->size_line);
//	printf("i: %d rgb: %d\n", i, rgb);
	frame->data_addr[i++] = rgb;
	frame->data_addr[i++] = rgb >> 8;
	frame->data_addr[i] = rgb >> 16;
	}
}
int		fdf_rgb(t_fdf fdf, double c)
{
	printf("c value: %f\n", c);
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
//	printf("color before cal: %d\n", fdf->color.rgb);
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
		plot_pixel(fdf, ypxl1 + 1, xpxl1,fdf_rgb(*fdf, fpart(yend) * xgap));	
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
//	printf("color before main: %d\n", fdf->color.rgb);
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
	(*fdf)->color.g = 255;
	(*fdf)->color.b = 255;
//	(*fdf)->color.r *= (*fdf)->color.c;
//	(*fdf)->color.g *= (*fdf)->color.c;
//	(*fdf)->color.b *= (*fdf)->color.c;
	(*fdf)->color.rgb = (*fdf)->color.r;
	(*fdf)->color.rgb = ((*fdf)->color.rgb << 8) + (*fdf)->color.g;
	(*fdf)->color.rgb = ((*fdf)->color.rgb << 8) + (*fdf)->color.b;
//	printf("color set at: %d\n", (*fdf)->color.rgb);
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
	p.z *= fdf->cam.z_zoom;
	fdf_rot_x(&p.y, &p.z, fdf->cam.alpha);
	fdf_rot_y(&p.x, &p.z, fdf->cam.beta);
	fdf_rot_z(&p.x, &p.y, fdf->cam.eta);
	if (fdf->cam.projection == ISO)
		fdf_iso(&p.x, &p.y, p.z);
	p.x += (WIN_W / 2);
	p.y += (WIN_H / 2);
	printf("(%f, %f)\n", p.x, p.y);
	return (p);
}

t_pt	gen_point(double x, double y, t_map *data)
{
	t_pt p;
	int idx;

	idx = y * data->map_w + x;
	p.x = x;
	p.y = y;
	p.z = data->map[idx];
	return (p);
}

void	clear_bg(t_fdf *fdf)
{
	ft_bzero(fdf->data_addr, WIN_W * WIN_H * (fdf->bits_per_pix /8));
}
void	draw(t_fdf *fdf, t_map *data)
{
	int x;
	int y;
	
	ft_bzero(fdf->data_addr, WIN_W * WIN_H * (fdf->bits_per_pix /8));
	y = 0;
	while (y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			if (x != data->map_w - 1)
  			plot_line(fdf, get_point(gen_point(x, y, data), fdf),
  					get_point(gen_point(x + 1, y, data), fdf));
			if (y != data->map_h - 1)
  			plot_line(fdf, get_point(gen_point(x, y, data), fdf),
  				get_point(gen_point(x, y + 1, data), fdf));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
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
	draw(fdf, fdf->data);
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
	mid_idx += (z / idx_steps);
	if (mid_idx < 0)
		mid_idx = 0;
	else if (mid_idx > size)
		mid_idx = size;
	printf("idx: %d\n", mid_idx);
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
//	printf("start r: %d g: %d b: %d\n", start.r, start.g, start.b);
//	printf("end r: %d g: %d b: %d\n", end.r, end.g, end.b);
	while (temp--)
	{
		color_node(start, steps, end, &rgb);
//		printf("r: %d g: %d b: %d\n", rgb.r, rgb.g, rgb.b);
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
	color_ramp(ramp, FDF_AZURE, 10, FDF_LEMON_CHIFFON); 
	color_ramp(ramp, FDF_LEMON_CHIFFON, 10, FDF_YELLOW_GREEN);
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
	color_ramp(ramp, FDF_CRIMSON, 10, FDF_LIGHT_SALMON);
	color_ramp(ramp, FDF_LIGHT_SALMON, 10, FDF_CORAL);
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
	color_ramp(ramp, FDF_BLACK, 200, FDF_WHITE);
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
	cam.z_zoom = 1.0;
	cam.alpha = 0.0;
	cam.beta = 0.0;
	cam.eta = 0.0;
	cam.projection = PARALLEL;
	return (cam);
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
	return (frame);
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
int main(int argc, char *argv[])
{
//	print_map(map_data->map, 209);
	int i = 0;
	i = 0;
	
	int coord[] = 
	{
		0, 0,-5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0,10,10, 0, 0,10,10, 0, 0, 0,10,10,10,10,10, 5, 0, 0,
		0, 0,10,10, 0, 0,10,10, 0, 0, 0,10,10,10,10,10,10, 0, 0,
		0, 0,10,10, 0, 0,10,10, 0, 0, 0, 0, 0, 0, 0,10,10, 0, 0,
		0, 0,10,10,10,10,10,10, 0, 0, 0, 5,10,10,10,10,10, 0, 0,
		0, 0, 0,10,10,10,10,10, 0, 0, 0,10,10, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,10,10, 0, 0, 0,10,10, 5, 5, 5,10, 0, 0,
		0, 0, 0, 0, 0, 0,10,10, 0, 0, 0,10,10,10,10,10,10, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	int size;
	size = sizeof(coord)/sizeof(int);
	t_ramp *ramp;
	ramp = NULL;
//	print_ramp(ramp);
	int ramp_size;
	ramp_size = 0;
//	for (int i = 0; i < size; i++)
//		get_color_index(coord[i], ramp_size);
	t_fdf *fdf;
	fdf = fdf_init();
	t_pt p0;
	t_pt p1;
	print_camera_settings(fdf);
	ramp_size = count_ramp(fdf->ramp_list);
	printf("ramp size: %d\n", ramp_size);


/*	puts("printing void pointer");
	for (int i = 0; fdf->ramp[i]; i++)
	{
		ramp = fdf->ramp[i];
		printf("r: %d g: %d b: %d\n", ramp->r, ramp->g, ramp->b);
	}
*/
	
	p0.x = 50;
	p0.y = 50;
	p1.x = 120;
	p1.y = 150;
	char *path;
	path = argv[argc-1];
	path = NULL;
	fdf->data->map = coord;
	fdf->data->map_w = 19;
	fdf->data->map_h = 11;

//	draw(fdf, fdf->data);
//	plot_line(fdf, p0, p1);
//	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
//	fdf->data = malloc(sizeof(t_map));
//	t_map *data;
	
//	data = fdf_map(r);
//	fdf->data = fdf_map(r);
//	int *map;
//	map = dup_coord(fdf->data->map, fdf_total(r));
//	print_map(map, fdf_total(r), fdf->data->width);
//	mlx_hook(fdf->win, 2, 0, key_control, fdf);
//	mlx_loop(fdf->mlx);
//	//fdf->test = coord;
	return (0);
}

