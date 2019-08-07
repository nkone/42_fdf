/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:24:01 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/06 19:57:03 by phtruong         ###   ########.fr       */
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
	double	z;
}				t_pt;

typedef struct	s_cam
{
	double		zoom;
	double		z_zoom;
	double		alpha;
	double		beta;
	double		eta;
}				t_cam;

typedef struct	s_fdf
{
	t_rgb		color;
	t_cam		cam;
	t_pt		pt;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bits_per_pix;
	int			size_line;
	int			endian;
	int			*map;
	int			map_h;
	int			map_w;
}				t_fdf;

typedef struct		s_read
{
	struct s_read	*next;
	char			**arr;
	int				width;
	int				height;
}					t_read;
#endif

