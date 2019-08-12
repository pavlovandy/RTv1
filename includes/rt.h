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
# ifdef	__APPLE__
#  include "../frameworks/SDL2.framework/Headers/SDL.h"
# else
#  include <SDL2/SDL.h>
# endif
# include <stdio.h>
# include "./terminal_colors.h"

# define WIN_WIDTH	1200
# define WIN_HEIGHT	720
# define MAX_OBJ_COUNT 10
# define MAX_LIGHTING_COUNT 10
# define RGB(v) (((int)v[0] << 16) + ((int)v[1] << 8) + (int)v[2])
# define ROTATION_SPEED 0.01
# define TRANSLATE_SPEED 0.1

# define D	1
# define VW	(1.4)
# define VH	(0.8)


# define BIG_VALUE 9e9

typedef	struct s_fig	t_fig;
typedef	struct s_sdl	t_sdl;
typedef	struct s_scene	t_scene;
typedef	struct s_rt		t_rt;
typedef	struct s_pov	t_pov;
typedef	float t_vector	__attribute__ ((vector_size(sizeof(float) * 4)));
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
	float	t1;
	float	t2;
}				t_roots;

typedef struct	s_sphere_data
{
	t_vector	cent;
	float		radius;
	t_vector	color;
	int			specular;
}				t_sphere_data;

typedef struct	s_plane_data //change this
{
	t_vector	normal;
	float		h;
	t_vector	color;
	int			specular;
}				t_plane_data;

typedef struct	s_cone_data
{

}				t_cone_data;

typedef struct	s_cylin_data
{

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
	float		cx;
	float		cy;
	float		sx;
	float		sy;
};

typedef struct	s_light
{
	char		*type;
	int			type_num;
	float		intensity;
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
	t_vector	n;
	t_vector	l;
	t_vector	o;
	t_vector	color;
	t_vector	v;
	t_vector	p;
	t_vector	r;
	int			closest_obj;
	float		closest_dist;
	t_roots		roots;
	float		intensity;
	float		scalar;
	int			specular;
}				t_pixel_cal;

struct	s_rt
{
	t_sdl	sdl;
	t_scene	scene;
	t_pov	pov;

};

//function
double		str_to_double(char *line);
int			get_coord_value(char *line, t_vector *vec);
int			read_hex(char *line);

//math
float		dot_prod(t_vector v1, t_vector v2);
t_vector	vector_prod(t_vector v1, t_vector v2);
float		vect_len(t_vector a);
t_vector	multi_vect(t_vector a, float multi);
t_vector	rotate_around_x_y(t_vector a, t_pov	pov);
t_vector	ft_rotate_camera(t_vector direction, t_pov *pov);

//sphere roots
t_roots		sphere_roots(t_vector view_point, t_vector view_port, t_sphere_data *sphere);


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

int			check_line_for_char(int fd, char c);
int			check_line_for_coord(int fd, t_vector *coord, char *data_mark);
int			check_line_for_value(int fd, float *value, char *value_mark);
int			check_line_for_int_value(int fd, int *value, char *value_mark);
int			check_line_for_color(int fd, Uint32 *color);
int			check_line_for_string(int fd, char **str, char *str_mark);

//init
int			sdl_init(t_sdl *sdl);

//render
void		put_pixel(int x, int y, Uint32 color, SDL_Surface *surr);
Uint32		get_pixel(int x, int y, SDL_Surface *surr);

void		start_render(t_rt *rt);
float		calculate_lighting(t_pixel_cal *pc, t_rt *rt);

//user events
int			user_commands(t_rt *rt);
int			there_will_be_loop(t_rt *rt);

#endif
