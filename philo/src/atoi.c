/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:00:39 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/06 16:46:50 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_clean(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_digit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	atoi_phil(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (is_clean(str) == -1)
		return (-1);
	if (res > 2147483647)
		return (-1);
	return ((int)res);
}
