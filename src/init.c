/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:53:42 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/11 16:12:33 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// Quedaria saber que numeros van a poder ser recibidos por cada
// variable de la estructura philo

static int	set_num(t_philo *data, int i, char *line)
{
	int	nbr;

	nbr = atoi_phil(line);
	if (nbr == -1)
		return (0);
	if (i == 1)
		data->num_philo = nbr;
	else if (i == 2)
		data->time_die = nbr;
	else if (i == 3)
		data->time_eat = nbr;
	else if (i == 4)
		data->time_sleep = nbr;
	else if (i == 5)
		data->quantity_eat = nbr;
	return (1);
}

int	init_struct(t_philo *data, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (set_num(data, i, argv[i]) == 0)
		{
			// free struct
			return (0);
		}
		i++;
	}
	return (1);
}
