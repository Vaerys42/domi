/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 01:16:36 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/31 01:16:37 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		ft_cylinder_info(t_cylinder *cylinder)
{
	if (cylinder->color == NULL)
		ft_putstr("Needs color for cylinder (0 to 1). Ex : color: 1 0 1\n");
	else if (cylinder->radius == -1)
		ft_putstr("Needs radius for cylinder. Ex radius: 3\n");
	else if (cylinder->shine < 0)
		ft_putstr("Needs shine for cylinder. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

int			cylinder_list(t_rt *rt, t_cylinder *cylinder)
{
	ft_cylinder_info(cylinder);
	if (rt->cylinder == NULL)
	{
		rt->cylinder = cylinder;
		rt->start->cyl = rt->cylinder;
	}
	else
	{
		rt->cylinder->next = cylinder;
		rt->cylinder = rt->cylinder->next;
	}
	return (1);
}

t_cylinder	*cyl_ini(void)
{
	t_cylinder	*cylinder;

	if (!(cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
		ft_malloc_error();
	cylinder->dir = ft_new_vect(0, 1, 0);
	cylinder->next = NULL;
	cylinder->o = ft_new_vect(0, 0, 0);
	cylinder->color = NULL;
	cylinder->rot = ft_new_vect(0, 0, 0);
	cylinder->radius = -1;
	return (cylinder);
}

void		ft_cyl_read_line(char **datas, t_cylinder *cyl, t_rt *rt, int fd)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		cyl->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		cyl->color = get_color(datas);
	else if (ft_strcmp(datas[0], "radius:") == 0)
		cyl->radius = get_radius(datas);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		cyl->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		cyl->shine = get_radius(datas);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_cylinder(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cylinder	*cylinder;

	cylinder = cyl_ini();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_cyl_read_line(datas, cylinder, rt, fd);
		ft_freetab(datas);
		free(line);
	}
	return (cylinder_list(rt, cylinder));
}
