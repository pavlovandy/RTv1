/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:43:37 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/02 15:43:38 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <fcntl.h>
# include "../libft/libft.h"
# include <math.h>
# include <pthread.h>
# ifdef __APPLE__
#  include "../frameworks/SDL2.framework/Headers/SDL.h"
# else
#  include <SDL2/SDL.h>
# endif
# include <stdio.h>
# include "terminal_colors.h"

# define WIN_WIDTH	800
# define WIN_HEIGHT	600
# define MAX_OBJ_COUNT 10
# define MAX_LIGHTING_COUNT 10
# define RGB(v) (((int)v[0] << 16) + ((int)v[1] << 8) + (int)v[2])
# define ROTATION_SPEED 0.1
# define TRANSLATE_SPEED 0.1
# define DIFFERENT_OBJ 4
# define EDITOR 96

# define D	1
# define VW	(1.155)
# define VH	(VW * WIN_HEIGHT / WIN_WIDTH)

# define BIG_VALUE 9e9

typedef	struct s_fig	t_fig;
typedef	struct s_sdl	t_sdl;
typedef	struct s_scene	t_scene;
typedef	struct s_rt		t_rt;
typedef	struct s_pov	t_pov;

typedef	double	t_vector __attribute__((vector_size(sizeof(double)*4)));

enum	e_fig
{
	SPHERE = 0, PLANE, CONE, CYLIN
};
enum	e_light
{
	AMBIENT = 0, DIRECT, POINT
};

typedef struct	s_roots
{
	double	t1;
	double	t2;
}				t_roots;

typedef struct	s_sphere_data
{
	t_vector	cent;
	double		radius;
	t_vector	color;
	int			specular;
}				t_sphere_data;

typedef struct	s_plane_data
{
	t_vector	normal;
	t_vector	dot;
	t_vector	color;
	int			specular;
}				t_plane_data;

typedef struct	s_cone_data
{
	t_vector	vertex;
	t_vector	dir;
	double		tangent;
	t_vector	color;
	int			specular;
}				t_cone_data;

typedef struct	s_cylin_data
{
	t_vector	dir;
	t_vector	dot;
	t_vector	color;
	double		radius;
	int			specular;
}				t_cylin_data;

struct	s_fig
{
	int		fig_type;
	void	*data;
};

struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*win_sur;
};

struct	s_pov
{
	t_vector	coord;
	t_vector	dir;
	double		cx;
	double		cy;
	double		sx;
	double		sy;
};

typedef struct	s_light
{
	char		*type;
	int			type_num;
	double		intensity;
	t_vector	v;
}				t_light;

struct	s_scene
{
	int			count_obj;
	t_fig		obj[MAX_OBJ_COUNT];
	int			count_light;
	t_light		light[MAX_LIGHTING_COUNT];
};

typedef	struct	s_pixel_cal
{
	t_vector	normal;
	t_vector	light_dir;
	t_vector	eye_point;
	t_vector	color;
	t_vector	to_eye_dir;
	t_vector	intersect_point;
	t_vector	reflected_ray;
	t_vector	eye_point_dir;
	int			closest_obj;
	double		closest_dist;
	t_roots		roots;
	double		intensity;
	double		scalar;
	int			specular;
	int			t_min;
	int			t_max;
	int			sign;

	double		a;
	double		b;
	double		c;
	double		d;
	double		dp_x_v;
	double		dp_d_v;
	t_vector	oc;
}				t_pixel_cal;

typedef	t_roots	(*intersect_fun)(t_vector, t_vector, void*, t_pixel_cal *);

typedef struct	s_fun
{
	intersect_fun	inter_f[DIFFERENT_OBJ];
}				t_fun;

struct	s_rt
{
	t_sdl	sdl;
	t_scene	scene;
	t_pov	pov;
	t_fun	fun;
	int		editing;
};

//function
double		str_to_double(char *line);
int			get_coord_value(char *line, t_vector *vec);
int			read_hex(char *line);
t_vector	trim_color(t_vector color);

//math
double		dot_prod(t_vector v1, t_vector v2);
t_vector	vector_prod(t_vector v1, t_vector v2);
double		vect_len(t_vector a);
t_vector	multi_vect(t_vector a, double multi);
t_vector	rotate_around_x_y(t_vector a, t_pov	pov);
t_vector	ft_rotate_camera(t_vector direction, t_pov *pov);
int			make_unit_vector(t_vector *v);

//sphere roots
t_roots		sphere_roots(t_vector view_point, t_vector view_port, \
												void *data, t_pixel_cal *pc);
void		sphere_cal(t_pixel_cal *pc, t_sphere_data *data);
t_roots		plane_roots(t_vector view_point, t_vector view_port, \
												void *data, t_pixel_cal *pc);
void		plane_cal(t_pixel_cal *pc, t_plane_data *data);
t_roots		cone_roots(t_vector view_point, t_vector view_port, \
												void *data, t_pixel_cal *pc);
void		cone_cal(t_pixel_cal *pc, t_cone_data *data);
t_roots		cylin_roots(t_vector view_point, t_vector view_port, \
												void *data, t_pixel_cal *pc);
void		cylin_cal(t_pixel_cal *pc, t_cylin_data	*cylin);

//output
int			put_usage(void);
int			error_message(char *msg);
void		print_scene_data(t_scene *sc);

//parser
int			read_scene(char *file, t_rt *rt);
int			read_sphere_data(int fd, t_sphere_data	*data);
int			read_plane_data(int fd, t_plane_data *data);
int			read_pov_data(int fd, t_pov *pov);
int			read_light_data(int fd, t_light *light);
int			read_cylin_data(int fd, t_cylin_data *data);
int			read_cone_data(int fd, t_cone_data *data);

int			check_line_for_char(int fd, char c);
int			check_line_for_coord(int fd, t_vector *coord, char *data_mark);
int			check_line_for_value(int fd, double *value, char *value_mark);
int			check_line_for_int_value(int fd, int *value, char *value_mark);
int			check_line_for_color(int fd, Uint32 *color);
int			check_line_for_string(int fd, char **str, char *str_mark);

int			sphere_routine(int fd, t_rt *rt);
int			plane_routine(int fd, t_rt *rt);
int			light_routine(int fd, t_rt *rt);
int			cylin_routine(int fd, t_rt *rt);
int			cone_routine(int fd, t_rt *rt);

//init
int			sdl_init(t_sdl *sdl);
int			config_intersect_function(t_rt *rt);

//render
void		put_pixel(int x, int y, Uint32 color, SDL_Surface *surr);
Uint32		get_pixel(int x, int y, SDL_Surface *surr);
t_vector	canvas_to_viewport(int x, int y);

void		start_render(t_rt *rt);
double		calculate_lighting(t_pixel_cal *pc, t_rt *rt);

//user events
int			user_commands(t_rt *rt);
int			there_will_be_loop(t_rt *rt);

//editor
int			change_scene(t_rt *rt);
int			change_light(t_light *light, int key);
int			change_obj(t_fig *fig, int key);
int			change_sphere(t_sphere_data *sphere, int key);
int			change_plane(t_plane_data *plane, int key);
int			change_cylin(t_cylin_data *cylin, int key);
int			change_cone(t_cone_data *cone, int key);
void		check_closest_inter(t_rt *rt, t_pixel_cal *pc);

#endif
