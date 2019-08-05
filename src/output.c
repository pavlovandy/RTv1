/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:31:50 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:31:51 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		error_message(char *msg)
{
	ft_putstr(msg);
	ft_putchar('\n');
	return (1);
}

int		put_usage(void)
{
	ft_putstr("usage\n");
	return (1);
}
