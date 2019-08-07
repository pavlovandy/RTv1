/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:28:23 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/07 16:28:24 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		read_pov_data(int fd, t_pov *pov)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &pov->coord, "coord : {"))
		return (1);
	if (check_line_for_coord(fd, &pov->dir, "angle : {"))
		return (1);
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}
