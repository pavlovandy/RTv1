/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:07:41 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/07 17:07:43 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		check_line_for_char(int fd, char c)
{
	char	*line;
	int		line_len;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full data"TNULL));
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

int		check_line_for_coord(int fd, t_vector *coord, char *data_mark)
{
	char	*line;
	int		i;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full data"TNULL));
	i = 0;
	while (line[i] != 0 && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, data_mark, ft_strlen(data_mark)))
		return (error_message(TRED"Coord line bad formated"TNULL));
	else
	{
		i += ft_strlen(data_mark);
		if (line[ft_strlen(line) - 1] != '}')
			return (error_message(TRED"Not braced at the end of line"TNULL));
		line[ft_strlen(line) - 1] = '\0';
		if (get_coord_value(line + i, coord))
			return (error_message(TRED"Coord line bad formated"TNULL));
	}
	free(line);
	return (0);
}

int		check_line_for_value(int fd, float *value, char *value_mark)
{
	char	*line;
	int		i;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full data"TNULL));
	i = 0;
	while (line[i] != 0 && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, value_mark, ft_strlen(value_mark)))
		return (error_message(TRED"Value line bad formated"TNULL));
	else
	{
		i += ft_strlen(value_mark);
		if (line[ft_strlen(line) - 1] != '}')
			return (error_message(TRED"Not braced at the end of line"TNULL));
		line[ft_strlen(line) - 1] = '\0';
		*value = (float)str_to_double(line + i);
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

int		check_line_for_string(int fd, char **str, char *str_mark)
{
	char	*line;
	int		i;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full data"TNULL));
	i = 0;
	while (line[i] != 0 && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, str_mark, ft_strlen(str_mark)))
		return (error_message(TRED"String line bad formated"TNULL));
	else
	{
		i += ft_strlen(str_mark);
		if (line[ft_strlen(line) - 1] != '}')
			return (error_message(TRED"Not braced at the end of line"TNULL));
		line[ft_strlen(line) - 1] = '\0';
		if ((*str = ft_strdup(line + i)) == 0)
			return (error_message(TRED"String line bad formated"TNULL));
	}
	free(line);
	return (0);
}

int		check_line_for_int_value(int fd, int *value, char *value_mark)
{
	char	*line;
	int		i;

	if (get_next_line(fd, &line) < 1)
		return (error_message(TRED"Not a full data"TNULL));
	i = 0;
	while (line[i] != 0 && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, value_mark, ft_strlen(value_mark)))
		return (error_message(TRED"Value line bad formated"TNULL));
	else
	{
		i += ft_strlen(value_mark);
		if (line[ft_strlen(line) - 1] != '}')
			return (error_message(TRED"Not braced at the end of line"TNULL));
		line[ft_strlen(line) - 1] = '\0';
		*value = (int)ft_atoi(line + i);
	}
	free(line);
	return (0);
}