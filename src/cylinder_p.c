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
	if (cylinder->o == NULL)
		ft_putstr("Needs origin coordinate for cylinder. Ex : coo: 1 2 5\n");
	else if (cylinder->color == NULL)
		ft_putstr("Needs color for cylinder (0 to 1). Ex : color: 1 0 1\n");
	else if (cylinder->radius == -1)
		ft_putstr("Needs radius for cylinder. Ex radius: 3\n");
	else if (cylinder->rot == NULL)
		ft_putstr("Needs rotation for cylinder . Ex : rot: 0 0 0\n");
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
	cylinder->next = NULL;
	cylinder->o = NULL;
	cylinder->color = NULL;
	cylinder->rot = NULL;
	cylinder->radius = -1;
	return (cylinder);
}

int			ft_add_cylinder(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cylinder	*cylinder;

	cylinder = cyl_ini();
	line = ft_strdup("");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (datas[0] == 0)
			ret++;
		if (ft_strcmp(datas[0], "coo:") == 0)
			cylinder->o = get_coo(datas, 2);
		else if (ft_strcmp(datas[0], "color:") == 0)
			cylinder->color = get_color(datas);
		else if (ft_strcmp(datas[0], "radius:") == 0)
			cylinder->radius = get_radius(datas);
		else if (ft_strcmp(datas[0], "rot:") == 0)
			cylinder->rot = get_coo(datas, 7);
		else if (ft_check_obj(datas[0], fd, rt) == 1)
			ret++;
		else
			ft_bad_arg(5);
	}
	return (cylinder_list(rt, cylinder));
}
