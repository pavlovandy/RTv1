/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:23:45 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/09 18:23:46 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		read_light_data(int fd, t_light *light)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_string(fd, &light->type, "type : {"))
		return (1);
	if (ft_strcmp(light->type, "point") != 0 && \
		ft_strcmp(light->type, "direct") != 0 && \
		ft_strcmp(light->type, "ambient") != 0)
		return (error_message(TCYN"Wrong light type"TNULL));
	if (check_line_for_value(fd, &light->intensity, "intensity : {"))
		return (1);
	if (light->intensity < 0)
		return (error_message(TCYN"Light intensity less then zero"TNULL));
	if (ft_strcmp(light->type, "point") == 0 || ft_strcmp(light->type, "direct") == 0)
	{
		if (check_line_for_coord(fd, &light->v, "v : {"))
			return (1);
	}
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}