/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 22:26:16 by kboucaud          #+#    #+#             */
/*   Updated: 2018/02/15 22:26:19 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		ft_cam_info(t_cam *cam)
{
	if (cam->pos == NULL)
		ft_putstr("Needs origin coordinate for cam. Ex : coo: 1 2 5\n");
	else if (cam->rot == NULL)
		ft_putstr("Needs rotation for the cam. Ex rot: 0 90 0 (In degres,\
		0 0 0 for no rot)\n");
	else
		return ;
	exit(-1);
}

t_cam		*ini_cam(void)
{
	t_cam		*cam;

	if (!(cam = (t_cam*)malloc(sizeof(t_cam))))
		ft_malloc_error();
	cam->pos = NULL;
	cam->rot = NULL;
	return (cam);
}

int			cam_lst(t_rt *rt, t_cam *cam)
{
	ft_cam_info(cam);
	rt->cam = cam;
	return (1);
}

int			ft_add_cam(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cam		*cam;

	cam = ini_cam();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (datas[0] == 0)
			ret++;
		if (ft_strcmp(datas[0], "coo:") == 0)
			cam->pos = get_coo(datas, 2);
		else if (ft_strcmp(datas[0], "rot:") == 0)
			cam->rot = get_coo(datas, 7);
		else if (ft_check_obj(datas[0], fd, rt) == 1)
			ret++;
		else
			ft_bad_arg(5);
		ft_freetab(datas);
		free(line);
	}
	return (cam_lst(rt, cam));
}
