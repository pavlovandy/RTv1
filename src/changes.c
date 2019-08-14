/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 05:55:28 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/14 05:55:29 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		change_sphere(t_sphere_data *sphere, int key)
{
	const Uint8		*keystate = SDL_GetKeyboardState(NULL);

	if (key == SDLK_q)
		sphere->cent[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_w)
		sphere->cent[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_e)
		sphere->cent[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_r)
		sphere->radius += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_s)
		sphere->specular += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_z)
		sphere->color[0] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_x)
		sphere->color[1] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_c)
		sphere->color[2] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_c || key == SDLK_x || key == SDLK_z || key == SDLK_s || \
			key == SDLK_r || key == SDLK_e || key == SDLK_w || key == SDLK_q)
		return (1);
	return (0);
}

int		change_plane(t_plane_data *plane, int key)
{
	const Uint8		*keystate = SDL_GetKeyboardState(NULL);
	int		change;

	change = 0;
	if (key == SDLK_q && (change = 1))
		plane->normal[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_w && (change = 1))
		plane->normal[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_e && (change = 1))
		plane->normal[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_r && (change = 1))
		plane->dot[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_t && (change = 1))
		plane->dot[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_y && (change = 1))
		plane->dot[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_s && (change = 1))
		plane->specular += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_z && (change = 1))
		plane->color[0] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_x && (change = 1))
		plane->color[1] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_c && (change = 1))
		plane->color[2] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	return (change);
}

int		change_cylin(t_cylin_data *cylin, int key)
{
	const Uint8		*keystate = SDL_GetKeyboardState(NULL);
	int		change;

	change = 0;
	if (key == SDLK_q && (change = 1))
		cylin->dir[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_w && (change = 1))
		cylin->dir[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_e && (change = 1))
		cylin->dir[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_r && (change = 1))
		cylin->dot[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_t && (change = 1))
		cylin->dot[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_y && (change = 1))
		cylin->dot[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_s && (change = 1))
		cylin->specular += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_z && (change = 1))
		cylin->color[0] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_x && (change = 1))
		cylin->color[1] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_c && (change = 1))
		cylin->color[2] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	return (change);
}

int		change_cone(t_cone_data *cone, int key)
{
	const Uint8		*keystate = SDL_GetKeyboardState(NULL);
	int		change;

	change = 0;
	if (key == SDLK_q && (change = 1))
		cone->dir[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_w && (change = 1))
		cone->dir[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_e && (change = 1))
		cone->dir[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_r && (change = 1))
		cone->vertex[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_t && (change = 1))
		cone->vertex[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_y && (change = 1))
		cone->vertex[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_s && (change = 1))
		cone->specular += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_z && (change = 1))
		cone->color[0] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_x && (change = 1))
		cone->color[1] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	if (key == SDLK_c && (change = 1))
		cone->color[2] += keystate[SDL_SCANCODE_TAB] ? -5 : 5;
	return (change);
}
