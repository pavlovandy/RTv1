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
	if (ft_strcmp(line, "sphere"))
	{
		if (rt->scene.count_obj >= 10)
			return (error_message("\x1b[31;1mToo much objects\x1b[0m"));
		rt->scene.obj[rt->scene.count_obj].fig_type = SPHERE;
		if (read_sphere_data(fd, rt->scene.obj[rt->scene.count_obj].data))
			return (error_message("\x1b[31;1mSphere data error\x1b[0m"));
		rt->scene.count_obj++;
	}
	else if (ft_strcmp(line, "point of view"))
		read_pov_data(fd, &rt->pov);
	else if (ft_strcmp(line, "plane"))
	{
		if (rt->scene.count_obj >= 10)
			return (error_message("\x1b[31;1mToo much objects\x1b[0m"));
		rt->scene.obj[rt->scene.count_obj].fig_type = PLANE;
		if (read_plane_data(fd, rt->scene.obj[rt->scene.count_obj].data))	
			return (error_message("\x1b[31;1mPlane data error\x1b[0m"));
		rt->scene.count_obj++;
	}
	else
		return (1);
	return (0);
}


int		read_scene(char *file, t_rt *rt)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (error_message("\x1b[31;1mFile problem\x1b[0m"));
	rt->scene.count_obj = 0;
	rt->pov.coord = (t_vector){0, 0, 0};
	rt->pov.dir = (t_vector){0, 0, 0};
	while (get_next_line(fd, &line) > 0)
		if (line_routine(fd, rt, line))
			return (error_message("\x1b[31;1mFile problem\x1b[0m"));
	return (0);
}
