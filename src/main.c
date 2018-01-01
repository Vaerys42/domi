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

int			main(void)
{
	t_rt		*rt;

	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		ft_malloc_error();
	ft_ini(rt);
	ft_raytracing(rt);
	window(rt);
	return (0);
}
