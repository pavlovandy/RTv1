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

//function of intersection with sphere

int		read_sphere_data(int fd, t_sphere_data	*data)
{
	char	*line;
	int		line_len;
	int		i;

	if (get_next_line(fd, &line) < 1)
		return (error_message("\x1b[31;1mNot a full sphere data\x1b[0m"));
	i = 0;
	line_len = ft_strlen(line);
	while (line[i] != '{')
		if (++i == line_len)
			return (error_message("\x1b[31;1mNot a full sphere data\x1b[0m"));
	if (get_coord_value(line + i, &data->cent))
		return (error_message("\x1b[31;1mCentre of the sphere error\x1b[0m"));
	free(line);
	if (get_next_line(fd, &line) < 1)
		return (error_message("\x1b[31;1mNot a full sphere data\x1b[0m"));
	data->radius = str_to_double(line);
	if (data->radius < 0)
		return (error_message("\x1b[31;1mNegative radius detected\x1b[0m"));
}