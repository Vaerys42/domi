/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:01:32 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 19:01:34 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

double		sphere_dst_rslt(double oh, t_coo sphere_ray, double det)
{
	double	ta;
	double	tb;

	ta = oh * ft_norme(sphere_ray) + det;
	tb = oh * ft_norme(sphere_ray) - det;
	if (ta >= tb && tb > 0)
		return (tb);
	return (ta);
}

double		ft_check_sphere(t_sphere *sphere, t_ray *ray)
{
	double	oh;
	double	chch;
	double	rr;
	t_coo	sphere_ray;

	sphere_ray.x = sphere->o.x - ray->o.x;
	sphere_ray.y = sphere->o.y - ray->o.y;
	sphere_ray.z = sphere->o.z - ray->o.z;
	oh = scal(ray->dir, ft_normalize(sphere_ray));
	if (oh >= 0)
	{
		chch = pow(ft_norme(sphere_ray), 2) -
		pow(oh * ft_norme(sphere_ray), 2);
		rr = sphere->radius * sphere->radius;
		if (chch <= rr)
			return (sphere_dst_rslt(oh, sphere_ray, sqrt(rr - chch)));
	}
	return (0);
}

void		new_sphere_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		rt->inter->obj = SPH;
	if (type == 1 && rt->inter->obj == SPH)
	{
		move_color(rt->inter->mat, rt->sphere->color->r,
		rt->sphere->color->g, rt->sphere->color->b);
		rt->light->shine = rt->sphere->shine;
		rt->inter->angle->o = ft_sub_vect(rt->inter->point,
		rt->sphere->o);
		rt->inter->angle->dir = ft_normalize(rt->inter->angle->o);
	}
}

void		check_sphere_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->sph != NULL)
	{
		rt->sphere = rt->start->sph;
		while (rt->sphere != NULL)
		{
			if (type == 0)
				tmp = ft_check_sphere(rt->sphere, rt->ray);
			else
				tmp = ft_check_sphere(rt->sphere, rt->light_ray);
			if (tmp < rt->inter->dst && tmp > 0)
				new_sphere_dst(rt, type, tmp);
			rt->sphere = rt->sphere->next;
		}
	}
}
