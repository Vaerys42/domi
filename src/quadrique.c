/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect * c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42 * fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 03:32:16 by kboucaud          #+#    #+#             */
/*   Updated: 2017/12/04 03:32:18 by kboucaud         ###   ######## * fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

double ft_shorter(double aq, double bq, double cq)
{
	double	ta;
	double	tb;

	ta = (- bq - sqrt((bq * bq) - (4 * aq * cq))) / (2 * aq);
	tb = (- bq + sqrt((bq * bq) - (4 * aq * cq))) / (2 * aq);
	if (ta > tb && tb > 0)
		return(tb);
	return(ta);
}

double ft_quad_dst(t_ray *ray, t_quad *quad)
{
	quad->aq = (quad->tab[0] * pow(DX, 2)) + (quad->tab[1] * pow(DY, 2))
	+ (quad->tab[2] * pow(DZ, 2)) + (quad->tab[3] * DX * DY) +
	(quad->tab[4] * DX * DZ) + (quad->tab[5] * DY * DZ);
	quad->bq = (2 * quad->tab[0] * QX * DX) + (2 * quad->tab[1] * QY * DY) + (2 *
	quad->tab[2] * QZ * DZ) + (quad->tab[3] * (QX * DY + QY * DX))
	+ (quad->tab[4] * (QX * DZ + DX * QZ)) + (quad->tab[5] *
	(QY * DZ + DY * QZ)) + (quad->tab[6] * DX) + (quad->tab[7] *
	DY) + (quad->tab[8] * DZ);
	quad->cq = (quad->tab[0] * pow(QX, 2)) + (quad->tab[1] * pow(QY, 2)) +
	(quad->tab[2] * pow(QZ, 2)) + (quad->tab[3] * QX * QY) + (quad->tab[4] * QX * QZ)
	+ (quad->tab[5] * QY * QZ) + (quad->tab[6] * QX) +
	(quad->tab[7] * QY) + (quad->tab[8] * QZ) + quad->tab[9];
	if (quad->aq == 0)
		return(- quad->cq / quad->bq);
	if ((quad->bq * quad->bq - (4 * quad->aq * quad->cq)) < 0)
		return(0);
	return(ft_shorter(quad->aq, quad->bq, quad->cq));
}

t_coo		*ft_quad_norm(t_coo *vect1, t_quad *quad)
{
	t_coo	*new;
	if (!(new = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	new->x = (2 * quad->tab[0] * vect1->x) + (quad->tab[3] * vect1->y) + (quad->tab[4] * vect1->z) + quad->tab[6];
	new->y = (2 * quad->tab[1] * vect1->y) + (quad->tab[3] * vect1->x) + (quad->tab[5] * vect1->z) + quad->tab[7];
	new->z = (2 * quad->tab[2] * vect1->z) + (quad->tab[4] * vect1->x) + (quad->tab[5] * vect1->y) + quad->tab[8];
	return (new);
}
