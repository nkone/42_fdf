/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_multi_fdf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 11:07:09 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/31 14:50:17 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>

typedef struct		s_files
{
	char			*name;
	char			*path;
	struct s_files	*next;
}					t_files;

void	make_node(t_files **ls, char *name, char *path)
{
	*ls = malloc(sizeof(t_files));
	(*ls)->name = strdup(name);
	(*ls)->path = path;
	(*ls)->next = NULL;
}

void	make_links(t_files **ls, char *name, char *path)
{
	t_files *cursor;

	if (!*ls)
		make_node(ls, name, path);
	else if (*ls)
	{
		cursor = *ls;
		while (cursor->next)
			cursor = cursor->next;
		make_node(&(cursor->next), name, path);
	}
}

char	*path_to_file(const char *path, const char *file)
{
	char	*result;
	size_t	len;
	int		i;

	i = 0;
	len = strlen(path) + strlen(file) + 1;
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

int		is_fdf_files(const char *filename)
{
	char *extension;

	extension = strchr(filename, '.');
	if (extension)
	{
		if (strcmp(extension, ".fdf") == 0)
			return (1);
	}
	return (0);
}

t_files	*read_multi_fdf(char *name)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*path;
	t_files			*ls;

	ls = NULL;
	if ((dir = opendir(name)) == NULL)
		printf("ft_ls: %s: %s\n", name, strerror(errno));
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
	}
	return (ls);
}

void	print_multi_fdf(t_files *ls)
{
	if (!ls)
		return ;
	while (ls)
	{
		printf("name: %s path: %s\n", ls->name, ls->path);
		ls = ls->next;
	}
}

int main(int argc, char *argv[])
{
	t_files *ls;

	if (argc !=2)
		return (0);
	ls = read_multi_fdf(argv[1]);
	print_multi_fdf(ls);
	return (0);
}
