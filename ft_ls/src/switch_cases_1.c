/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_cases_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:06:47 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 18:20:45 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	case_ua(void)
{
	ignore_mode = DOT_AND_DOTDOT;
}

void	case_uf(void)
{
	indicator_style = classify;
}

void	case_ur(void)
{
	g_recursive = true;
}

void	case_us(void)
{
	sort_type = sort_size;
}

void	case_ui(void)
{
	ignore_mode = MINIMAL;
	sort_type = sort_none;
}
