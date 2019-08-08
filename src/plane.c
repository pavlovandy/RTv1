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

int			read_plane_data(int fd, t_plane_data *data)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &data->normal, "normal : {"))
		return (1);
	if (check_line_for_value(fd, &data->h, "h : {"))
		return (1);
	if (check_line_for_color(fd, &data->color))
		return (1);
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}
