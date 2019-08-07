/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:31:50 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:31:51 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		error_message(char *msg)
{
	ft_putstr(msg);
	ft_putchar('\n');
	return (1);
}

int		put_usage(void)
{
	ft_putstr("usage\n");
	return (1);
}

void	print_scene_data(t_scene *sc) //delete this
{
	int		i;

	i = -1;
	while (++i < sc->count_obj)
	{
		if (sc->obj[i].fig_type == SPHERE)
		{
			ft_putstr("There is a sphere\n");
			printf("%f\n", ((t_sphere_data*)sc->obj[i].data)->radius);
		}
		else if (sc->obj[i].fig_type == PLANE)
		{
			ft_putstr("There is a plane\n");
			printf("%f\n", ((t_plane_data*)sc->obj[i].data)->h);
		}
		else if (sc->obj[i].fig_type == CONE)
			ft_putstr("There is a cone\n");
		else if (sc->obj[i].fig_type == CYLIN)
			ft_putstr("There is a cylinder\n");
		else
			ft_putstr("What the hell is it\n");
	}
}
