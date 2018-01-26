
#include "../rtv1.h"

void				ft_sphere_info(t_sphere *sphere)
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

void				ft_plane_info(t_plane *plane)
{
	if (plane->o == NULL)
		ft_putstr("Needs origin coordinate for plane. Ex : coo: 1 2 5\n");
	else if (plane->color == NULL)
		ft_putstr("Needs color for plane (0 to 1). Ex : color: 1 0 1\n");
	else if (plane->norm == NULL)
		ft_putstr("Needs normal vector for plnae. Ex norm: 0 0 1\n");
	else 
		return ;
	exit (-1);
}

void				ft_cone_info(t_cone *cone)
{
	if (cone->o == NULL)
		ft_putstr("Needs origin coordinate for cone. Ex : coo: 1 2 5\n");
	else if (cone->color == NULL)
		ft_putstr("Needs color for cone (0 to 1). Ex : color: 1 0 1\n");
	else if (cone->angle < 0)
		ft_putstr("Needs angle for cone. Ex angle: 30\n");
	else if (cone->dir == NULL)
		ft_putstr("Needs dir for cone. Ex dir: 0 -1 0");
	else
		return ;
	exit (-1);
}