#include "../rtv1.h"

double		cone_dst_rslt( double a, double b, double c)
{
	double	ta;
	double	tb;

	ta = (- b - sqrt((b * b) - (4 * a * c))) / (2 * a);
	tb = (- b + sqrt((b * b) - (4 * a * c))) / (2 * a);;

	if (ta > tb && tb > 0)
		return(tb);
	return(ta);
}

double		ft_check_cone(t_cone *cone, t_ray *ray)
{
  t_coo con_o;
	double		a;
	double		b;
	double		c;

	con_o.x = (ray->o->x - cone->o->x);
	con_o.y = (ray->o->y - cone->o->y);
	con_o.z = (ray->o->z - cone->o->z);
	a = pow(ray->dir->x, 2) - pow(tan(cone->angle),2) * pow(ray->dir->y, 2)
	+ pow(ray->dir->z, 2);
	b = (2 * con_o.x * ray->dir->x) - (2 * pow(tan(cone->angle),2) *
  con_o.y * ray->dir->y) + (2 * con_o.z * ray->dir->z);
	c = pow(con_o.x, 2) - pow(tan(cone->angle),2) * pow(con_o.y, 2) +
		pow(con_o.z, 2);
	if (a == 0)
		return(-c / b);

	if ((b * b - (4 * a * c)) < 0)
		return(0);

	return(cone_dst_rslt(a, b, c));
}

void		new_cone_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		rt->inter->obj = CON;
	if (type == 1 && rt->inter->obj == CON)
	{
    move_color(rt->inter->mat, rt->cone->color->r, rt->cone->color->g,
    rt->cone->color->b);
    rt->inter->angle->dir->x = rt->inter->point->x - rt->cone->o->x;
    rt->inter->angle->dir->y = rt->inter->point->y;
    rt->inter->angle->dir->z = rt->inter->point->z - rt->cone->o->z;
    rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
	}
}

void				check_cone_inter(t_rt *rt, int type)
{
  double tmp;

	if (rt->start->con != NULL)
	{
    rt->cone = rt->start->con;
    while (rt->cone != NULL)
		{
			if (type == 0)
          tmp = ft_check_cone(rt->cone, rt->ray);
      else
          tmp = ft_check_cone(rt->cone, rt->light_ray);
      if (tmp > 0.01 && tmp < rt->inter->dst)
        new_cone_dst(rt, type, tmp);
        rt->cone = rt->cone->next;
    }
  }
}
