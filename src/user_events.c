/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:23:24 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/09 18:23:25 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			there_will_be_loop(t_rt *rt)
{
	start_render(rt);
	rt->editing = 0;
	while (1)
	{
		if (rt->editing)
		{
			if (change_scene(rt))
				start_render(rt);
		}
		else if (user_commands(rt))
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
	rt->pov.cx = cos(rt->pov.dir[0]);
	rt->pov.sx = sin(rt->pov.dir[0]);
	rt->pov.cy = cos(rt->pov.dir[1]);
	rt->pov.sy = sin(rt->pov.dir[1]);
	return (1);
}

static int	translate(t_rt *rt)
{
	const Uint8	*keyboard_state = SDL_GetKeyboardState(0);

	if (keyboard_state[SDL_SCANCODE_W])
		rt->pov.coord[1] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_A])
		rt->pov.coord[0] -= TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_D])
		rt->pov.coord[0] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_S])
		rt->pov.coord[1] -= TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_D] \
		|| keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_S])
		return (1);
	return (0);
}

static void	get_first_click(t_rt *rt)
{
	int			x;
	int			y;

	SDL_GetMouseState(&x, &y);
	rt->uc.click[0] = x;
	rt->uc.click[1] = y;
}

int			user_commands(t_rt *rt)
{
	rt->uc.change = 0;
	rt->uc.change += rotate(rt);
	rt->uc.change += translate(rt);
	while (SDL_PollEvent(&rt->uc.ev) > 0 && rt->editing == 0)
	{
		if (rt->uc.ev.type == SDL_QUIT)
		{
			ft_putstr(TGRE"See you\n"TNULL);
			exit(0);
		}
		else if (rt->uc.ev.type == SDL_KEYDOWN)
		{
			if (rt->uc.ev.key.keysym.sym == SDLK_ESCAPE)
			{
				ft_putstr(TGRE"Bye bye\n"TNULL);
				exit(0);
			}
			else if (rt->uc.ev.key.keysym.sym == EDITOR)
				rt->editing = 1;
		}
		else if (rt->uc.ev.type == SDL_MOUSEWHEEL)
		{
			if (rt->uc.ev.wheel.y > 0 && (rt->uc.change = 1))
				rt->pov.coord[2] += TRANSLATE_SPEED;
			else if (rt->uc.ev.wheel.y < 0 && (rt->uc.change = 1))
				rt->pov.coord[2] -= TRANSLATE_SPEED;
		}
		// else if (rt->uc.ev.type == SDL_MOUSEBUTTONDOWN)
		// 	get_first_click(rt);
		// else if (rt->uc.ev.type == SDL_MOUSEBUTTONUP)
		// 	rt->uc.click = (t_vector){0, 0, 0, 0};
		// else if (rt->uc.ev.type == SDL_MOUSEMOTION)
		// 	rt->uc.change += rotate(rt);
	}
	return (rt->uc.change);
}
