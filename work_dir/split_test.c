/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 19:38:00 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/21 19:42:19 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

int main(void)
{
	char *test = "-111 111";
	char **arr = ft_strsplit(test, ' ');
	
	for (int i = 0; arr[i]; i++)
		printf("|%s|\n", arr[i]);
}
