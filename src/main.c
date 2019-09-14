/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:44:09 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/14 13:21:08 by apavlov          ###   ########.fr       */
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
		if (sdl_init(&rt.sdl))
			return (1);
		if (config_intersect_function(&rt))
			return (1);
		there_will_be_loop(&rt);
	}
	return (0);
}
