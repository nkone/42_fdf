/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 11:59:34 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/01 17:34:40 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include <termios.h>
# include <time.h>
# include <pwd.h>
# include "../../libft/libft.h"
# include "../../libft/ft_printf.h"

# define LS_FLAGS "AIFRSailmnprtx1"

/*
** These macros are for color printing
** P_NC for no colors (end color printing mode)
*/
# define P_RED "\033[31m"
# define P_RED_HL "\033[30;41m"
# define P_GREEN "\033[32m"
# define P_YELLOW "\033[33m"
# define P_BLUE "\033[34m"
# define P_MAGENTA "\033[35m"
# define P_CYAN "\033[36m"
# define P_NC "\033[0m"

/*
** These macros are for format printing
** Not compatible with all terminals
*/
# define P_BOLD "\033[1m"
# define P_DIM "\033[2m"
# define P_UNDERLINE "\033[4m"
# define P_BLINK "\033[5m"
# define P_REVERSE "\033[7m"
# define P_HIDDEN "\033[8m"

/*
** recreating switch operation using jump table
*/
void				case_ua(void);
void				case_ui(void);
void				case_uf(void);
void				case_ur(void);
void				case_us(void);
void				case_a(void);
void				case_i(void);
void				case_l(void);
void				case_m(void);
void				case_n(void);
void				case_p(void);
void				case_r(void);
void				case_t(void);
void				case_x(void);
void				case_1(void);

/*
** jump table g_ls_flags
** Table consists of void return functions with void paramters
** Recreating switch operation (switch is forbidden in 42 school)
** uf means uppercase F (uppercase is forbidden in snake casting)
** t_ for table and g_ for global variables
*/
typedef	void		t_ls_jump(void);

static t_ls_jump	*g_ls_flags[] =
{
	case_ua,
	case_ui,
	case_uf,
	case_ur,
	case_us,
	case_a,
	case_i,
	case_l,
	case_m,
	case_n,
	case_p,
	case_r,
	case_t,
	case_x,
	case_1
};

/*
**===========================================================|
**|                 	FORMAT TABLE                         |
**|---------------+------------------------------------------|
**| Name          | Description                              |
**|---------------+------------------------------------------|
**| long_format   | list in details for -l and similar flags |
**| one_per_line  | for -1                                   |
**| many_per_line | default options sort vertically          |
**| horizontal    | for -x sort horizontally                 |
**| with_commas   | for -m print with commas                 |
**|---------------+------------------------------------------|
*/

/*
** e_ is naming covention for enum structure
*/
enum		e_format
{
	long_format,
	one_per_line,
	many_per_line,
	horizontal,
	with_commas
};

/*
** rename e_ structure to desirable name
*/
enum e_format format;

/*
** sort_name is default
** sort_time for -t
*/
enum	e_sort_type
{
	sort_none = -1,
	sort_name,
	sort_time,
	sort_size
};

enum e_sort_type sort_type;

/*
** none is default
** slash for -p
** classify for -F
*/

enum	e_indicator_style
{
	none,
	slash,
	classify
};

enum e_indicator_style indicator_style;

/*
** DOT_AND_DOTDOT for -A
** Prints hidden files starting with '.' except for '.' and '..' themselves.
** MINIMAL for -a
** Prints everything including '.' and '..'
*/

enum	e_ignore_mode
{
	DEFAULT,
	DOT_AND_DOTDOT,
	MINIMAL
};

enum e_ignore_mode ignore_mode;

/*
** for -r
** comparison is done using strcmp;
** 10 preceeds 2;
** if true then the opposite;
*/

bool g_sort_reverse;

/*
** for -i
** print inode number before each file
*/

bool g_print_inode;

/*
** for -R
** Display contents inside each directories found.
*/

bool g_recursive;

/*
** for -n
** print user and group id as number
*/

bool g_numeric_id;

/*
** to find starting argc
*/

int	g_argc;

bool g_print_total;

void	**g_sorted_file;

/*
** typedef struct stat to t_stat for naming convention
*/
typedef struct stat	t_stat;

/*
** struct s_files
** linked list structure that stores filenames and their stats
** Parameters:
** 		[name]: name of file or directory
** 		[fstat]: built in stat structure
**		[next]: pointer to next node
*/
typedef struct		s_files
{
	char			*name;
	char			*path;
	struct stat		fstat;
	char			*color;
	struct s_files	*next;
	char			style;
}					t_files;

/*
** s_pcol (print columns)
** a helper struct for column printing support
** Paramters:
** 		[col]: columns to be printed
**		[row]: total rows
**		[no_f]: number of files
**		[max]: file name max len
*/
typedef struct		s_pcol
{
	int				col;
	int				row;
	int				no_f;
	int				max;
}					t_pcol;

typedef struct		s_idx
{
	int				ino_w;
	int				lin_w;
	int				usr_w;
	int				grp_w;
	int				maj_w;
	int				min_w;
	int				siz_w;
}					t_idx;

/*
** ft_ls_util.c
*/
void				open_print(char *name);
void				print_directories(t_files *f);
void				ls_init_sort(t_files **f);

/*
** sort_util.c
*/

int					cmp_alpha(const char *s1, const char *s2);
int					cmp_time(t_files *a, t_files *b);
int					cmp_size(off_t a, off_t b);
int					select_sort(t_files *a, t_files *b);

/*
** get_settings.c
*/

void				ft_ls_init(void);
int					get_flags(char *argv[], int c);
void				flag_driver(int argc, char *argv[]);

/*
** get_macros.c
*/

char				*get_color(t_stat stat);
char				get_style(t_stat stat);
char				get_file_type(int mode);
char				get_acl_exe(char *path);

/*
** ls_core_struct.c
*/

void				make_node(t_files **ls, char *name, char *path);
void				make_links(t_files **ls, char *name, char *path);
void				merge_sort_list(t_files **ls);
void				split_list(t_files *src, t_files **front, t_files **back);
t_files				*sorted_merge(t_files *a, t_files *b, int (*cmp)());

/*
** ls_boolean.c
*/

bool				is_exe(t_stat stat);
bool				is_regular_file(const char *path);
bool				is_regular_dir(const char *path);
bool				is_empty_dir(t_files *f);
bool				file_ignored(const char *filename);

/*
** ls_index.c
*/

int					count_nbr(int n);
void				index_details(t_files *f, t_idx *i);

/*
** ls_dir.c
*/

char				*path_to_file(const char *path, const char *file);
void				free_inner_dir(t_files *f);
void				print_dir(t_files *f, int flag);
t_files				*inner_dir(const char *name);

/*
** ls_driver.c
*/
void				print_long(t_files *f);
void				print_list(t_files *f);
void				print_with_commas(t_files *f);
void				print_columns(t_pcol p);
void				ls_driver(t_files *f);

/*
** ls_print_util.c
*/

void				print_mode(int mode, char *path);
void				print_classify(t_pcol p, t_files *f);
void				print_usr_grp(t_idx i, t_files *f);
void				print_long_name(t_files *f);
void				print_time(t_files *f);

/*
** ls_time_util.c
*/

void				print_date_time(char *s);
void				print_year(char *s);
int					check_timestamp(struct tm f_time);

/*
** ls_col_util.c
*/

void				col_format(t_files *f, t_pcol *p, unsigned short wcol);
void				ls_list_globalize(t_files *f, t_pcol p);

#endif
