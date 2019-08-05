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
			res = res << 4 + line[i] - '0';
		else if (line[i] >= 'A' && line[i] <= 'F')
			res = res << 4 + line[i] - 'A';
		else
			return (res);
		i++;
	}
	return (res);
}

int			get_coord_value(char *line, t_vector *vec)
{
	char	**split;

	split = ft_strsplit(line, ',');
	if (*split != NULL || *split + 1 != NULL || *split + 2 != NULL)
		return (1);
	vec->x = str_to_double(*split);
	vec->y = str_to_double(*split + 1);
	vec->z = str_to_double(*split + 2);
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
	while (line[dot_pos] != '.')
		if (++dot_pos == line_len)
			break ;
	int_part = ft_atoi(line);
	float_part = dot_pos != line_len ? ft_atoi(line + dot_pos) : 0;
	return (int_part + (float)float_part / (count_num(float_part) * 10));
}