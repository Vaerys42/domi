/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:00:38 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 19:00:41 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

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

void				new_plane_dst(t_rt *rt)
{
	move_color(rt->inter->mat, rt->plane->color->r,
	rt->plane->color->g, rt->plane->color->b);
	rt->inter->angle->dir = rt->plane->norm;
}

void				check_plane_inter(t_rt *rt, int type)
{
	double		tmp;

	if (rt->start->pln != NULL)
	{
		rt->plane = rt->start->pln;
		while (rt->plane != NULL)
		{
			if (type == 0)
				tmp = ft_check_plane(rt->plane, rt->ray);
			else
				tmp = ft_check_plane(rt->plane, rt->light_ray);
			if (tmp > 0 && tmp < rt->inter->dst)
			{
				rt->inter->dst = tmp;
				if (type == 0)
					rt->inter->obj = PLN;
				if (type != 0 && rt->inter->obj == PLN)
					new_plane_dst(rt);
			}
			rt->plane = rt->plane->next;
		}
	}
}
