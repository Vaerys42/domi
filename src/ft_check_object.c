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
	double	k;

	rt->color->r = rt->sphere->color->r * rt->light->power;
	rt->color->g = rt->sphere->color->g * rt->light->power;
	rt->color->b = rt->sphere->color->b * rt->light->power;


	rt->light_ray->o = ft_sub_vect(rt->inter, rt->light->o);
	rt->light_ray->dir = ft_div_vect(ft_norm_2(rt->light_ray->o), rt->light_ray->o);
	rt->angle_ray->o = ft_sub_vect(rt->inter, rt->sphere->o);
	rt->angle_ray->dir = ft_div_vect(ft_norm_2(rt->angle_ray->o), rt->angle_ray->o);
	angle = scal(rt->light_ray->dir, rt->angle_ray->dir);

	angle = (angle < 0.1) ? 0.1 : angle;
	k = 0.9;

	rt->color->r = rt->color->r + rt->light->color->r * angle * k;
	rt->color->g = rt->color->g + rt->light->color->g * angle * k;
	rt->color->b = rt->color->b + rt->light->color->b * angle * k;
	//printf("r%f g%f b%f\n", rt->color->r, rt->color->g, rt->color->b );
}

/*
int			ft_check_plane(t_rt *rt)
{
	double	result;

	result =
	if (result == 0)
		return (rt->plane->color);
	return (0x000000);
}
*/
double				ft_check_sphere(t_rt *rt)
{
	//double	a;
	//double	b;
	//double	c;
	//double	det;

	double OH;

	rt->sphere_ray->o = ft_sub_vect(rt->sphere->o, rt->cam->pos);

	OH = scal(rt->ray->dir, rt->sphere_ray->o);

	if (OH >= 0)
	{
		double CHCH, RR;

		CHCH = pow(ft_norm_2(rt->sphere_ray->o),2) - (OH * OH);
		RR = rt->sphere->radius * rt->sphere->radius;

		if (CHCH <= RR)
		{
			double dd, ta, tb;

			dd = RR - CHCH;
			ta = ft_norm(rt->ray->dir, rt->sphere_ray->o) + sqrt(dd);
			tb = ft_norm(rt->ray->dir, rt->sphere_ray->o) - sqrt(dd);

			if (ta >= tb)
			{
				return(tb);
			}
			return(ta);
		}
	}
	return(0);
	/*a = pow(rt->ray->dir->x, 2) + pow(rt->ray->dir->y, 2) + pow(rt->ray->dir->z, 2);
	b = 2 * (rt->ray->dir->x * (rt->ray->o->x - rt->sphere->o->x) + rt->ray->dir->y * (rt->ray->o->y
	- rt->sphere->o->y) + rt->ray->dir->z * (rt->ray->o->z - rt->sphere->o->z));
	c = (pow(rt->ray->o->x - rt->sphere->o->x, 2) + pow(rt->ray->o->y - rt->sphere->o->y, 2)
	+ pow(rt->ray->o->z - rt->sphere->o->z, 2)) - pow(rt->sphere->radius, 2);
	det = b * b - 4 * a * c;
	if (det >= 0)
	{
		if (((-b - sqrt(det)) / (2 * a)) > ((-b + sqrt(det)) / (2 * a)))
			return ((-b + sqrt(det)) / (2 * a));
		return (((-b - sqrt(det)) / (2 * a)));
	}

	return (0);*/
}

void			ft_check_object(t_rt *rt)
{
/*	color = ft_check_plane(rt);
	if (color != 0x000000)
		return (color);*/
	rt->dst = ft_check_sphere(rt);
	if (rt->dst <= 0.01)
		rt->dst = 0;
	rt->color = rt->zcolor;
	if (rt->dst != 0)
	{	rt->color = rt->sphere->color;
		ft_get_point(rt);
		ft_get_light(rt);
	}
	return ;
}
