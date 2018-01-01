/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:50:21 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/02 17:50:23 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int				ft_line_in_file(int fd)
{
	int			i;
	char		*tmp;
	int			ret;

	i = 0;
	while ((ret = get_next_line(fd, &tmp)) > 0)
	{
		free(tmp);
		i++;
	}
	if (ret == -1)
		ft_bad_arg(1);
	free(tmp);
	return (i);
}

char			**ft_get_file(char *path)
{
	int			fd;
	int			ret;
	int			line;
	char		**file;

	fd = open(path, O_RDONLY);
	line = ft_line_in_file(fd);
	if ((file = (char**)malloc(sizeof(char*) * line + 1)) == NULL)
		ft_malloc_error();
	close(fd);
	fd = open(path, O_RDONLY);
	line = 0;
	while ((ret = get_next_line(fd, &(file[line]))) > 0)
		line++;
	file[line] = 0;
	close(fd);
	return (file);
}

void			ft_transfer(char *file, t_rt *rt)
{
	char		**line;

	line = ft_strsplit(file, ' ');
	if (ft_strcmp(line[0], "sphere") == 0)
		ft_create_sphere(rt, line);
}

void			ft_parser(char *path, t_rt *rt)
{
	char		**file;
	int			i;

	i = -1;
	file = ft_get_file(path);
	while (file[++i] != 0)
		ft_transfer(file[i], rt);
}
