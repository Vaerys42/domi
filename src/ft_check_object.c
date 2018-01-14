/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 00:31:27 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/03 00:31:29 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		ft_get_point(t_rt *rt)
{
	rt->inter = ft_mult_vect(rt->dst, rt->ray->dir);
	rt->inter = ft_add_vect(rt->cam->pos, rt->inter);
}

void		ft_get_light(t_rt *rt)
{
	double		angle;

	rt->light_ray->o = ft_sub_vect(rt->light->o, rt->inter);
	rt->light_ray->dir = ft_div_vect(ft_norm_2(rt->light_ray->o), rt->light_ray->o);
	rt->angle_ray->o = ft_sub_vect(rt->inter, rt->sphere->o);
	rt->angle_ray->dir = ft_div_vect(ft_norm_2(rt->angle_ray->o), rt->angle_ray->o);
	angle = scal(rt->light_ray->dir, rt->angle_ray->dir);

	angle = (angle < 0.1) ? 0.1 : angle;

	rt->color->r = rt->color->r * rt->light->color->r * angle * rt->light->power;
	rt->color->g = rt->color->g * rt->light->color->g * angle * rt->light->power;
	rt->color->b = rt->color->b * rt->light->color->b * angle * rt->light->power;
}

double				ft_check_plane(t_plane *plane, t_ray *ray)
{
	double		a;
	double		b;

	b = scal(plane->norm, ray->dir);
	if (b == 0)
		return (-1);
	a = scal(plane->norm, ray->o) + plane->supp;
	return (-a / b);
}

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
	OH = scal(ray->dir, &sphere_ray);
	if (OH >= 0)
	{
		CHCH = pow(ft_norm_2(&sphere_ray),2) - (OH * OH);
		RR = sphere->radius * sphere->radius;
		if (CHCH <= RR)
		{
			ta = ft_norm(ray->dir, &sphere_ray) + sqrt(RR - CHCH);
			tb = ft_norm(ray->dir, &sphere_ray) - sqrt(RR - CHCH);
			if (ta >= tb)
				return(tb);
			return(ta);
		}
	}
	return(0);
}

void			ft_check_object(t_rt *rt)
{
	//double tmp;

	/*if ((rt->dst = ft_check_sphere(rt->sphere, rt->ray)) > 0)
		rt->color = rt->sphere->color;*/
	rt->color->r = 0.0;
	rt->color->g = 0.0;
	rt->color->b = 0.0;
	if ((rt->dst = ft_check_plane(rt->plane, rt->ray)) < 0){
		rt->color = rt->plane->color;
	}
	if (rt->dst <= 0.01)
		rt->dst = 0;
	if (rt->dst != 0)
	{
		ft_get_point(rt);
		ft_get_light(rt);
	}
	return ;
}
