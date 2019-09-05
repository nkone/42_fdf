/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_util_calculations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:26:53 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/04 23:18:21 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

int		ipart(double x)
{
	return ((int)x);
}

int		ft_round(double x)
{
	return (ipart(x + 0.5));
}

double	fpart(double x)
{
	if (x > 0)
		return (x - ipart(x));
	else
		return (x - (ipart(x) + 1));
}

double	rfpart(double x)
{
	return (1 - fpart(x));
}

double	curr_percent(double start, double curr, double end)
{
	double here;
	double distance;
	double where;

	distance = end - start;
	where = curr - start;
	here = (distance == 0.0) ? 1.0 : (where / distance);
	return (here);
}
