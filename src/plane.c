/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:32:40 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:32:40 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_roots		plane_roots(t_vector view_point, t_vector view_port, void *data)
{
	t_vector	vr;
	float		dp_x_v;
	float		dp_d_v;
	t_plane_data	*plane;

	plane = (t_plane_data*)data;

	dp_d_v = dot_prod(view_port, plane->normal);
	if (dp_d_v == 0)
		return ((t_roots){BIG_VALUE, BIG_VALUE});
	dp_x_v = dot_prod(view_point, plane->normal);
	vr = view_point - plane->dot;
	return ((t_roots){BIG_VALUE, dp_d_v / dp_x_v});
}

int			read_plane_data(int fd, t_plane_data *data)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &data->normal, "normal : {"))
		return (1);
	if (make_unit_vector(&data->normal))
		return (error_message(TRED"Normile vector is 0-vector"TNULL));
	if (check_line_for_coord(fd, &data->dot, "dot : {"))
		return (1);
	if (check_line_for_coord(fd, &data->color, "color : {"))
		return (1);
	if (data->color[0] > 255 || data->color[1] > 255 || data->color[2] > 255)
		return (error_message(TRED"Bad color values"TNULL));
	if (data->color[0] < 0 || data->color[1] < 0 || data->color[2] < 0)
		return (error_message(TRED"Bad color values"TNULL));
	if (check_line_for_int_value(fd, &data->specular, "specular : {"))
		return (1);
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}
