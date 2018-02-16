/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 01:16:26 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/31 01:16:26 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		ft_cone_info(t_cone *cone)
{
	if (cone->o == NULL)
		ft_putstr("Needs origin coordinate for cone. Ex : coo: 1 2 5\n");
	else if (cone->color == NULL)
		ft_putstr("Needs color for cone (0 to 1). Ex : color: 1 0 1\n");
	else if (cone->angle < 0)
		ft_putstr("Needs angle for cone. Ex angle: 30\n");
	else if (cone->shine < 0)
		ft_putstr("Needs shine for cone. Ex shine: 0.5\n");
	else if (cone->rot == NULL)
		ft_putstr("Needs rotation for cone. Ex : rot: 0 0 0\n");
	else
		return ;
	exit(-1);
}

t_cone		*new_cone(void)
{
	t_cone		*cone;

	if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
		ft_malloc_error();
	cone->next = NULL;
	cone->o = NULL;
	if (!(cone->dir = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	cone->dir->x = 0;
	cone->dir->y = 1;
	cone->dir->z = 0;
	cone->color = NULL;
	cone->rot = NULL;
	cone->angle = -1;
	cone->shine = -1;
	return (cone);
}

int			cone_lst(t_rt *rt, t_cone *cone)
{
	ft_cone_info(cone);
	ft_normalize(cone->dir);
	cone->angle = (cone->angle * M_PI) / 180;
	if (rt->cone == NULL)
	{
		rt->cone = cone;
		rt->start->con = rt->cone;
	}
	else
	{
		rt->cone->next = cone;
		rt->cone = rt->cone->next;
	}
	return (1);
}

void		ft_read_line(char **datas, t_cone *cone, t_rt *rt, int fd)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		cone->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		cone->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "color:") == 0)
		cone->color = get_color(datas);
	else if (ft_strcmp(datas[0], "angle:") == 0)
		cone->angle = get_radius(datas);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		cone->shine = get_radius(datas);
	else if (ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_cone(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cone		*cone;

	cone = new_cone();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_read_line(datas, cone, rt, fd);
		ft_freetab(datas);
		free(line);
	}
	return (cone_lst(rt, cone));
}
