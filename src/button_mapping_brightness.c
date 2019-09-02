/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brightness_button_mapping.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:10:31 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 12:58:48 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	handle_brightness_button(int x, int y, t_fdf *fdf)
{
	double h;

	h = 1.88;
	if (x >= WIN_W / 30 + 16 && x <= WIN_W / 30 + 36 &&
		y >= WIN_H / h + 55 && y <= WIN_H / h + 70)
	{
		fdf->cam.brightness -= 5;
		if (fdf->cam.after_img == false && fdf->cam.brightness < 0)
			fdf->cam.brightness = 0;
	}
	if (x >= WIN_W / 30 + 163 && x <= WIN_W / 30 + 186 &&
		y >= WIN_H / h + 55 && y <= WIN_H / h + 70)
	{
		fdf->cam.brightness += 5;
		if (fdf->cam.brightness > 255)
			fdf->cam.brightness = 255;
	}
}
