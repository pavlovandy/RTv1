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

int		user_commands(t_rt *rt)
{
	SDL_Event	ev;

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
	}
	return (0);
}
