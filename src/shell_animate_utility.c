/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_animate_utility.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:43:46 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/02 20:00:59 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static void	make_links(t_files **ls, char *name, char *path)
{
	t_files *cursor;
	t_files *new;

	cursor = *ls;
	new = malloc(sizeof(t_files));
	new->name = ft_strdup(name);
	new->path = path;
	new->next = NULL;
	if (!*ls)
	{
		new->prev = NULL;
		*ls = new;
		return ;
	}
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new;
	new->prev = cursor;
	return ;
}

static char	*path_to_file(const char *path, const char *file)
{
	char	*result;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(path) + ft_strlen(file) + 1;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result[len] = '\0';
	while (*path)
		result[i++] = *path++;
	result[i++] = '/';
	while (*file)
		result[i++] = *file++;
	return (result);
}

static int	is_fdf_files(const char *filename)
{
	char *extension;

	extension = ft_strchr(filename, '.');
	if (extension)
	{
		if (ft_strcmp(extension, ".fdf") == 0)
			return (1);
	}
	return (0);
}

t_files		*read_multi_fdf(char *name)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*path;
	t_files			*ls;

	ls = NULL;
	if ((dir = opendir(name)) == NULL)
		perror("Error");
	else
	{
		while ((dp = readdir(dir)) != NULL)
		{
			if (is_fdf_files(dp->d_name))
			{
				path = path_to_file(name, dp->d_name);
				make_links(&ls, dp->d_name, path);
			}
		}
		closedir(dir);
		shell_animate_sort(&ls);
	}
	return (ls);
}
