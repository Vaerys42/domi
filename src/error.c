/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 18:47:45 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/02 18:47:47 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		ft_bad_arg(int i)
{
	if (i == 0)
		ft_putstr("bad number of arguments\n");
	else if (i == 1)
		ft_putstr("bad file : please use a valid file\n");
	exit(0);
}

void		ft_malloc_error(void)
{
	ft_putstr("malloc error\n");
	exit(0);
}

void		ft_exit(void)
{
	ft_putstr("error\n");
	exit(0);
}
