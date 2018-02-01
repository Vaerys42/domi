/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:58:48 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 18:58:50 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

double			ft_check_cone(t_cone *cone, t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	double	det;
	t_coo	*co;

	co = ft_sub_vect(cone->o, ray->o);
	a = pow(scal(ray->dir, cone->dir), 2) - pow(cos(cone->angle), 2);
	b = 2 * (scal(ray->dir, cone->dir) * scal(co, cone->dir) - (scal(ray->dir, co)) * pow(cos(cone->angle), 2));
	c = pow(scal(co, cone->dir), 2) - (scal(co, co) * pow(cos(cone->angle), 2));
	det = (b * b) - (4 * a * c);
	if (det < 0)
		return (0);
	if ((-b - sqrt(det) / (2 * a)) > (-b + sqrt(det) / (2 * a)) && (-b + sqrt(det) / (2 * a)) > 0)
		return (-b + sqrt(det) / (2 * a));
	return (-b - sqrt(det) / (2 * a));
}

void			check_cone_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->con != NULL)
	{
		rt->cone = rt->start->con;
		while (rt->cone != NULL)
		{
			if (type == 0)
				tmp = ft_check_cone(rt->cone, rt->ray);
			else
				tmp = ft_check_cone(rt->cone, rt->light_ray);
			if (tmp < rt->inter->dst && tmp > 0)
			{
				rt->inter->dst = tmp;
				if (type == 0)
					rt->inter->obj = CON;
				if (type == 1 && rt->inter->obj == CON)
				{
					move_color(rt->inter->mat, rt->cone->color->r, rt->cone->color->g, rt->cone->color->b);
					/*rt->inter->angle->dir = rt->ray->dir;
					rt->inter->angle->dir->x = rt->inter->point->x - rt->cone->o->x;
          			rt->inter->angle->dir->y = rt->inter->point->y;
         			rt->inter->angle->dir->z = rt->inter->point->z - rt->cone->o->z;
         			rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);*/
				}
			}
			rt->cone = rt->cone->next;
		}
	}
}
