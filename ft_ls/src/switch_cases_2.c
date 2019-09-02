/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_cases_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:09:20 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 18:20:35 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	case_a(void)
{
	ignore_mode = MINIMAL;
}

void	case_i(void)
{
	g_print_inode = true;
}

void	case_l(void)
{
	format = long_format;
}

void	case_m(void)
{
	format = with_commas;
}

void	case_n(void)
{
	g_numeric_id = true;
	format = long_format;
}
