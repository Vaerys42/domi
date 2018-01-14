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

	rt->color->r = rt->light->color->r * angle * rt->light->power;
	rt->color->g = rt->light->color->g * angle * rt->light->power;
	rt->color->b = rt->light->color->b * angle * rt->light->power;
}

double				ft_check_plane(t_rt *rt)
{
	double		dst;

	dst = ((scal(rt->plane->norm, rt->cam->pos) + rt->plane->supp)
	/ (scal(rt->plane->norm, rt->ray->dir)));
	return (dst);
}

double				ft_check_sphere(t_rt *rt)
{
	double OH;
	double CHCH;
	double RR;
	double ta;
	double tb;

	rt->sphere_ray->o = ft_sub_vect(rt->sphere->o, rt->cam->pos);
	OH = scal(rt->ray->dir, rt->sphere_ray->o);
	if (OH >= 0)
	{
		CHCH = pow(ft_norm_2(rt->sphere_ray->o),2) - (OH * OH);
		RR = rt->sphere->radius * rt->sphere->radius;
		if (CHCH <= RR)
		{
			ta = ft_norm(rt->ray->dir, rt->sphere_ray->o) + sqrt(RR - CHCH);
			tb = ft_norm(rt->ray->dir, rt->sphere_ray->o) - sqrt(RR - CHCH);
			if (ta >= tb)
				return(tb);
			return(ta);
		}
	}
	return(0);
}

void			ft_check_object(t_rt *rt)
{
	double tmp;

	rt->dst = ft_check_sphere(rt);
	tmp = ft_check_plane(rt);
	if (tmp < 0)
		printf("%f\n", tmp);
	/*if (tmp < rt->dst)
		rt->dst = tmp;*/
	if (rt->dst <= 0.01)
		rt->dst = 0;
	rt->color = rt->zcolor;
	if (rt->dst != 0)
	{
		rt->color = rt->sphere->color;
		ft_get_point(rt);
		ft_get_light(rt);
	}
	return ;
}
