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

void	print_scene_data(t_scene *sc)
{
	int		i;
	t_sphere_data	*sphere;
	t_plane_data	*plane;
	t_cylin_data	*cylin;
	t_cone_data		*cone;

	i = -1;
	printf("__________________________\n");
	while (++i < sc->count_obj)
	{
		if (sc->obj[i].fig_type == SPHERE)
		{
			sphere = sc->obj[i].data;
			printf("sphere\n");
			printf("\tcent : {%f, %f, %f}\n", sphere->cent[0], sphere->cent[1], sphere->cent[2]);
			printf("\tradius : {%f}\n", sphere->radius);
			printf("\tcolor : {%f, %f, %f}\n", sphere->color[0], sphere->color[1], sphere->color[2]);
			printf("\tspecular : {%i}\n", sphere->specular);
		}
		else if (sc->obj[i].fig_type == PLANE)
		{
			plane = sc->obj[i].data;
			printf("plane\n");
			printf("\tnormal : {%f, %f, %f}\n", plane->normal[0], plane->normal[1], plane->normal[2]);
			printf("\tdot : {%f, %f, %f}\n", plane->dot[0], plane->dot[1], plane->dot[2]);
			printf("\tcolor : {%f, %f, %f}\n", plane->color[0], plane->color[1], plane->color[2]);
			printf("\tspecular : {%i}\n", plane->specular);
		}
		else if (sc->obj[i].fig_type == CONE)
		{
			cone = sc->obj[i].data;
			printf("cone\n");
			printf("\tvertex : {%f, %f, %f}\n", cone->vertex[0], cone->vertex[1], cone->vertex[2]);
			printf("\tangle : {%f}\n", atan(cone->tangent) * 360 / M_PI);
			printf("\tdir : {%f, %f, %f}\n", cone->dir[0], cone->dir[1], cone->dir[2]);
			printf("\tcolor : {%f, %f, %f}\n", cone->color[0], cone->color[1], cone->color[2]);
			printf("\tspecular : {%i}\n", cone->specular);
		}
		else if (sc->obj[i].fig_type == CYLIN)
		{
			cylin = sc->obj[i].data;
			printf("cylinder\n");
			printf("\tdot : {%f, %f, %f}\n", cylin->dot[0], cylin->dot[1], cylin->dot[2]);
			printf("\tradius : {%f}\n", cylin->radius);
			printf("\tdir : {%f, %f, %f}\n", cylin->dir[0], cylin->dir[1], cylin->dir[2]);
			printf("\tcolor : {%f, %f, %f}\n", cylin->color[0], cylin->color[1], cylin->color[2]);
			printf("\tspecular : {%i}\n", cylin->specular);
		}
		else
			ft_putstr(TRED"What the hell is it\n"TNULL);
	}
}
