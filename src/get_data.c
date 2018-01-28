
#include "../rtv1.h"

int			tab_len(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

t_coo		*get_coo(char **str, int err)
{
	t_coo	*coo;

	if (tab_len(str) != 4)
		ft_bad_arg(err);
	if (!(coo = (t_coo*)malloc(sizeof(t_coo))))
		ft_malloc_error();
	coo->x = ft_atodouble(str[1]);
	coo->y = ft_atodouble(str[2]);
	coo->z = ft_atodouble(str[3]);
	return (coo);
}

t_material	*get_color(char **str)
{
	t_material		*color;

	if (tab_len(str) != 4)
		ft_bad_arg(3);
	if (!(color = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	color->r = ft_atodouble(str[1]);
	color->g = ft_atodouble(str[2]);
	color->b = ft_atodouble(str[3]);
	if (color->r < 0 || color->g < 0 || color->b < 0)
	{
		ft_putstr("Please use valid colors.\n");
		exit(-1);
	}	
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
	return (color);
}

double		get_radius(char **str)
{
	double		radius;

	if (tab_len(str) != 2)
		ft_bad_arg(4);
	radius = ft_atodouble(str[1]);
	if (radius < 0)
	{
		ft_putstr("Please use valid radius\n");
		exit(-1);
	}
	return (radius);
}