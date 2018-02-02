/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 22:21:24 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 22:21:25 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		ft_sphere_info(t_sphere *sphere)
{
	if (sphere->o == NULL)
		ft_putstr("Needs origin coordinate for sphere. Ex : coo: 1 2 5\n");
	else if (sphere->color == NULL)
		ft_putstr("Needs color for sphere (0 to 1). Ex : color: 1 0 1\n");
	else if (sphere->radius == -1)
		ft_putstr("Needs radius for sphere. Ex radius: 3\n");
	else
		return ;
	exit(-1);
}

int			sphere_list(t_rt *rt, t_sphere *sphere)
{
	ft_sphere_info(sphere);
	if (rt->sphere == NULL)
	{
		rt->sphere = sphere;
		rt->start->sph = rt->sphere;
	}
	else
	{
		rt->sphere->next = sphere;
		rt->sphere = rt->sphere->next;
	}
	return (1);
}

t_sphere	*sph_ini(void)
{
	t_sphere	*sphere;

	if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		ft_malloc_error();
	sphere->next = NULL;
	sphere->o = NULL;
	sphere->color = NULL;
	sphere->radius = -1;
	return (sphere);
}

int			ft_add_sphere(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_sphere	*sphere;

	sphere = sph_ini();
	line = ft_strdup("");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (datas[0] == 0)
			ret++;
		if (ft_strcmp(datas[0], "coo:") == 0)
			sphere->o = get_coo(datas, 2);
		else if (ft_strcmp(datas[0], "color:") == 0)
			sphere->color = get_color(datas);
		else if (ft_strcmp(datas[0], "radius:") == 0)
			sphere->radius = get_radius(datas);
		else if (ft_check_obj(datas[0], fd, rt) == 1)
			ret++;
		else
			ft_bad_arg(5);
	}
	return (sphere_list(rt, sphere));
}
