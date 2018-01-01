/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 20:11:06 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/03 20:11:08 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void	put_pxl(t_data *data, int x, int y, t_icolor *color)
{
	int		i;

	if (x * 4 >= WIN_LEN * 4 || x * 4 < 0)
		return ;
	i = (x * 4) + (y * data->s_l);
	if (i > WIN_HEIGHT * WIN_LEN * 4)
		return ;
	data->image_string[i] = color->b;
	data->image_string[++i] = color->g;
	data->image_string[++i] = color->r;
}

void		ft_convert(t_rt *rt)
{
	rt->icolor->r = (rt->color->r * 255);
	rt->icolor->g = (rt->color->g * 255);
	rt->icolor->b = (rt->color->b * 255);
}

void		ft_ray(t_rt *rt, int x, int y)
{
	ft_check_object(rt);
	//if (rt->color->r == 0 && rt->color->g == 0 && rt->color->b == 0)
	//	return ;
	ft_convert(rt);
	put_pxl(rt->data, x, y, rt->icolor);
}

void		ft_ini_ray(t_rt *rt, int x, int y)
{

	rt->ray->dir = ft_sub_vect(ft_add_vect(rt->view->up_left, ft_mult_vect(rt->view->length * x / WIN_LEN, rt->cam->right)), ft_mult_vect(rt->view->height * y / WIN_HEIGHT, rt->cam->up));
	//rt->ray->dir = ft_sub_vect(rt->ray->o, rt->cam->pos);
	//rt->ray->dir = ft_sub_vect(rt->ray->dir, rt->cam->pos);
	rt->ray->dir = ft_div_vect(ft_norm_2(rt->ray->dir), rt->ray->dir);
}

void		ft_raytracing(t_rt *rt)
{
	int			x;
	int			y;

	y = -1;
	while (++y <= WIN_HEIGHT)
	//y = 350;
	//while (++y <= 450)
	{
		x = -1;
		while (++x <= WIN_LEN)
		//x = 450;
		//while (++x <= 550)
		{
			ft_ini_ray(rt, x, y);
			ft_ray(rt, x, y);
		}
	}
	mlx_put_image_to_window(rt->data->mlx, rt->data->mlx_window, rt->data->mlx_image, 0, 0);
}
