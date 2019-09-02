/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_cases_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:10:41 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/20 13:51:05 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	case_p(void)
{
	indicator_style = slash;
}

void	case_r(void)
{
	g_sort_reverse = true;
}

void	case_t(void)
{
	if (sort_type == sort_name)
		sort_type = sort_time;
}

void	case_x(void)
{
	format = horizontal;
}

void	case_1(void)
{
	format = one_per_line;
}
