/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 00:31:34 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/14 00:31:36 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		sphere_routine(int fd, t_rt *rt)
{
	t_sphere_data	**data;

	if (rt->scene.count_obj >= MAX_OBJ_COUNT)
		return (error_message(TRED"Too much objects"TNULL));
	rt->scene.obj[rt->scene.count_obj].fig_type = SPHERE;
	data = (t_sphere_data**)&rt->scene.obj[rt->scene.count_obj].data;
	if (!((*data) = ft_memalloc(sizeof(t_sphere_data))))
		return (error_message(TRED"Can't allocate memory for obj"TNULL));
	if (read_sphere_data(fd, *data))
		return (error_message(TRED"Sphere data error"TNULL));
	rt->scene.count_obj++;
	return (0);
}

int		plane_routine(int fd, t_rt *rt)
{
	t_plane_data	**data;

	if (rt->scene.count_obj >= MAX_OBJ_COUNT)
		return (error_message(TRED"Too much objects"TNULL));
	rt->scene.obj[rt->scene.count_obj].fig_type = PLANE;
	data = (t_plane_data**)&rt->scene.obj[rt->scene.count_obj].data;
	if (!((*data) = ft_memalloc(sizeof(t_plane_data))))
		return (error_message(TRED"Can't allocate memory for obj"TNULL));
	if (read_plane_data(fd, *data))
		return (error_message(TRED"Plane data error"TNULL));
	rt->scene.count_obj++;
	return (0);
}

int		light_routine(int fd, t_rt *rt)
{
	if (rt->scene.count_light >= MAX_LIGHTING_COUNT)
		return (error_message(TRED"Too much lighting"TNULL));
	if (read_light_data(fd, rt->scene.light + rt->scene.count_light))
		return (error_message(TRED"Light data error"TNULL));
	rt->scene.count_light++;
	return (0);
}

int		cylin_routine(int fd, t_rt *rt)
{
	t_cylin_data	**data;

	if (rt->scene.count_obj >= MAX_OBJ_COUNT)
		return (error_message(TRED"Too much objects"TNULL));
	rt->scene.obj[rt->scene.count_obj].fig_type = CYLIN;
	data = (t_cylin_data**)&rt->scene.obj[rt->scene.count_obj].data;
	if (!((*data) = ft_memalloc(sizeof(t_cylin_data))))
		return (error_message(TRED"Can't allocate memory for obj"TNULL));
	if (read_cylin_data(fd, *data))
		return (error_message(TRED"Cylin data error"TNULL));
	rt->scene.count_obj++;
	return (0);
}

int		cone_routine(int fd, t_rt *rt)
{
	t_cone_data		**data;

	if (rt->scene.count_obj >= MAX_OBJ_COUNT)
		return (error_message(TRED"Too much objects"TNULL));
	rt->scene.obj[rt->scene.count_obj].fig_type = CONE;
	data = (t_cone_data**)&rt->scene.obj[rt->scene.count_obj].data;
	if (!((*data) = ft_memalloc(sizeof(t_cone_data))))
		return (error_message(TRED"Can't allocate memory for obj"TNULL));
	if (read_cone_data(fd, *data))
		return (error_message(TRED"Cone data error"TNULL));
	rt->scene.count_obj++;
	return (0);
}
