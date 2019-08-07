/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:32:35 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:32:35 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		read_sphere_data(int fd, t_sphere_data *data)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &data->cent, "cent : {"))
		return (1);
	if (check_line_for_value(fd, &data->radius, "radius : {"))
		return (1);
	if (data->radius <= 0)
	{
		printf("%f\n", data->radius);
		return (error_message(TRED"Negative radius of sphere detected"TNULL));
	}
	if (check_line_for_color(fd, &data->color))
		return (1);
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}
