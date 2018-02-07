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

t_coo		*ft_rotation(t_coo *vect, t_coo *rot)
{
	t_coo		*new;
  
	if (!(new = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
  rot = ft_mult_vect(M_PI / 180, rot);
  if (rot->x != 0)
  {
    new->x = vect->x;
    new->y = vect->y * cos(rot->x) - vect->z * sin(rot->x);
    new->z = vect->y * sin(rot->x) + vect->z * cos(rot->x);
  }
  if (rot->y != 0)
  {
    new->x = vect->x * cos(rot->y) + vect->z * sin(rot->y);
    new->y = vect->y;
    new->z = - vect->x * sin(rot->y) + vect->z * cos(rot->y);
  }
  if (rot->z != 0)
  {
    new->x = vect->x * cos(rot->z) - vect->y * sin(rot->z);
    new->y = vect->x * sin(rot->z) + vect->y * cos(rot->z);
    new->z = vect->z;
  }
	return (new);
}
