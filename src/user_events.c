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

int		there_will_be_loop(t_rt *rt)
{		
	start_render(rt);
	SDL_UpdateWindowSurface(rt->sdl.win);
	while (1)
	{
		if (user_commands(rt)) //if anything changes draw scene again
		{
			start_render(rt);
			SDL_UpdateWindowSurface(rt->sdl.win);
		}
	}
	return (0);
}

static int	rotate(t_pov *pov)
{
	int				x;
	int				y;

	SDL_GetRelativeMouseState(&x,&y);
	if (x == 0 && y == 0)
		return (0);
	pov->dir[0] += x * ROTATION_SPEED;
	pov->dir[1] += y * ROTATION_SPEED;
	pov->cx = cos(pov->dir[0]);
	pov->sx = sin(pov->dir[0]);
	pov->cy = cos(pov->dir[1]);
	pov->sy = sin(pov->dir[1]);
	return (1);
}

static int	translate(t_pov *pov)
{
	const Uint8	*keyboard_state = SDL_GetKeyboardState(0);


	if (keyboard_state[SDL_SCANCODE_W])
		pov->coord[1] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_A])
		pov->coord[0] -= TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_D])
		pov->coord[0] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_S])
		pov->coord[1] -= TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_D] \
		|| keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_S])
		return (1);
	return (0);
}

int		user_commands(t_rt *rt)
{
	SDL_Event	ev;
	int		change;

	change = 0;
	//change += rotate(&rt->pov);
	change += translate(&rt->pov);

	while (SDL_PollEvent(&ev) > 0)
	{
		if (ev.type == SDL_QUIT)
		{
			ft_putstr(TGRE"See you\n"TNULL);
			exit(0);
		}
		else if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_ESCAPE)
			{
				ft_putstr(TGRE"Bye bye\n"TNULL);
				exit(0);
			}
		}
		else if (ev.type == SDL_MOUSEWHEEL)
		{
			if(ev.wheel.y > 0) // scroll up
			{
				rt->pov.coord[2] += TRANSLATE_SPEED;
				return (1);
			}
			else if(ev.wheel.y < 0) // scroll down
			{
				rt->pov.coord[2] -= TRANSLATE_SPEED;
				return (1);
			}
		}
	}
	return (change);
}
