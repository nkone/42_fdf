/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:24:01 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/08 14:42:26 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# define WIN_H		1080
# define WIN_W		1920
# define KEY_ESC	53
# define KEY_I		34
# define KEY_K		40
# define KEY_PLUS	24
# define KEY_MINUS	27
# define KEY_L_SQ_BRKT 33
# define KEY_R_SQ_BRKT 30
# define KEY_L_ARROW 123
# define KEY_R_ARROW 124
# define KEY_U_ARROW 126
# define KEY_D_ARROW 125
# define KEY_NUM_7	89
# define KEY_NUM_9	92
# define ISO_RAD	(30 * M_PI/180)

# define FDF_ABORT_MESSAGE "An unknown error has occured\n"
# define FDF_RED   0xFF0000

/*
** FDF_COLORS MACROS
** Source:
** https://en.wikipedia.org/wiki/Web_colors
*/

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

enum			e_projection
{
	ISO,
	PARALLEL
};

enum e_projection projection;

typedef struct	s_rgb
{
	int		r;
	int		g;
	int		b;
	int		rgb;
}				t_rgb;

typedef struct	s_pt
{
	double	x;
	double	y;
	int	z;
}				t_pt;

typedef struct	s_cam
{
	double		zoom;
	double		z_zoom;
	double		alpha;
	double		beta;
	double		eta;
}				t_cam;

typedef struct	s_map
{
	int		*map;
	int		map_h;
	int		map_w;
}				t_map;

typedef struct	s_fdf
{
	t_rgb		color;
	t_cam		cam;
	t_pt		pt;
	t_map		*data;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bits_per_pix;
	int			size_line;
	int			endian;
}				t_fdf;

typedef struct s_ramp
{
	int r;
	int g;
	int b;
	struct s_ramp *next;
}				t_ramp;
typedef struct		s_read
{
	struct s_read	*next;
	char			**arr;
	int				width;
	int				height;
}					t_read;
#endif

