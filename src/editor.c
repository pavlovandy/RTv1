/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 03:53:04 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/14 03:53:04 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			change_light(t_light *light, int key)
{
	if (key == SDLK_l)
		light->intensity += 0.01;
	if (key == SDLK_w)
		light->v[1] += 0.01;
	if (key == SDLK_s)
		light->v[1] -= 0.01;
	if (key == SDLK_q)
		light->v[0] += 0.01;
	if (key == SDLK_a)
		light->v[0] -= 0.01;
	if (key == SDLK_e)
		light->v[2] += 0.01;
	if (key == SDLK_d)
		light->v[2] -= 0.01;
	if (key == SDLK_d || key == SDLK_e || key == SDLK_a || key == SDLK_q ||\
				 key == SDLK_s || key == SDLK_w || key == SDLK_l)
		return (1);
	return (0);
}

int			change_obj(t_fig *fig, int key)
{
	if (fig->fig_type == SPHERE)
		return (change_sphere(fig->data, key));
	else if (fig->fig_type == PLANE)
		return (change_plane(fig->data, key));
	else if (fig->fig_type == CONE)
		return (change_cone(fig->data, key));
	else if (fig->fig_type == CYLIN)
		return (change_cylin(fig->data, key));
	return (0);
}

int			focus_the_obj(t_rt *rt)
{
	int			x;
	int			y;
	t_pixel_cal	pc;

	SDL_GetMouseState(&x, &y);
	pc.eye_point_dir = canvas_to_viewport(x, y);
	//pc.eye_point_dir = ft_rotate_camera(d, &rt->pov);
	pc.eye_point = rt->pov.coord;
	check_closest_inter(rt, &pc);
	return (pc.closest_obj);
}

int			change_scene(t_rt *rt)
{
	SDL_Event	ev;
	int			change;
	int			num;

	change = 0;
	num = 0;
	while (SDL_PollEvent(&ev) && rt->editing)
	{
		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_ESCAPE)
				exit(0);
			else if (ev.key.keysym.sym == EDITOR)
				rt->editing = 0;
			else if (num != -1)
				change_obj(rt->scene.obj + num, ev.key.keysym.sym);
		}
		else if (ev.type == SDL_QUIT)
			exit(0);
		else if (ev.type == SDL_MOUSEBUTTONDOWN)
			num = focus_the_obj(rt);
	}
	return (change);
}
