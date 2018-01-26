/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:33 by kboucaud          #+#    #+#             */
/*   Updated: 2017/10/21 01:09:43 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		window(t_rt *rt)
{
	mlx_hook(rt->data->mlx_window, 2, 1L << 0, my_key_press, rt);
	mlx_hook(rt->data->mlx_window, 17, 0, ft_exit_cross, rt);
	mlx_loop(rt->data->mlx);
}

void		ft_print(t_rt *rt)
{
	if (rt->start->con != NULL)
	{
		rt->cone = rt->start->con;
		while (rt->cone != NULL)
		{
			printf("cone: \n");
			printf("coo %f %f %f\n", rt->cone->o->x, rt->cone->o->y, rt->cone->o->z);
			printf("color %f %f %f\n", rt->cone->color->r, rt->cone->color->g, rt->cone->color->b);
			printf("angle %f\n", rt->cone->angle);
			rt->cone = rt->cone->next;
		}
	}
}

int			main(int argc, char **argv)
{
	t_rt		*rt;

	if (argc != 2)
		ft_bad_arg(0);
	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		ft_malloc_error();
	parser(rt, argv[1]);
	//ft_print(rt);
	ft_ini(rt);
	ft_raytracing(rt);
	window(rt);
	return (0);
}
