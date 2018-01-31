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

int			ft_check_obj(char *str, int fd, t_rt *rt)
{
	if (ft_strcmp(str, "plane") == 0)
		return (ft_add_plane(fd, rt));
	else if (ft_strcmp(str, "sphere") == 0)
		return (ft_add_sphere(fd, rt));
	else if (ft_strcmp(str, "cone") == 0)
		return (ft_add_cone(fd, rt));
	else if (ft_strcmp(str, "cylinder") == 0)
		return (ft_add_cylinder(fd, rt));
	else
	{
		printf("%s\n", str);
		return (0);
	}
	return (0);
}

void		ft_ini_struct(t_rt *rt)
{
	if (!(rt->start = (t_start*)malloc(sizeof(t_start))))
		ft_malloc_error();
	rt->sphere = NULL;
	rt->plane = NULL;
	rt->cone = NULL;
	rt->cylinder = NULL;
	rt->start->sph = NULL;
	rt->start->pln = NULL;
	rt->start->con = NULL;
	rt->start->cyl = NULL;
}

void		parser(t_rt *rt, char *file)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_bad_arg(1);
	ft_ini_struct(rt);
	while ((ret = get_next_line(fd, &line)) > 0)
		ft_check_obj(line, fd, rt);
	if (ret == -1)
		ft_bad_arg(-1);
}
