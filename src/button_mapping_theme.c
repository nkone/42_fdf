/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theme_button_mapping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:08:39 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/01 17:04:54 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static void	handle_theme_button_2(int x, int y, t_fdf *fdf)
{
	double h;

	h = 2.35;
	if (x >= WIN_W / 30 + 94 && x <= WIN_W / 30 + 148 &&
		y >= WIN_H / h + 30 && y <= WIN_H / h + 45)
	{
		ft_printf("Theme switched to: COLD\n");
		switch_fdf_theme(fdf, COLD);
	}
	if (x >= WIN_W / 30 + 94 && x <= WIN_W / 30 + 166 &&
		y >= WIN_H / h + 55 && y <= WIN_H / h + 70)
	{
		ft_printf("Theme switched to: CUSTOM\n");
		switch_fdf_theme(fdf, CUSTOM);
	}
}

void		handle_theme_button(int x, int y, t_fdf *fdf)
{
	double h;

	h = 2.35;
	if (x >= WIN_W / 30 + 94 && x <= WIN_W / 30 + 176 &&
		y >= WIN_H / h - 45 && y <= WIN_H / h - 30)
	{
		ft_printf("Theme switched to: DEFAULT\n");
		switch_fdf_theme(fdf, DEFAULT);
	}
	if (x >= WIN_W / 30 + 94 && x <= WIN_W / 30 + 136 &&
		y >= WIN_H / h - 20 && y <= WIN_H / h - 5)
	{
		ft_printf("Theme switched to: HOT\n");
		switch_fdf_theme(fdf, HOT);
	}
	handle_theme_button_2(x, y, fdf);
}

void		switch_fdf_theme(t_fdf *fdf, int theme)
{
	int i;

	i = 0;
	fdf->theme = theme;
	fdf->data->map_color = false;
	while (fdf->ramp[i])
		free(fdf->ramp[i++]);
	free(fdf->ramp);
	fdf->ramp_list = fdf_gen_color_ramp(fdf);
	fdf->ramp = fdf_index_color_ramp(fdf->ramp_list);
	fdf->ramp_size = count_ramp(fdf->ramp_list);
}
