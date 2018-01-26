
#include "../rtv1.h"

int				ft_add_cone(int fd, t_rt *rt)
{
	int 		ret;
	char		*line;
	char		**datas;
	t_cone		*cone;

	if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
		ft_malloc_error();
	cone->next = NULL;
	cone->o = NULL;
	cone->dir = NULL;
	cone->color = NULL;
	cone->angle = -1;
	line = ft_strdup("");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (ft_strcmp(datas[0], "coo:") == 0)
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

int				ft_add_sphere(int fd, t_rt *rt)
{
	int 		ret;
	char		*line;
	char		**datas;
	t_sphere	*sphere;

	if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		ft_malloc_error();
	sphere->next = NULL;
	sphere->o = NULL;
	sphere->color = NULL;
	sphere->radius = -1;
	line = ft_strdup("");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
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

int			ft_add_plane(int fd, t_rt *rt)
{
	int 		ret;
	char		*line;
	char		**datas;
	t_plane		*plane;

	if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
		ft_malloc_error();
	plane->next = NULL;
	plane->o = NULL;
	plane->color = NULL;
	plane->norm = NULL;
	line = ft_strdup("");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (ft_strcmp(datas[0], "coo:") == 0)
			plane->o = get_coo(datas, 2);
		else if (ft_strcmp(datas[0], "color:") == 0)
			plane->color = get_color(datas);
		else if (ft_strcmp(datas[0], "norm:") == 0)
			plane->norm = get_coo(datas, 6);
		else if (ft_check_obj(datas[0], fd, rt) == 1)
			ret++;
		else
			ft_bad_arg(5);
	}
	ft_plane_info(plane);
	if (rt->plane == NULL)
	{
		rt->plane = plane;
		rt->start->pln = rt->plane;
	}
	else
	{
		rt->plane->next = plane;
		rt->plane = rt->plane->next;
	}
	return (1);
}

int			ft_check_obj(char *str, int fd, t_rt *rt)
{
	if (ft_strcmp(str, "plane") == 0)
		return (ft_add_plane(fd, rt));
	else if (ft_strcmp(str, "sphere") == 0)
		return (ft_add_sphere(fd, rt));
	else if (ft_strcmp(str, "cone") == 0)
		return (ft_add_cone(fd, rt));
	else
		return (0);
	return (0);
}