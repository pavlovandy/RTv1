/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:32:17 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:32:17 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

//vector math

float		dot_prod(t_vector v1, t_vector v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] \
			+ v1[2] * v2[2]);
}

t_vector	vector_prod(t_vector v1, t_vector v2)
{
	t_vector	res;

	res[0] = v1[1] * v2[2] - v1[2] * v2[1];
	res[1] = v1[0] * v2[2] - v1[2] * v2[0];
	res[2] = v1[1] * v2[0] - v1[0] * v2[1];
	return (res);
}

float		vect_len(t_vector a)
{
	return (sqrt(dot_prod(a, a)));
}

t_vector	multi_vect(t_vector a, float multi)
{
	return (t_vector){a[0] * multi, a[1] * multi, a[2] * multi};
}

int			make_unit_vector(t_vector *v)
{
	float	v_len;

	v_len = vect_len(*v);
	if (comp_real(v_len, 0, 0.00001))
		return (1);
	*v = multi_vect(*v, v_len);
	return (0);
}