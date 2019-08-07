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

int		check_line_for_char(int fd, char c)
{
	char	*line;
	int		line_len;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full sphere data"TNULL));
	line_len = ft_strlen(line);
	if (line_len < 1)
		return (error_message(TRED"Empty line"TNULL));
	else if (line_len > 1)
		return (error_message(TRED"Lenght of line more then 1"TNULL));
	else if (line[0] != c)
		return (error_message(TRED"There is no brace on the line"TNULL));
	free(line);
	return (0);
}

int		check_line_for_coord(int fd, t_vector *coord)
{
	char	*line;
	int		i;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full sphere data"TNULL));
	i = 0;
	while (line[i] != 0 && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, "coord : {", 9))
		return (error_message(TRED"Coord line bad formated"TNULL));
	else
	{
		i += ft_strlen("coord : {");
		if (line[ft_strlen(line) - 1] != '}')
			return (error_message(TRED"Not braced at the end of line"TNULL));
		line[ft_strlen(line) - 1] = '\0';
		if (get_coord_value(line + i, coord))
			return (error_message(TRED"Coord line bad formated"TNULL));
	}
	free(line);
	return (0);
}

int		check_line_for_radius(int fd, float *rad)
{
	char	*line;
	int		i;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full sphere data"TNULL));
	i = 0;
	while (line[i] != 0 && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, "radius : {", 10))
		return (error_message(TRED"Radius line bad formated"TNULL));
	else
	{
		i += ft_strlen("radius : {");
		if (line[ft_strlen(line) - 1] != '}')
			return (error_message(TRED"Not braced at the end of line"TNULL));
		line[ft_strlen(line) - 1] = '\0';
		if ((*rad = (float)str_to_double(line + i)) <= 0)
			return (error_message(TRED"Negative or zero radius detected"TNULL));
	}
	free(line);
	return (0);
}

int		check_line_for_color(int fd, Uint32 *color)
{
	char	*line;
	int		i;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full sphere data"TNULL));
	i = 0;
	while (line[i] != 0 && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, "color : {", 9))
		return (error_message(TRED"Color line bad formated"TNULL));
	else
	{
		i += ft_strlen("color : {");
		if (line[ft_strlen(line) - 1] != '}')
			return (error_message(TRED"Not braced at the end of line"TNULL));
		line[ft_strlen(line) - 1] = '\0';
		*color = read_hex(line + i);
	}
	free(line);
	return (0);
}

int		read_sphere_data(int fd, t_sphere_data	*data)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &data->cent))
		return (1);
	if (check_line_for_radius(fd, &data->radius))
		return (1);
	if (check_line_for_color(fd, &data->color))
		return (1);
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}
