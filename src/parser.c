/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:50:21 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/02 17:50:23 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		ft_ini_struct(t_rt *rt)
{
	if (!(rt->start = (t_start*)malloc(sizeof(t_start))))
		ft_malloc_error();
	rt->sphere = NULL;
	rt->plane = NULL;
	rt->cone = NULL;
	rt->start->sph = NULL;
	rt->start->pln = NULL;
	rt->start->con = NULL;
}

void		parser(t_rt *rt, char *file)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_bad_arg(1);
	ft_ini_struct(rt);
	while ((ret = get_next_line(fd, &line)) > 0)
		ft_check_obj(line, fd, rt);
	if (ret == -1)
		ft_bad_arg(-1);
}