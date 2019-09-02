/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_theme.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:28:24 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:04:01 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

/*
** Middle color is moccasin
*/

void	fdf_theme_default(t_ramp **ramp)
{
	color_ramp(ramp, FDF_BLACK, 10, FDF_MIDNIGHT_BLUE);
	color_ramp(ramp, FDF_MIDNIGHT_BLUE, 10, FDF_MEDIUM_BLUE);
	color_ramp(ramp, FDF_MEDIUM_BLUE, 10, FDF_DEEP_SKY_BLUE);
	color_ramp(ramp, FDF_DEEP_SKY_BLUE, 10, FDF_LIGHT_BLUE);
	color_ramp(ramp, FDF_LIGHT_BLUE, 10, FDF_AZURE);
	color_ramp(ramp, FDF_AZURE, 10, FDF_MOCCASIN);
	color_ramp(ramp, FDF_MOCCASIN, 10, FDF_YELLOW_GREEN);
	color_ramp(ramp, FDF_YELLOW_GREEN, 10, FDF_FOREST_GREEN);
	color_ramp(ramp, FDF_FOREST_GREEN, 10, FDF_MAROON);
	color_ramp(ramp, FDF_MAROON, 10, FDF_SIENNA);
	color_ramp(ramp, FDF_SIENNA, 10, FDF_SNOW);
	color_ramp(ramp, FDF_SNOW, 10, FDF_BLACK);
}

/*
** Middle color is wheat
*/

void	fdf_theme_hot(t_ramp **ramp)
{
	color_ramp(ramp, FDF_DARK_RED, 10, FDF_CRIMSON);
	color_ramp(ramp, FDF_CRIMSON, 10, FDF_CORAL);
	color_ramp(ramp, FDF_CORAL, 10, FDF_LIGHT_SALMON);
	color_ramp(ramp, FDF_CORAL, 10, FDF_ORANGE);
	color_ramp(ramp, FDF_ORANGE, 10, FDF_GOLD);
	color_ramp(ramp, FDF_GOLD, 10, FDF_WHEAT);
	color_ramp(ramp, FDF_WHEAT, 10, FDF_LEMON_CHIFFON);
	color_ramp(ramp, FDF_LEMON_CHIFFON, 10, FDF_LIGHT_PINK);
	color_ramp(ramp, FDF_LIGHT_PINK, 10, FDF_PINK);
	color_ramp(ramp, FDF_PINK, 10, FDF_HOT_PINK);
	color_ramp(ramp, FDF_HOT_PINK, 10, FDF_DEEP_PINK);
	color_ramp(ramp, FDF_DEEP_PINK, 10, FDF_MEDIUM_VIOLET_RED);
}

/*
** Middle color is azure
*/

void	fdf_theme_cold(t_ramp **ramp)
{
	color_ramp(ramp, FDF_BLACK, 10, FDF_DARK_SLATE_GRAY);
	color_ramp(ramp, FDF_DARK_SLATE_GRAY, 10, FDF_SLATE_GRAY);
	color_ramp(ramp, FDF_SLATE_GRAY, 10, FDF_LIGHT_STEEL_BLUE);
	color_ramp(ramp, FDF_LIGHT_STEEL_BLUE, 10, FDF_LIGHT_SKY_BLUE);
	color_ramp(ramp, FDF_LIGHT_SKY_BLUE, 10, FDF_LIGHT_BLUE);
	color_ramp(ramp, FDF_LIGHT_BLUE, 10, FDF_AZURE);
	color_ramp(ramp, FDF_AZURE, 10, FDF_HONEYDEW);
	color_ramp(ramp, FDF_HONEYDEW, 10, FDF_PALE_GREEN);
	color_ramp(ramp, FDF_PALE_GREEN, 10, FDF_LAWN_GREEN);
	color_ramp(ramp, FDF_LAWN_GREEN, 10, FDF_LIME_GREEN);
	color_ramp(ramp, FDF_LIME_GREEN, 10, FDF_OLIVE_DRAB);
	color_ramp(ramp, FDF_OLIVE_DRAB, 10, FDF_DARK_OLIVE_GREEN);
}

void	fdf_theme_custom(t_ramp **ramp)
{
	color_ramp(ramp, FDF_BLACK, 121, FDF_WHITE);
}

t_ramp	*fdf_gen_color_ramp(t_fdf *fdf)
{
	t_ramp *ramp;

	ramp = NULL;
	if (fdf->theme == DEFAULT)
		fdf_theme_default(&ramp);
	else if (fdf->theme == HOT)
		fdf_theme_hot(&ramp);
	else if (fdf->theme == COLD)
		fdf_theme_cold(&ramp);
	else if (fdf->theme == CUSTOM)
		fdf_theme_custom(&ramp);
	return (ramp);
}
