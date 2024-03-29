/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:27:27 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 15:27:28 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		sdl_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->win_sur = SDL_GetWindowSurface(sdl->win)))
		return (error_message((char *)SDL_GetError()));
	return (0);
}

void	put_pixel(int x, int y, Uint32 color, SDL_Surface *surr)
{
	Uint32	*pixels;

	pixels = surr->pixels;
	pixels[y * surr->w + x] = color;
}

Uint32	get_pixel(int x, int y, SDL_Surface *surr)
{
	Uint32	*pixels;

	pixels = surr->pixels;
	return (pixels[y * surr->w + x]);
}

int		config_intersect_function(t_rt *rt)
{
	rt->fun.inter_f[SPHERE] = sphere_roots;
	rt->fun.inter_f[PLANE] = plane_roots;
	rt->fun.inter_f[CONE] = cone_roots;
	rt->fun.inter_f[CYLIN] = cylin_roots;
	return (0);
}
