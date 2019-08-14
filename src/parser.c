/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:31:28 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:31:28 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		line_routine(int fd, t_rt *rt, char *line)
{
	if (ft_strcmp(line, "sphere") == 0 && sphere_routine(fd, rt) == 0)
		return (0);
	else if (ft_strcmp(line, "point of view") == 0 && \
										read_pov_data(fd, &rt->pov) == 0)
		return (0);
	else if (ft_strcmp(line, "plane") == 0 && plane_routine(fd, rt) == 0)
		return (0);
	else if (ft_strcmp(line, "light") == 0 && light_routine(fd, rt) == 0)
		return (0);
	else if (ft_strcmp(line, "cylinder") == 0 && cylin_routine(fd, rt) == 0)
		return (0);
	else if (ft_strcmp(line, "cone") == 0 && cone_routine(fd, rt) == 0)
		return (0);
	else if (ft_strcmp(line, "") == 0)
		return (0);
	return (error_message(TRED"Something unknown"TNULL));
}

int		read_scene(char *file, t_rt *rt)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (error_message(TRED"File problem"TRED));
	rt->scene.count_obj = 0;
	rt->scene.count_light = 0;
	rt->pov.coord = (t_vector){0, 0, 0};
	rt->pov.dir = (t_vector){0, 0, 0};
	while (get_next_line(fd, &line) > 0)
	{
		if (line_routine(fd, rt, line))
			return (error_message(TRED"File problem"TRED));
		free(line);
	}
	return (0);
}
