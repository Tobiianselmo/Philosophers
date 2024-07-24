/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:24:40 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/24 18:00:43 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	*hawk_eye(void *arg) //MONITOR
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (get_death(philo->vars) == 0)
	{
		i = -1;
		while (++i < philo->vars->n_philo)
		{
			pthread_mutex_lock(&philo->vars->last_meal_mtx);
			if (philo->vars->t_die < (get_time() - philo->vars->start) - philo[i].last_meal)
			{
				pthread_mutex_unlock(&philo->vars->last_meal_mtx);
				write_action(&philo[i], DIED);
				set_death(philo->vars, 1);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->vars->last_meal_mtx);
			pthread_mutex_lock(&philo->vars->num_meals_mtx);
			if (philo[i].num_meals == philo->vars->must_eat)
			{
				pthread_mutex_unlock(&philo->vars->num_meals_mtx);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->vars->num_meals_mtx);
		}
		usleep(50);
	}
	return (NULL);
}

static void	init_hawk(t_philo *philo, pthread_t *hawk)
{
	if (pthread_create(hawk, NULL, &hawk_eye, (void *)philo))
		printf("Error breeding hawk\n");
}

static pthread_mutex_t	*init_forks(int len)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * len);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
			return (NULL);
	}
	return (forks);
}

// HAWK_EYE : METER 4 MUTEX
//

int	main(int argc, char **argv)
{
	t_vars			vars;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		hawk;
	int				i;

	i = -1;
	if (argc != 5 && argc != 6)
	{
		write(2, "Error arguments number\n", 24);
		return (2);
	}
	if (init_struct(&vars, argv) == 0)
		return (0);
	forks = init_forks(vars.n_philo);
	if (!forks)
		return (0);
	philo = create_threads(&vars, forks);
	init_hawk(philo, &hawk);
	pthread_join(hawk, NULL);
	while (++i < philo->vars->n_philo)
	{
		//printf("llegadsffdsfdsf\n");
		pthread_join(philo[i].thread, NULL);
		//printf("%d\n", i);
	}
	free(philo);
	free(forks);
	return (0);
}
