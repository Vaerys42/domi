#include "../rtv1.h"

double		cylinder_dst_rslt( double a, double b, double c)
{
	double	ta;
	double	tb;

	ta = (- b - sqrt((b * b) - (4 * a * c))) / (2 * a);
	tb = (- b + sqrt((b * b) - (4 * a * c))) / (2 * a);;

	if (ta > tb && tb > 0)
		return(tb);
	return(ta);
}

double		ft_check_cylinder(t_cylinder *cylinder, t_ray *ray)
{
  t_coo cyl_o;
	double		a;
	double		b;
	double		c;

  cyl_o.x = (ray->o->x - cylinder->o->x);
  cyl_o.y = (ray->o->y - cylinder->o->y);
  cyl_o.z = (ray->o->z - cylinder->o->z);

  a = pow(ray->dir->x, 2) + pow(ray->dir->z, 2);
	b = 2 * cyl_o.x * ray->dir->x + 2 * cyl_o.z * ray->dir->z;
  c = pow(cyl_o.x, 2) + pow(cyl_o.z, 2) - pow(cylinder->radius,2);
	if (a == 0)
		return(- c / b);
	if ((b * b - (4 * a * c)) < 0)
		return(0);
	return(cylinder_dst_rslt(a, b, c));
}

void		new_cylinder_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		rt->inter->obj = CYL;
	if (type == 1 && rt->inter->obj == CYL)
	{
    		move_color(rt->inter->mat, rt->cylinder->color->r, rt->cylinder->color->g,
    		rt->cylinder->color->b);
		rt->inter->angle->dir->x = rt->inter->point->x - rt->cylinder->o->x;
		rt->inter->angle->dir->y = rt->inter->point->y;
		rt->inter->angle->dir->z = rt->inter->point->z - rt->cylinder->o->z;
		rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
	}
}

void				check_cylinder_inter(t_rt *rt, int type)
{
  double tmp;

	if (rt->start->cyl != NULL)
	{
    rt->cylinder = rt->start->cyl;
    while (rt->cylinder != NULL)
		{
			if (type == 0)
          tmp = ft_check_cylinder(rt->cylinder, rt->ray);
      else
          tmp = ft_check_cylinder(rt->cylinder, rt->light_ray);
      if (tmp > 0.01 && tmp < rt->inter->dst)
        new_cylinder_dst(rt, type, tmp);
        rt->cylinder = rt->cylinder->next;
    }
  }
}
