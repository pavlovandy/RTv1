/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:23:24 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/14 13:21:27 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			there_will_be_loop(t_rt *rt)
{
	start_render(rt);
	rt->editing = 0;
	rt->uc.rotation = 0;
	while (1)
	{
		if (user_commands(rt))
			start_render(rt);
	}
	return (0);
}

static int	rotate(t_rt *rt)
{
	int				x;
	int				y;

	SDL_GetRelativeMouseState(&x, &y);
	if (x == 0 && y == 0)
		return (0);
	rt->pov.dir[0] += (y) * ROTATION_SPEED;
	rt->pov.dir[1] += (x) * ROTATION_SPEED;
	rt->pov.cx = cos(rt->pov.dir[0] / 180 * M_PI);
	rt->pov.sx = sin(rt->pov.dir[0] / 180 * M_PI);
	rt->pov.cy = cos(rt->pov.dir[1] / 180 * M_PI);
	rt->pov.sy = sin(rt->pov.dir[1] / 180 * M_PI);
	return (1);
}

static int	translate(t_rt *rt)
{
	const Uint8		*keyboard_state = SDL_GetKeyboardState(0);
	t_vector		translate_vector;

	translate_vector = (t_vector){0, 0, 0, 0};
	if (keyboard_state[SDL_SCANCODE_D])
		translate_vector[0] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_A])
		translate_vector[0] -= TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_W])
		translate_vector[2] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_S])
		translate_vector[2] -= TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_SPACE])
		translate_vector[1] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_LCTRL])
		translate_vector[1] -= TRANSLATE_SPEED;
	translate_vector = ft_rotate_camera(translate_vector, &rt->pov);
	rt->pov.coord += translate_vector;
	if (vect_len(translate_vector) != 0)
		return (1);
	return (0);
}

int			user_commands(t_rt *rt)
{
	rt->uc.change = 0;
	if (rt->uc.rotation)
		rt->uc.change += rotate(rt);
	rt->uc.change += translate(rt);
	while (SDL_PollEvent(&rt->uc.ev) > 0)
	{
		if (rt->uc.ev.type == SDL_QUIT)
			exit(error_message(TGRE"See you\n"TNULL) - 1);
		else if (rt->uc.ev.type == SDL_KEYDOWN)
		{
			if (rt->uc.ev.key.keysym.sym == SDLK_ESCAPE)
				exit(error_message(TGRE"Bye bye\n"TNULL) - 1);
			else if (rt->uc.ev.key.keysym.sym == SDLK_0)
			{
				rt->uc.rotation = !rt->uc.rotation;
				SDL_SetRelativeMouseMode(rt->uc.rotation);
				SDL_GetRelativeMouseState(NULL, NULL);
			}
		}
	}
	return (rt->uc.change);
}
