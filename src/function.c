/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:53:38 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 16:53:39 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			read_hex(char *line)
{
	int		res;
	int		i;
	int		line_len;

	line_len = ft_strlen(line);
	if (line_len > 2)
		if (line[0] != '0' || line[1] != 'x')
			return (0);
	i = 2;
	res = 0;
	while (i < line_len)
	{
		if (line[i] >= '0' && line[i] <= '9')
			res = (res << 4) + (line[i] - '0');
		else if (line[i] >= 'A' && line[i] <= 'F')
			res = (res << 4) + (line[i] - 'A');
		else if (line[i] >= 'a' && line[i] <= 'f')
			res = (res << 4) + (line[i] - 'a');
		else
			return (res);
		i++;
	}
	return (res);
}

int			get_coord_value(char *line, t_vector *vec)
{
	char	**split;
	int		i;

	split = ft_strsplit(line, ',');
	if (*split == NULL || *(split + 1) == NULL || *(split + 2) == NULL)
		return (1);
	(*vec)[0] = str_to_double(*split);
	(*vec)[1] = str_to_double(*(split + 1));
	(*vec)[2] = str_to_double(*(split + 2));
	i = 0;
	while (split[i] != 0)
		free(split[i++]);
	free(split);
	return (0);
}

double		str_to_double(char *line)
{
	int		int_part;
	int		float_part;
	int		dot_pos;
	int		line_len;

	dot_pos = 0;
	line_len = ft_strlen(line);
	while (line[dot_pos] != '.' && line[dot_pos] != 0)
		dot_pos++;
	dot_pos++;
	int_part = ft_atoi(line);
	float_part = (dot_pos != line_len) ? ft_atoi(line + dot_pos) : 0;
	return (int_part + (double)float_part / (pow(10, count_num(float_part))));
}

t_vector	trim_color(t_vector color)
{
	color[0] = CLAMP(color[0], 0, 255);
	color[1] = CLAMP(color[1], 0, 255);
	color[2] = CLAMP(color[2], 0, 255);
	return (color);
}

int			check_line_for_int_value(int fd, int *value, char *value_mark)
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
