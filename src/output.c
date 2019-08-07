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
	t_sphere_data	*data;

	i = -1;
	while (++i < sc->count_obj)
	{
		if (sc->obj[i].fig_type == SPHERE)
		{
			data = (t_sphere_data*)sc->obj[i].data;
			ft_putstr("There is a sphere\n");
			ft_putstr("Num of obj : \n");
			ft_putnbr(data->cent.z);
			ft_putchar('\n');
			ft_putstr("Radius : \n");
			ft_putnbr(data->cent.x);
			ft_putchar('\n');
			ft_putstr("Color : \n");
			ft_putnbr(data->cent.y);
			ft_putchar('\n');
		}
		else if (sc->obj[i].fig_type == PLANE)
			ft_putstr("There is a plane\n");
		else if (sc->obj[i].fig_type == CONE)
			ft_putstr("There is a cone\n");
		else if (sc->obj[i].fig_type == CYLIN)
			ft_putstr("There is a cylinder\n");
		else
			ft_putstr("What the hell is it\n");
	}
}