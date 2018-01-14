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

void	ft_create(t_rt *rt)
{
	if (!(rt->data = (t_data*)malloc(sizeof(t_data))))
		ft_malloc_error();
	if (!(rt->data->image_int = (int*)malloc(sizeof(int) * WIN_LEN * WIN_HEIGHT)))
		ft_malloc_error();
	if (!(rt->data->mlx = mlx_init()))
		ft_exit();
	if (!(rt->data->mlx_window = mlx_new_window(rt->data->mlx, WIN_LEN, WIN_HEIGHT, "RTV1")))
		ft_exit();
	if (!(rt->data->mlx_image = mlx_new_image(rt->data->mlx, WIN_LEN, WIN_HEIGHT)))
		ft_exit();
	if (!(rt->data->image_string = mlx_get_data_addr(rt->data->mlx_image, &rt->data->bpp, &rt->data->s_l, &rt->data->endian)))
		ft_exit();
	rt->data->image_int = (int*)rt->data->image_string;
}

void	ft_ini_sphere(t_rt *rt)
{
	if (!(rt->sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		ft_malloc_error();
	if (!(rt->sphere->o = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	if (!(rt->sphere->color = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	rt->sphere->radius = 2;
	rt->sphere->color->r = 0;
	rt->sphere->color->g = 1;
	rt->sphere->color->b = 0;
	rt->sphere->next = NULL;
	rt->sphere->o->x = 3;
	rt->sphere->o->y = 2;
	rt->sphere->o->z = 30.0;
}

void	ft_ini_plane(t_rt *rt)
{
	if (!(rt->plane = (t_plane*)malloc(sizeof(t_plane))))
		ft_malloc_error();
	if (!(rt->plane->norm = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	if (!(rt->plane->color = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->plane->o = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	rt->plane->color->r = 0;
	rt->plane->color->g = 0;
	rt->plane->color->b = 1;
	rt->plane->next = NULL;
	rt->plane->norm->x = 0;
	rt->plane->norm->y = 1;
	rt->plane->norm->z = 0;
	rt->plane->o->x = 0;
	rt->plane->o->y = 0;
	rt->plane->o->z = 0;
	rt->plane->supp = (-1) * rt->plane->o->x * rt->plane->norm->x +
	(-1) * rt->plane->o->y * rt->plane->norm->y +
	(-1) * rt->plane->o->z * rt->plane->norm->z;
}

void	ft_ini_viewplane(t_rt *rt)
{
	//double			focal;

	if (!(rt->view = (t_view*)malloc(sizeof(t_view))))
		ft_malloc_error();
	//focal = sqrt(WIN_LEN * WIN_LEN + WIN_HEIGHT * WIN_HEIGHT) / (2 * tan((90 * M_PI / 180) / 2));
	//rt->view->screen_ratio = (float)WIN_LEN / WIN_HEIGHT;
	rt->view->height = 0.35;
	rt->view->length = 0.5;
	rt->cam->pos->x = rt->view->length / 2;
	rt->cam->pos->y = rt->view->height / 2;
	rt->cam->pos->z = 0;
	rt->view->up_left =
	ft_add_vect(ft_mult_vect(PLN_DST, rt->cam->forw), ft_sub_vect(ft_mult_vect(rt->view->height
	/ 2, rt->cam->up), ft_mult_vect(rt->view->length / 2, rt->cam->right)));

}

void	ft_ini_cam(t_rt *rt)
{
	if (!(rt->cam = (t_cam*)malloc(sizeof(t_cam))))
		ft_malloc_error();
	if (!(rt->cam->pos = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
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
	rt->light->color->r = 1.0;
	rt->light->color->g = 0.0;
	rt->light->color->b = 1.0;
	rt->light->o->x = 0.0;
	rt->light->o->y = 0.0;
	rt->light->o->z = 25.0;
	rt->light->power = 1.0;
}

void	ft_ini(t_rt *rt)
{
	ft_create(rt);
	if (!(rt->ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->light_ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->angle_ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->sphere_ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->color = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->icolor = (t_icolor*)malloc(sizeof(t_icolor))))
		ft_malloc_error();
	if (!(rt->inter = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	if (!(rt->zcolor = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	rt->zcolor->r = 0.0;
	rt->zcolor->g = 0.0;
	rt->zcolor->b = 0.0;
	ft_ini_cam(rt);
	ft_ini_sphere(rt);
	ft_ini_plane(rt);
	ft_ini_light(rt);
}
