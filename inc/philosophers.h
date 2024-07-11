/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:41:52 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/11 16:08:20 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct	s_philo
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	quantity_eat;
}	t_philo;

//-------------INIT------------//
int		init_struct(t_philo *data, char **argv);
//-------------ATOI------------//
int		atoi_phil(char *str);

#endif