/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:44:09 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/02 15:44:55 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		main(int argc, char **argv)
{
	t_rt	rt;

	if (argc != 2)
		return (put_usage());
	else
	{
		if (read_scene(argv[1], &rt))
			return (1);
		print_scene_data(&rt.scene);
		if (sdl_init(&rt.sdl))
			return (1);
		start_render(&rt);
	}
	return (0);
}
