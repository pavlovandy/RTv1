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
	void	**data;

	if (ft_strcmp(line, "sphere") == 0)
	{
		if (rt->scene.count_obj >= 10)
			return (error_message(TRED"Too much objects"TNULL));
		rt->scene.obj[rt->scene.count_obj].fig_type = SPHERE;
		data = &rt->scene.obj[rt->scene.count_obj].data;
		if (!((*data) = ft_memalloc(sizeof(t_sphere_data))))
			return (error_message(TRED"Can't allocate memory for obj"TNULL));
		if (read_sphere_data(fd, (t_sphere_data*)(*data)))
			return (error_message(TRED"Sphere data error"TNULL));
		rt->scene.count_obj++;
	}
	else if (ft_strcmp(line, "point of view") == 0)
		read_pov_data(fd, &rt->pov);
	else if (ft_strcmp(line, "plane") == 0)
	{
		if (rt->scene.count_obj >= 10)
			return (error_message(TRED"Too much objects"TNULL));
		rt->scene.obj[rt->scene.count_obj].fig_type = PLANE;
		data = &rt->scene.obj[rt->scene.count_obj].data;
		if (!((*data) = ft_memalloc(sizeof(t_plane_data))))
			return (error_message(TRED"Can't allocate memory for obj"TNULL));
		if (read_plane_data(fd, rt->scene.obj[rt->scene.count_obj].data))
			return (error_message(TRED"Plane data error"TNULL));
		rt->scene.count_obj++;
	}
	else if (ft_strcmp(line, "light") == 0)
	{
		if (rt->scene.count_light >= 10)
			return (error_message(TRED"Too much lighting"TNULL));
		if (read_light_data(fd, rt->scene.light + rt->scene.count_light))
			return (error_message(TRED"Light data error"TNULL));
		rt->scene.count_light++;
	}
	else if (ft_strcmp(line, "") == 0)
		return (0);
	else
		return (error_message(TRED"Something unknown"TNULL));
	return (0);
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
