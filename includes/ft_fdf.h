/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 14:27:18 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/05 18:15:41 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# include <time.h>

# define WIN_H			1080
# define WIN_W			1920
# define KEY_ESC		53
# define KEY_I			34
# define KEY_K			40
# define KEY_S			1
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_D			2
# define KEY_H			4
# define KEY_PLUS		24
# define KEY_MINUS		27
# define KEY_L_SQ_BRKT 	33
# define KEY_R_SQ_BRKT 	30
# define KEY_L_ARROW 	123
# define KEY_R_ARROW 	124
# define KEY_U_ARROW 	126
# define KEY_D_ARROW 	125
# define KEY_NUM_7		89
# define KEY_NUM_9		92

# define MOUSE_LEFT_B 		1
# define MOUSE_RIGHT_B 		2
# define MOUSE_SCROLL_UP 	4
# define MOUSE_SCROLL_DOWN 	5
# define ISO_RAD			(30 * M_PI/180)

# define FDF_ABORT_MESSAGE "An unknown error has occured\n"

# define P_RED				"\033[31m"
# define P_GREEN			"\033[32m"
# define P_YELLOW			"\033[33m"
# define P_NC				"\033[0m"
# define P_FG_256_154		"\033[38;5;154m"

# define LS_PATH				"./ft_ls/ft_ls"
# define FDF_HELP_PATH			"./read_me/help.txt"
# define FDF_SHELL_HELP_PATH	"./read_me/shell_help.txt"
# define FDF_USAGE 				"./fdf [.fdf file]\n"

# define FDF_DELAY			200
/*
** FDF_COLORS MACROS
** Source:
** https://en.wikipedia.org/wiki/Web_colors
*/

/*
** Pink Colors
*/

# define FDF_PINK					0xFFC0CB
# define FDF_LIGHT_PINK				0xFFB6C1
# define FDF_HOT_PINK				0xFF69B4
# define FDF_DEEP_PINK				0xFF1493
# define FDF_PALE_VIOLET_RED		0xDB7093
# define FDF_MEDIUM_VIOLET_RED		0xC71585

/*
** Red Colors
** Proof read check: [✓]
*/

# define FDF_LIGHT_SALMON			0xFFA07A
# define FDF_SALMON					0xFA8072
# define FDF_DARK_SALMON			0xE9967A
# define FDF_LIGHT_CORAL			0xF08080
# define FDF_INDIAN_RED				0xCD5C5C
# define FDF_CRIMSON				0xDC143C
# define FDF_FIREBRICK				0xB22222
# define FDF_DARK_RED				0x8B0000
# define FDF_RED					0xFF0000

/*
** Orange Colors
*/

# define FDF_ORANGE_RED				0xFF4500
# define FDF_TOMATO					0xFF6347
# define FDF_CORAL					0xFF7F50
# define FDF_DARK_ORANGE			0xFF8C00
# define FDF_ORANGE					0xFFA500

/*
** Green Colors
** Proof read check: [✓]
*/

# define FDF_DARK_OLIVE_GREEN		0x556B2F
# define FDF_OLIVE					0x808000
# define FDF_OLIVE_DRAB				0x6B8E23
# define FDF_YELLOW_GREEN			0x9ACD32
# define FDF_LIME_GREEN				0x32CD32
# define FDF_LIME					0x00FF00
# define FDF_LAWN_GREEN				0x7CFC00
# define FDF_CHARTREUSE				0x7FFF00
# define FDF_GREEN_YELLOW			0xADFF2F
# define FDF_SPRING_GREEN			0x00FF7F
# define FDF_MEDIUM_SPRING_GREEN	0x00FA9A
# define FDF_LIGHT_GREEN			0x90EE90
# define FDF_PALE_GREEN				0x98FB98
# define FDF_DARK_SEA_GREEN			0x8FBC8F
# define FDF_MEDIUM_AQUAMARINE		0x66CDAA
# define FDF_MEDIUM_SEA_GREEN		0x3CB371
# define FDF_SEA_GREEN				0x2E8B57
# define FDF_FOREST_GREEN			0x228B22
# define FDF_GREEN					0x008000
# define FDF_DARK_GREEN				0x006400

/*
** Blue Colors
** Proof read check: [✓]
*/

# define FDF_LIGHT_STEEL_BLUE		0xB0C4DE
# define FDF_POWDER_BLUE			0xB0E0E6
# define FDF_LIGHT_BLUE				0xADD8E6
# define FDF_SKY_BLUE				0x87CEEB
# define FDF_LIGHT_SKY_BLUE			0x87CEFA
# define FDF_DEEP_SKY_BLUE			0x00BFFF
# define FDF_DODGER_BLUE			0x1E90FF
# define FDF_CORN_FLOWER_BLUE		0x6495ED
# define FDF_STEEL_BLUE				0x4682B4
# define FDF_ROYAL_BLUE				0x4169E1
# define FDF_BLUE					0x0000FF
# define FDF_MEDIUM_BLUE			0x0000CD
# define FDF_DARK_BLUE				0x00008B
# define FDF_NAVY					0x000080
# define FDF_MIDNIGHT_BLUE			0x191970

/*
** Brown Colors
** Proof read check: [✓]
*/

# define FDF_CORNSILK				0xFFF8DC
# define FDF_BLANCHED_ALMOND		0xFFEBCD
# define FDF_BISQUE					0xFFE4C4
# define FDF_NAVAJO_WHITE			0xFFDEAD
# define FDF_WHEAT					0xF5DEB3
# define FDF_BURLYWOOD				0xDEB887
# define FDF_TAN					0xD2B48C
# define FDF_ROSY_BROWN				0xBC8F8F
# define FDF_SANDY_BROWN			0xF4A460
# define FDF_GOLDRENROD				0xDAA520
# define FDF_DARK_GOLDENROD			0xB8860B
# define FDF_PERU					0xCD853F
# define FDF_CHOCOLATE				0xD2691E
# define FDF_SADDLE_BROWN			0x8B4513
# define FDF_SIENNA					0xA0522D
# define FDF_BROWN					0xA52A2A
# define FDF_MAROON					0x800000

/*
** Yellow Colors
** Proof read check: [✓]
*/

# define FDF_YELLOW					0xFFFF00
# define FDF_LIGHT_YELLOW			0xFFFFE0
# define FDF_LEMON_CHIFFON			0xFFFACD
# define FDF_LIGHT_GOLDENROD_YELLOW	0xFAFAD2
# define FDF_PAPAYA_WHIP			0xFFEFD5
# define FDF_MOCCASIN				0xFFE4B5
# define FDF_PEACH_PUFF				0xFFDAB9
# define FDF_PALE_GOLDENROD			0xEEE8AA
# define FDF_KHAKI					0xF0E68C
# define FDF_DARK_KHAKI				0xBDB76B
# define FDF_GOLD					0xFFD700

/*
** White Colors
** Proof read check: [✓]
*/

# define FDF_WHITE					0xFFFFFF
# define FDF_SNOW					0xFFFAFA
# define FDF_HONEYDEW				0xF0FFF0
# define FDF_MINT_CREAM				0xF5FFFA
# define FDF_AZURE					0xF0FFFF
# define FDF_ALICE_BLUE				0xF0F8FF
# define FDF_GHOST_WHITE			0xF8F8FF
# define FDF_WHITE_SMOKE			0xF5F5F5
# define FDF_SEASHELL				0xFFF5EE
# define FDF_BEIGE					0xF5F5DC
# define FDF_OLD_LACE				0xFDF5E6
# define FDF_FLORAL_WHITE			0xFFFAF0
# define FDF_IVORY					0xFFFFF0
# define FDF_ANTIQUE_WHITE			0xFAEBD7
# define FDF_LINEN					0xFAF0E6
# define FDF_LAVENDER_BLUSH			0xFFF0F5
# define FDF_MISTY_ROSE				0xFFE4E1

/*
** Gray and Black Colors
** Proof read check: [✓]
*/

# define FDF_GAINSBORO				0xDCDCDC
# define FDF_LIGHT_GRAY				0xD3D3D3
# define FDF_SILVER					0xC0C0C0
# define FDF_DARK_GRAY				0xA9A9A9
# define FDF_GRAY					0x808080
# define FDF_DIM_GRAY				0x696969
# define FDF_LIGHT_SLATE_GRAY		0x778899
# define FDF_SLATE_GRAY				0x708090
# define FDF_DARK_SLATE_GRAY		0x2F4F4F
# define FDF_BLACK					0x000000

typedef enum		e_projection
{
	ISO,
	PARALLEL,
	ELEVATION
}					t_projection;

typedef enum		e_theme
{
	DEFAULT,
	COLD,
	HOT,
	CUSTOM
}					t_theme;

typedef struct		s_rgb
{
	int		r;
	int		g;
	int		b;
	int		rgb;
}					t_rgb;

typedef struct		s_pt
{
	int		x;
	int		y;
	int		z;
	t_rgb	rgb;
}					t_pt;

typedef struct		s_cam
{
	double			zoom;
	double			zoom_accel;
	double			z_zoom;
	double			z_accel;
	double			depth_f;
	double			alpha;
	double			beta;
	double			eta;
	int				brightness;
	bool			depth;
	bool			after_img;
	bool			anti_alias;
	int				x_offset;
	int				y_offset;
	t_projection	projection;
}					t_cam;

typedef struct		s_mouse
{
	int		x;
	int		y;
	int		prev_x;
	int		prev_y;
	bool	left_b;
	bool	right_b;
}					t_mouse;

typedef struct		s_ramp
{
	int				r;
	int				g;
	int				b;
	struct s_ramp	*next;
}					t_ramp;

typedef struct		s_map
{
	int		*map;
	int		*c_map;
	int		map_h;
	int		map_w;
	int		map_size;
	bool	map_color;
}					t_map;

typedef struct		s_var
{
	bool	steep;
	bool	swap;
	bool	swap_d;
	double	dx;
	double	dy;
	double	gradient;
	double	xend;
	double	yend;
	double	xgap;
	double	ygap;
	int		xpxl1;
	int		ypxl1;
	double	intery;
	double	interx;
	int		xpxl2;
	int		ypxl2;
}					t_var;

typedef struct		s_files
{
	char			*name;
	char			*path;
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct		s_fdf
{
	t_rgb		color;
	t_cam		cam;
	t_pt		pt;
	t_map		*data;
	t_ramp		*ramp_list;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	void		**ramp;
	int			ramp_size;
	int			bits_per_pix;
	int			size_line;
	int			endian;
	double		coef_m;
	double		coef_b;
	int			min;
	int			max;
	t_theme		theme;
	t_mouse		mouse;
	bool		help;
	bool		multi_fdf;
	int			multi_delay;
	t_files		*fdf_queue;
}					t_fdf;

typedef struct		s_read
{
	struct s_read	*next;
	char			**arr;
}					t_read;

/*
** button_mapping_brightness.c
*/

void				handle_brightness_button(int x, int y, t_fdf *fdf);

/*
** button_mapping_depth.c
*/

void				handle_depth_button(int x, int y, t_fdf *fdf);

/*
** button_mapping_extra.c
*/

void				handle_extra_button(int x, int y, t_fdf *fdf);

/*
** button_mapping_theme.c
*/

void				handle_theme_button(int x, int y, t_fdf *fdf);
void				switch_fdf_theme(t_fdf *fdf, int theme);

/*
** button_mapping_view.c
*/

void				handle_view_button(int x, int y, t_fdf *fdf);

/*
** button_mapping_zoom.c
*/

void				handle_z_zoom_button(int x, int y, t_fdf *fdf);
void				handle_z_accel_button(int x, int y, t_fdf *fdf);
void				handle_zoom_button(int x, int y, t_fdf *fdf);

/*
** color_ramp.c
*/

void				int_to_rgb(t_rgb *ret, int color);
void				append_ramp_node(t_ramp **ramp, t_rgb rgb);
void				color_node(t_rgb start, int steps, t_rgb end, t_rgb *rgb);
void				color_ramp(t_ramp **r, int c_start, int steps, int c_end);
t_ramp				*create_ramp_node(t_rgb rgb);

/*
** color_ramp_util.c
*/

int					count_ramp(t_ramp *ramp);
void				**fdf_index_color_ramp(t_ramp *ramp);
void				free_color_ramp(t_ramp *ramp);
int					get_color_index(int z, int size);

/*
** draw_help_1.c
*/

void				draw_help_title(int fd, t_fdf *fdf);
void				draw_help_mouse(int fd, t_fdf *fdf);
void				draw_help_description_view(int fd, t_fdf *fdf);
void				draw_help_description_theme(int fd, t_fdf *fdf);
void				draw_help_description_depth(int fd, t_fdf *fdf);

/*
** draw_help_2.c
*/

void				draw_help_description_brightness(int fd, t_fdf *fdf);
void				draw_help_description_z_zoom(int fd, t_fdf *fdf);
void				draw_help_description_z_accel(int fd, t_fdf *fdf);
void				draw_help_button(int fd, t_fdf *fdf);
void				draw_help_utility(int fd, t_fdf *fdf);

/*
** draw_help_driver.c
*/

void				draw_help_menu(t_fdf *fdf);

/*
** draw_menu_1.c
*/

void				draw_view_menu(t_fdf *fdf);
void				draw_info_angle_menu(t_fdf *fdf);
void				draw_info_min_max_menu(t_fdf *fdf);
void				draw_theme_menu(t_fdf *fdf);
void				draw_depth_menu(t_fdf *fdf);

/*
** draw_menu_2.c
*/

void				draw_z_zoom_menu(t_fdf *fdf);
void				draw_z_accel_menu(t_fdf *fdf);
void				draw_zoom_menu(t_fdf *fdf);
void				draw_after_img_menu(t_fdf *fdf);
void				draw_utility_menu(t_fdf *fdf);

/*
** draw_menu_driver.c
*/

void				draw_bg(t_fdf *fdf);
void				draw_menu(t_fdf *fdf);

/*
** fdf_initializers.c
*/

t_map				*fdf_init_data_struct(void);
t_cam				fdf_cam_init(void);
t_mouse				mouse_init(void);
t_fdf				*fdf_init(void);

/*
** fdf_parser.c
*/

void				create_arr_node(t_read **head, char **block);
void				link_arr_node(t_read **head, char **block);
int					*parse_fdf(int fd, t_fdf *fdf);

/*
** fdf_minishell.c
*/

void				shell_in(t_fdf *fdf);
int					check_input(char **input, t_fdf *fdf);
void				free_input(char **input);

/*
** fdf_theme.c
*/

void				fdf_theme_default(t_ramp **ramp);
void				fdf_theme_hot(t_ramp **ramp);
void				fdf_theme_cold(t_ramp **ramp);
void				fdf_theme_custom(t_ramp **ramp);
t_ramp				*fdf_gen_color_ramp(t_fdf *fdf);

/*
** fdf_utility.c
*/

int					abort_fdf(void);
void				delay(int milliseconds);

/*
** keyboard_mapping.c
*/

int					key_control(int key, t_fdf *fdf);

/*
** map_fdf.c
*/

int					count_arr_width(char **arr);
int					check_map_width(t_read *read);
int					check_map_height(t_read *read);
int					get_map_size(t_read *read, t_fdf *fdf);
int					*map_coord(t_read *read, t_fdf *fdf);

/*
** map_fdf_utility.c
*/

void				map_magic(const char *str, int *map, int *c, t_fdf *fdf);

/*
** mouse_handler.c
*/

void				handle_mouse_left_b(int x, int y, t_fdf *fdf);
void				handle_mouse_right_b(int button, t_fdf *fdf);
int					mouse_press(int button, int x, int y, t_fdf *fdf);
int					mouse_release(int button, int x, int y, t_fdf *fdf);
int					mouse_move(int x, int y, t_fdf *fdf);

/*
** plot_init.c
*/

void				plot_line_init(t_pt *p0, t_pt *p1, t_var *var);
void				plot_line_first_pt(t_fdf *fdf, t_var *var, t_pt p0);
void				plot_line_second_pt(t_fdf *fdf, t_var *var, t_pt p1);

/*
** plot_main.c
*/

void				plot_line(t_fdf *fdf, t_pt p0, t_pt p1);

/*
** plot_pixel.c
*/

void				plot_pixel(t_fdf *frame, int x, int y, int rgb);
t_rgb				apply_depth(int z, t_rgb rgb, t_fdf *fdf);
void				apply_brightness(t_rgb *rgb, int brightness);
int					get_color(t_rgb s, t_rgb e, double curr, double bright);

/*
** plot_util_calculations.c
*/

int					ipart(double x);
int					ft_round(double x);
double				fpart(double x);
double				rfpart(double x);
double				curr_percent(int start, int curr, int end);

/*
** point_generator.c
*/

t_pt				get_point(t_pt p, t_fdf *fdf);
t_pt				gen_point(int x, int y, t_fdf *fdf);
int					draw(t_fdf *fdf, t_map *data);
void				draw_multi_fdf(t_fdf *fdf, t_files *fdf_queue);

/*
** rotation_magic.c
*/

void				fdf_rot_x(int *y, int *z, double alpha);
void				fdf_rot_y(int *x, int *z, double beta);
void				fdf_rot_z(int *x, int *y, double eta);
void				fdf_iso(int *x, int *y, int z);

/*
** shell_animate_wrapper.c
*/

void				shell_animate_wrapper(char **input, t_fdf *fdf);

/*
** shell_info_wrapper.c
*/

void				shell_info_wrapper(t_fdf *fdf);

/*
** shell_change_wrapper.c
*/

void				shell_change_wrapper(char **input, t_fdf *fdf);

/*
** shell_ls_wrapper.c
*/

void				shell_ls_wrapper(char **input);

/*
** shell_animate_sort.c
*/

void				shell_animate_sort(t_files **ls);

/*
** shell_animate_utility.c
*/

t_files				*read_multi_fdf(char *name);

/*
** zoom_magic.c
*/

void				extract_min_max(int *map, int *min, int *max, int size);
void				get_coefficient(int *map, t_fdf *fdf);
void				fdf_zoom_magic(t_fdf *fdf);

#endif
