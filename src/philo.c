/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:24:40 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/10 17:05:11 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//1 number_of_philosophers (Tambien el Num de tenedores)
//2 time_to_die (tiempo que puede estar sin comer)
//3 time_to_eat (tiempo para comer, y que tiene los tenedores ocupados)
//4 time_to_sleep (tiempo que tiene para dormir)
//5 [number_of_times_each_philosopher_must_eat] ((OPCIONAL), es la cantidad de veces que tienen que comer)

int	main(int argc, char **argv)
{
	t_philo	data;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		write(2, "Error arguments number\n", 24);
		return (2);
	}
	if (init_struct(&data, argv) == 0)
		return (0);
	return (0);
}
