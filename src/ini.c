/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:42 by kboucaud          #+#    #+#             */
/*   Updated: 2017/10/21 01:09:54 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void	ft_ini_viewplane(t_rt *rt)
{
	if (!(rt->view = (t_view*)malloc(sizeof(t_view))))
		ft_malloc_error();
	rt->view->height = 35;
	rt->view->length = 50;
	rt->view->up_left = ft_add_vect(rt->cam->pos,
	ft_add_vect(ft_mult_vect(PLN_DST, rt->cam->forw), ft_sub_vect(ft_mult_vect(
	rt->view->height / 2, rt->cam->up), ft_mult_vect(rt->view->length / 2,
	rt->cam->right))));
}

void	ft_ini_cam(t_rt *rt)
{
	if (!(rt->cam->forw = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	if (!(rt->cam->up = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	if (!(rt->cam->right = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	rt->cam->forw->x = 0;
	rt->cam->forw->y = 0;
	rt->cam->forw->z = 1;
	rt->cam->up->x = 0;
	rt->cam->up->y = 1;
	rt->cam->up->z = 0;
	rt->cam->right->x = 1;
	rt->cam->right->y = 0;
	rt->cam->right->z = 0;
	ft_ini_viewplane(rt);
}

void	ft_ini_light(t_rt *rt)
{
	if (!(rt->light = (t_light*)malloc(sizeof(t_light))))
		ft_malloc_error();
	if (!(rt->light->o = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	if (!(rt->light->color = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	rt->light->color->r = 1;
	rt->light->color->g = 1;
	rt->light->color->b = 1;
	rt->light->o->x = 0.0;
	rt->light->o->y = 3.0;
	rt->light->o->z = 11.0;
	rt->light->power = 0.7;
}

void	ft_malloc_ini(t_rt *rt)
{
	ft_create(rt);
	if (!(rt->inter = (t_inter*)malloc(sizeof(t_inter))))
		ft_malloc_error();
	if (!(rt->ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->light_ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->inter->angle = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->inter->mat = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->inter->point = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
}

void	ft_ini(t_rt *rt)
{
	ft_malloc_ini(rt);
	ft_ini_cam(rt);
	ft_ini_light(rt);
	rt->ray->o = rt->cam->pos;
	rt->plane = rt->start->pln;
	rt->inter->obj = -1;
	rt->cone = rt->start->con;
	make_rot(rt);
}
