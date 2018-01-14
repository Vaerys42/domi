/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:26 by kboucaud          #+#    #+#             */
/*   Updated: 2017/10/21 03:59:13 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WIN_LEN 640
# define WIN_HEIGHT 480
# define PLN_DST 1.0
# define AMB_LIGHT 0.2

# include "libft/includes/libft.h"
# include "minilibx_macos/mlx.h"
# include "math.h"

typedef	struct 			s_material
{
	double				r;
	double				g;
	double				b;
}						t_material;

typedef struct 			s_icolor
{
	int 				r;
	int 				g;
	int 				b;
}						t_icolor;

typedef	struct			s_coo
{
	double				x;
	double				y;
	double				z;
}						t_coo;

typedef	struct			s_data
{
	void				*mlx;
	void				*mlx_window;
	void				*mlx_image;
	char 				*image_string;
	int					s_l;
	int					bpp;
	int					endian;
	int					*image_int;
}						t_data;

typedef struct 			s_cylinder
{
	t_coo				*o;
	double				radius;
	t_material			*color;
	double				height;
}						t_cylinder;

typedef	struct 			s_cone
{
	t_coo				*o;
	double				radius;
	t_material			*color;
	double				height;
	struct s_cone		*next;
}						t_cone;

typedef	struct 			s_sphere
{
	t_coo				*o;
	double				radius;
	t_material			*color;
	struct s_sphere		*next;
}						t_sphere;

typedef	struct 			s_plane
{
	t_material			*color;
	t_coo				*norm;
	t_coo 				*o;
	double				supp;
	struct s_plane		*next;
}						t_plane;

typedef struct 			s_light
{
	t_coo 				*o;
	t_material 			*color;
	double				power;
}						t_light;

typedef	struct 			s_ray
{
	t_coo				*o;
	t_coo				*dir;
}						t_ray;

typedef	struct 			s_cam
{
	t_coo				*pos;
	t_coo				*forw;
	t_coo				*up;
	t_coo				*right;
}						t_cam;

typedef	struct 			s_view
{
	double 				screen_ratio;
	double				height;
	double				length;
	t_coo				*up_left;
}						t_view;

typedef	struct			s_rt
{
	t_data				*data;
	t_ray				*ray;
	t_cam				*cam;
	t_light				*light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_view				*view;
	t_material			*color;
	t_icolor			*icolor;
	t_coo 				*inter;
	double				dst;
	t_ray				*light_ray;
	t_ray				*angle_ray;
}						t_rt;

void					ft_malloc_error(void);
void					ft_bad_arg(int i);
void					ft_exit(void);

void					ft_ini(t_rt *rt);

int						my_key_press(int key, t_rt *rt);
int						ft_exit_cross(t_rt *rt);
void					put_pxl(t_data *data, int x, int y, t_icolor *color);

void					ft_parser(char *path, t_rt *rt);
void					ft_create_sphere(t_rt *rt, char **line);

void					ft_raytracing(t_rt *rt);

void					ft_check_object(t_rt *rt);

t_coo					*ft_add_vect(t_coo *vect1, t_coo *vect2);
double					scal(t_coo *vect1, t_coo *vect2);
t_coo					*ft_mult_vect(double i, t_coo *vect);
t_coo					*ft_sub_vect(t_coo *vect1, t_coo *vect2);
double					ft_norm(t_coo *point1, t_coo *point2);
t_coo					*ft_div_vect(double i, t_coo *vect);
double					ft_norm_2(t_coo *vect);

void					zero_color(t_rt *rt);

#endif
