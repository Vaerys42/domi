
#include "../rtv1.h"

double				ft_check_sphere(t_sphere *sphere, t_ray *ray)
{
	double	OH;
	double	CHCH;
	double	RR;
	double	ta;
	double	tb;
	t_coo	sphere_ray;

	sphere_ray.x = sphere->o->x - ray->o->x;
	sphere_ray.y = sphere->o->y - ray->o->y;
	sphere_ray.z = sphere->o->z - ray->o->z;
	OH = scal(ray->dir, ft_normalize(&sphere_ray));
	if (OH >= 0)
	{
		CHCH = pow(ft_norme(&sphere_ray),2) - pow(OH * ft_norme(&sphere_ray), 2);
		RR = sphere->radius * sphere->radius;
		if (CHCH <= RR )
		{
			ta = OH * ft_norme(&sphere_ray) + sqrt(RR - CHCH);
			tb = OH * ft_norme(&sphere_ray) - sqrt(RR - CHCH);
			if (ta >= tb && tb > 0)
				return(tb);
			return(ta);
		}
	}
	return(0);
}

void			check_sphere_inter(t_rt *rt)
{
	double	tmp;

	if (rt->sphere != NULL)
	{
		tmp = ft_check_sphere(rt->sphere, rt->ray);
		if (tmp < rt->inter->dst && tmp > 0)
		{
			rt->inter->dst = tmp;
			move_color(rt->inter->mat, rt->sphere->color->r, rt->sphere->color->g, rt->sphere->color->b);
			rt->inter->angle->o = ft_sub_vect(rt->inter->point, rt->sphere->o);
			rt->inter->angle->dir = ft_normalize(rt->inter->angle->o);
		}
		while (rt->sphere->next != NULL)
		{
			tmp = ft_check_sphere(rt->sphere, rt->ray);
			if (tmp < rt->inter->dst && tmp > 0)
			{
				rt->inter->dst = tmp;
				move_color(rt->inter->mat, rt->sphere->color->r, rt->sphere->color->g, rt->sphere->color->b);
				rt->inter->angle->o = ft_sub_vect(rt->inter->point, rt->sphere->o);
				rt->inter->angle->dir = ft_normalize(rt->inter->angle->o);
			}
			rt->sphere = rt->sphere->next;
		}
	}
}
