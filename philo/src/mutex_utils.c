/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:07:36 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/30 13:47:53 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	check_mutex(int value, int action)
{
	if (value == 0)
		return ;
	else if (value == EINVAL)
		write(1, "Invalid mutex object\n", 22);
	else if (value == EAGAIN && (action == LOCK || action == UNLOCK))
		write(1, "Recursive locks for mutex has been exceeded\n", 45);
	else if (value == EDEADLK && action == LOCK)
		write(1, "The current thread already owns the mutex\n", 43);
	else if (value == EPERM && action == UNLOCK)
		write(1, "The current thread does not own the mutex\n", 43);
	else if (value == EBUSY && action == DESTROY)
		write(1, "The object referenced by mutex is locked\n", 42);
}

void	protect_mutex(int action, pthread_mutex_t *mutex)
{
	if (action == LOCK)
		check_mutex(pthread_mutex_lock(mutex), action);
	else if (action == UNLOCK)
		check_mutex(pthread_mutex_unlock(mutex), action);
	else if (action == DESTROY)
		check_mutex(pthread_mutex_destroy(mutex), action);
}
