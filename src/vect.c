/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 03:32:16 by kboucaud          #+#    #+#             */
/*   Updated: 2017/12/04 03:32:18 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_coo		*ft_new_vect(float x, float y, float z)
{
	t_coo		*new;

	if (!(new = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

t_coo		*ft_normalize(t_coo *vect)
{
	double		norm;
	t_coo		*new;

	if (!(new = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	norm = ft_norme(vect);
	new = ft_div_vect(norm, vect);
	return (new);
}

double		ft_norme(t_coo *vect)
{
	double	rslt;

	rslt = sqrt(vect->x * vect->x + vect->y * vect->y + vect->z * vect->z);
	return (rslt);
}

t_coo		*ft_div_vect(double i, t_coo *vect)
{
	if (i == 0)
		return (vect);
	return (ft_new_vect(vect->x / i, vect->y / i, vect->z / i));
}

double		ft_dst(t_coo *vect1, t_coo *vect2)
{
	double		rslt;

	rslt = sqrt(pow(vect2->x - vect1->x, 2) +
	pow(vect2->y - vect1->y, 2) + pow(vect2->z - vect1->z, 2));
	return (rslt);
}

t_coo		*ft_mult_vect(double i, t_coo *vect)
{
	return (ft_new_vect(i * vect->x, i * vect->y, i * vect->z));
}

t_coo		*ft_add_vect(t_coo *vect1, t_coo *vect2)
{
	t_coo	*new;

	if (!(new = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	new->x = vect1->x + vect2->x;
	new->y = vect1->y + vect2->y;
	new->z = vect1->z + vect2->z;
	return (new);
}

t_coo		*ft_sub_vect(t_coo *vect1, t_coo *vect2)
{
	return (ft_new_vect(vect1->x - vect2->x, vect1->y - vect2->y, vect1->z - vect2->z));
}

double		scal(t_coo *v1, t_coo *v2)
{
	double		rslt;

	rslt = (v1->x * v2->x) + v1->y * v2->y + v1->z * v2->z;
	return (rslt);
}
