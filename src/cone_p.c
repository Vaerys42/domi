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
	else if (cone->dir == NULL)
		ft_putstr("Needs dir for cone. Ex dir: 0 -1 0\n");
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
	cone->dir = NULL;
	cone->color = NULL;
	cone->angle = -1;
	return (cone);
}

int			cone_lst(t_rt *rt, t_cone *cone)
{
	ft_cone_info(cone);
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

int			ft_add_cone(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cone		*cone;

	cone = new_cone();
	line = ft_strdup("");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (datas[0] == 0)
			ret++;
		else if (ft_strcmp(datas[0], "coo:") == 0)
			cone->o = get_coo(datas, 2);
		else if (ft_strcmp(datas[0], "dir:") == 0)
			cone->dir = get_coo(datas, 7);
		else if (ft_strcmp(datas[0], "color:") == 0)
			cone->color = get_color(datas);
		else if (ft_strcmp(datas[0], "angle:") == 0)
			cone->angle = get_radius(datas);
		else if (ft_check_obj(datas[0], fd, rt) == 1)
			ret++;
		else
			ft_bad_arg(5);
	}
	return (cone_lst(rt, cone));
}
