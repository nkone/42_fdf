/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_util_calculations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:26:53 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:05:25 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

double	ipart(double x)
{
	return (floor(x));
}

double	round(double x)
{
	return (ipart(x + 0.5));
}

double	fpart(double x)
{
	return (x - floor(x));
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
