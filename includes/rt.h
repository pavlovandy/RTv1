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

#ifndef	RT_H
# define RT_H

# include <fcntl.h>
# include "../libft/libft.h"
# include <math.h>
# include <pthread.h>
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include <stdio.h>

# define WIN_WIDTH	1200
# define WIN_HEIGHT	800
# define MAX_OBJ_COUNT 10

typedef	struct s_fig	t_fig;
typedef	struct s_vector	t_vector;
typedef	struct s_sdl	t_sdl;
typedef	struct s_scene	t_scene;
typedef	struct s_rt		t_rt;
typedef	struct s_pov	t_pov;

enum	fig{SPHERE = 0, PLANE, CONE, CYLIN};

struct	s_vector
{
	float	x;
	float	y;
	float	z;
};

typedef struct	s_sphere_data
{
	t_vector	cent;
	float		radius;
	Uint32		color;
}				t_sphere_data;

typedef struct	s_plane_data
{

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
};

struct	s_scene
{
	int		count_obj;
	t_fig	obj[MAX_OBJ_COUNT];
};

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
float		scalar_prod(t_vector v1, t_vector v2);
t_vector	vector_prod(t_vector v1, t_vector v2);

//output
int			put_usage(void);
int			error_message(char *msg);

//parser
int			read_scene(char *file, t_rt *rt);

//init
int			sdl_init(t_sdl *sdl);

//render
void		start_render(t_rt *rt);

#endif
