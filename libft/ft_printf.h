/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:52:04 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 13:03:33 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# define _F_MINUS	(1U << 0U)
# define _F_PLUS	(1U << 1U)
# define _F_SPACE	(1U << 2U)
# define _F_ZERO	(1U << 3U)
# define _F_HASH	(1U << 4U)

# define _F_PCN		(1U << 5U)

# define _S_H		(1U << 0U)
# define _S_HH		(1U << 1U)
# define _S_L		(1U << 2U)
# define _S_LL		(1U << 3U)
# define _S_LF		(1U << 4U)
# define _S_Z		(1U << 5U)
# define _S_J		(1U << 6U)
# define _S_T		(1U << 7U)

# define _VALID_TYPES "cs%diuboxXpf"
# define LOWER_BASE "0123456789abcdef"
# define UPPER_BASE "0123456789ABCDEF"
# define D_FPREC	6

typedef struct		s_print
{
	unsigned int	argv;
	unsigned int	flag;
	int				pcn;
	unsigned int	size;
	unsigned int	type;
	int				width;
	unsigned int	done;
	const char		*str;
	va_list			ap;
}					t_print;

typedef struct		s_float
{
	uint64_t		whole;
	uint64_t		frac;
	uint32_t		space;
	uint32_t		pads;
	uint32_t		pcn;
	int8_t			sign;
	long double		rem;
	long double		diff;
}					t_float;

/*
** ft_printf.c
*/

int					collect_argv(t_print *p);
int					collector_driver(t_print *p);
int					ft_printf_con(t_print *p);
int					ft_printf_(const char *str, va_list ap);
int					ft_printf(const char *str, ...);

/*
** print_collector.c
*/

int					collect_flag(t_print *p);
int					collect_size(t_print *p);
int					collect_width(t_print *p);
int					collect_pcn(t_print *p);
int					collect_type(t_print *p);

/*
** print_char_driver.c
*/

void				print_char_(t_print *p, char c);
int					get_char_argv(t_print *p);
void				print_char(t_print *p);
void				print_mod(t_print *p);

/*
** print_main_1.c
*/

void				print_nbr(t_print *p);
void				print_unbr(t_print *p);
void				print_unbr_base2(t_print *p);
void				print_unbr_base8(t_print *p);
void				print_unbr_base16(t_print *p);

/*
** print_main_2.c
*/

void				print_void_pointer(t_print *p);
void				print_float(t_print *p);

/*
** print_string.c
*/

void				print_str_pcn(t_print *p, char *s, int space);
void				print_str_(t_print *p, char *s, int space);
void				print_str(t_print *p);
char				*get_str_argv(t_print *p);

typedef void		t_jump(t_print *p);

static	t_jump *g_print_table[] =
{
	print_char,
	print_str,
	print_mod,
	print_nbr,
	print_nbr,
	print_unbr,
	print_unbr_base2,
	print_unbr_base8,
	print_unbr_base16,
	print_unbr_base16,
	print_void_pointer,
	print_float
};

/*
** print_nbr_size_1.c
*/

intmax_t			print_nbr_nosize(va_list ap);
intmax_t			print_nbr_sizeh(va_list ap);
intmax_t			print_nbr_sizehh(va_list ap);
intmax_t			print_nbr_sizel(va_list ap);
intmax_t			print_nbr_sizell(va_list ap);

/*
** print_nbr_size_2.c
*/

intmax_t			print_nbr_sizelf(va_list ap);
intmax_t			print_nbr_sizej(va_list ap);
intmax_t			print_nbr_sizez(va_list ap);
intmax_t			print_nbr_sizet(va_list ap);
intmax_t			print_nbr_getsize(t_print *p);

typedef intmax_t	t_getsize(va_list ap);

static	t_getsize *g_signed_tab[] =
{
	print_nbr_nosize,
	print_nbr_sizeh,
	print_nbr_sizehh,
	print_nbr_sizel,
	print_nbr_sizell,
	print_nbr_sizelf,
	print_nbr_sizej,
	print_nbr_sizez,
	print_nbr_sizet
};

/*
** print_unbr_size_1.c
*/

uintmax_t			print_unbr_nosize(va_list ap);
uintmax_t			print_unbr_sizeh(va_list ap);
uintmax_t			print_unbr_sizehh(va_list ap);
uintmax_t			print_unbr_sizel(va_list ap);
uintmax_t			print_unbr_sizell(va_list ap);

/*
** print_unbr_size_2.c
*/

uintmax_t			print_unbr_sizelf(va_list ap);
uintmax_t			print_unbr_sizej(va_list ap);
uintmax_t			print_unbr_sizez(va_list ap);
uintmax_t			print_unbr_sizet(va_list ap);

typedef uintmax_t	t_getusize(va_list ap);

static	t_getusize *g_usigned_tab[] =
{
	print_unbr_nosize,
	print_unbr_sizeh,
	print_unbr_sizehh,
	print_unbr_sizel,
	print_unbr_sizell,
	print_unbr_sizelf,
	print_unbr_sizej,
	print_unbr_sizez,
	print_unbr_sizet
};

/*
** ft_printf_util.c
*/

void				reset_print(t_print *p);
void				reset_collector(t_print *p);
int					put_nchar(char c, int n);
int					get_nspace(t_print *p, int len);

/*
** print_nbr_driver.c
*/

void				print_nbr_case1(t_print *p, intmax_t n);
void				print_nbr_case2(t_print *p, intmax_t n, int sp);
void				print_nbr_case3(t_print *p, intmax_t n, int pd);
void				print_nbr_case4(t_print *p, intmax_t n, int sp, int pd);
void				print_nbr_driver(t_print *p, intmax_t n, int sp, int pd);

/*
** print_nbr_util_1.c
*/

int					print_nbr_plus_flag(intmax_t n);
int					print_nbr_sp_flag(intmax_t n);
int					get_nbr_space(t_print *p, intmax_t n, int pd);
void				process_sp_plus_flag(t_print *p, intmax_t n);
void				print_nbr_prototype(t_print *p, intmax_t n);

/*
** print_nbr_util_2.c
*/

int					flag_to_index(int flag);
int					get_nbr_len(uintmax_t n);
intmax_t			print_nbr_getsize_arg(t_print *p);

/*
** print_unbr_driver.c
*/

void				print_unbr_case1(t_print *p, uintmax_t n);
void				print_unbr_case2(t_print *p, uintmax_t n, int sp);
void				print_unbr_case3(t_print *p, uintmax_t n, int pd);
void				print_unbr_case4(t_print *p, uintmax_t n, int sp, int pd);
void				print_unbr_driver(t_print *p, uintmax_t n, int sp, int pd);

/*
** print_unbr_util_1.c
*/

void				print_uintmax(uintmax_t n);
void				process_sp_plus_flag_unbr(t_print *p);
int					get_unbr_space(t_print *p, uintmax_t n, int pd);
uintmax_t			print_unbr_getsize(t_print *p);
uintmax_t			print_unbr_getsize_arg(t_print *p);

/*
** print_unbr_util_2.c
*/

void				print_unbr_base_lo(uintmax_t n, uint8_t base);
void				print_unbr_prototype(t_print *p, uintmax_t n, uint8_t base);
void				process_hash_flag(t_print *p, uint8_t base);
int					get_unbr_len_base(uintmax_t n, uint8_t base);
int					get_unbr_sp_base(t_print *p, uintmax_t n, int d, uint8_t b);

/*
** print_unbr_util_3.c
*/

void				print_unbr_base_up(uintmax_t n, uint8_t base);

/*
** print_binary_driver.c
*/

void				print_base2_case1(t_print *p, uintmax_t n);
void				print_base2_case2(t_print *p, uintmax_t n, int sp);
void				print_base2_case3(t_print *p, uintmax_t n, int pd);
void				print_base2_case4(t_print *p, uintmax_t n, int sp, int pd);
void				print_base2_driver(t_print *p, uintmax_t n, int sp, int pd);

/*
** print_octal_driver.c
*/

void				print_base8_case1(t_print *p, uintmax_t n);
void				print_base8_case2(t_print *p, uintmax_t n, int sp);
void				print_base8_case3(t_print *p, uintmax_t n, int pd);
void				print_base8_case4(t_print *p, uintmax_t n, int sp, int pd);
void				print_base8_driver(t_print *p, uintmax_t n, int sp, int pd);

/*
** print_hex_driver.c
*/

void				print_base16_case1(t_print *p, uintmax_t n);
void				print_base16_case2(t_print *p, uintmax_t n, int sp);
void				print_base16_case3(t_print *p, uintmax_t n, int pd);
void				print_base16_case4(t_print *p, uintmax_t n, int sp, int pd);
void				print_base16_driver(t_print *p, uintmax_t n, int s, int d);

/*
** print_pointer_driver.c
*/

void				print_vp_case1(t_print *p, uintmax_t n);
void				print_vp_case2(t_print *p, uintmax_t n, int sp);
void				print_vp_case3(t_print *p, uintmax_t n, int pd);
void				print_vp_case4(t_print *p, uintmax_t n, int sp, int pd);
void				print_vp_driver(t_print *p, uintmax_t n, int sp, int pd);

/*
** print_float_driver.c
*/

void				init_float(t_float *f);
void				print_float_driver(t_print *p, t_float f);
void				print_float_(t_print *p, t_float f);
void				print_float_rounding(long double n, t_float *f);

/*
** print_float_util.c
*/

long double			get_float(t_print *p, va_list ap);
long double			get_float_arg(t_print *p);
uintmax_t			pow10(int8_t n);

#endif
