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

void		move_color(t_material *c, double r, double g, double b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void		ft_get_point(t_rt *rt)
{
	rt->inter->point = ft_mult_vect(rt->inter->dst, rt->ray->dir);
	rt->inter->point = ft_add_vect(rt->cam->pos, rt->inter->point);
}

void		ft_get_light(t_rt *rt)
{
	double		angle;

	rt->inter->dst = 99999;
	move_color(rt->inter->mat, 0.0, 0.0, 0.0);
	rt->light_ray->o = rt->light->o;
	rt->light_ray->dir = ft_normalize(ft_sub_vect(rt->inter->point, rt->light->o));
	check_sphere_inter(rt, 1);
	check_plane_inter(rt, 1);

	angle = -scal(rt->light_ray->dir, rt->inter->angle->dir);
	angle = (angle < 0.1) ? 0.1 : angle;
	rt->inter->mat->r = rt->inter->mat->r * rt->light->color->r * angle * rt->light->power;
	rt->inter->mat->g = rt->inter->mat->g * rt->light->color->g * angle * rt->light->power;
	rt->inter->mat->b = rt->inter->mat->b * rt->light->color->b * angle * rt->light->power;
}

void			ft_check_object(t_rt *rt)
{
	rt->inter->dst = 99999;
	rt->inter->angle->dir = rt->ray->dir;
	check_sphere_inter(rt, 0);
	check_plane_inter(rt, 0);
	//check_cone_inter(rt, 0);
	if (rt->inter->dst <= 0.01)
		rt->inter->dst = 0;
	if (rt->inter->dst != 0)
	{
		ft_get_point(rt);
		ft_get_light(rt);
	}
	return ;
}
