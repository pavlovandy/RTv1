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

int		change_sphere(t_sphere_data *sphere, int key, const Uint8 *keystate)
{
	int		change;

	change = 0;
	if (key == SDLK_q && (change = 1))
		sphere->cent[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_w && (change = 1))
		sphere->cent[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_e && (change = 1))
		sphere->cent[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_r && (change = 1))
		sphere->radius += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (sphere->radius < 0.2)
		sphere->radius = 0.2;
	change += change_color_and_specular(&sphere->color, \
		&sphere->specular, key, keystate);
	return (change);
}

int		change_plane(t_plane_data *plane, int key, const Uint8 *keystate)
{
	int		change;

	change = 0;
	if (key == SDLK_q && (change = 1))
		plane->normal[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_w && (change = 1))
		plane->normal[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_e && (change = 1))
		plane->normal[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	make_unit_vector(&plane->normal);
	if (key == SDLK_a && (change = 1))
		plane->dot[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_s && (change = 1))
		plane->dot[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_d && (change = 1))
		plane->dot[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	change += change_color_and_specular(&plane->color, \
		&plane->specular, key, keystate);
	return (change);
}

int		change_cylin(t_cylin_data *cylin, int key, const Uint8 *keystate)
{
	int		change;

	change = 0;
	if (key == SDLK_q && (change = 1))
		cylin->dir[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_w && (change = 1))
		cylin->dir[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_e && (change = 1))
		cylin->dir[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	make_unit_vector(&cylin->dir);
	if (key == SDLK_r && (change = 1))
		cylin->radius += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (cylin->radius < 0.2)
		cylin->radius = 0.2;
	if (key == SDLK_a && (change = 1))
		cylin->dot[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_s && (change = 1))
		cylin->dot[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_d && (change = 1))
		cylin->dot[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	change += change_color_and_specular(&cylin->color, \
		&cylin->specular, key, keystate);
	return (change);
}

int		change_color_and_specular(t_vector *color, int *specular, \
										int key, const Uint8 *keystate)
{
	int		change;

	change = 0;
	if (key == SDLK_z && (change = 1))
		*specular += keystate[SDL_SCANCODE_TAB] ? -20 : 20;
	if (*specular > 1000)
		*specular = 1000;
	if (key == SDLK_z && (change = 1))
		(*color)[0] += keystate[SDL_SCANCODE_TAB] ? -20 : 20;
	if (key == SDLK_x && (change = 1))
		(*color)[1] += keystate[SDL_SCANCODE_TAB] ? -20 : 20;
	if (key == SDLK_c && (change = 1))
		(*color)[2] += keystate[SDL_SCANCODE_TAB] ? -20 : 20;
	*color = trim_color(*color);
	return (change);
}

int		change_cone(t_cone_data *cone, int key, const Uint8 *keystate)
{
	int		change;

	change = 0;
	if (key == SDLK_q && (change = 1))
		cone->dir[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_w && (change = 1))
		cone->dir[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_e && (change = 1))
		cone->dir[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	make_unit_vector(&cone->dir);
	if (key == SDLK_r && (change = 1))
		cone->tangent += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	cone->tangent = CLAMP(cone->tangent, 0.1, 2);
	if (key == SDLK_a && (change = 1))
		cone->vertex[0] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_s && (change = 1))
		cone->vertex[1] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	if (key == SDLK_d && (change = 1))
		cone->vertex[2] += keystate[SDL_SCANCODE_TAB] ? -0.1 : 0.1;
	change += change_color_and_specular(&cone->color, \
		&cone->specular, key, keystate);
	return (change);
}
