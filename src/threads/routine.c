/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:42:02 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/28 10:11:20 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	phwrite(char *str, size_t time, t_philos *ph)
{
	pthread_mutex_lock(ph->write_lock);
	printf(str, time, ph->id);
	pthread_mutex_unlock(ph->write_lock);
}

static int	eat(t_philos *ph)
{
	size_t	time;

	if (is_dead_flag(ph))
		return (1);
	pthread_mutex_lock(ph->right_fork);
	time = get_current_time() - ph->start_time;
	phwrite("%zu %d has taken a fork\n", time, ph);
	pthread_mutex_lock(ph->left_fork);
	time = get_current_time() - ph->start_time;
	phwrite("%zu %d has taken a fork\n", time, ph);
	pthread_mutex_lock(ph->meals_lock);
	time = get_current_time() - ph->start_time;
	phwrite("%zu %d is eating\n", time, ph);
	ph->time_lmeal = time;
	++ph->current_meals;
	if (*ph->max_meals == ph->current_meals)
		++*ph->how_many_finished;
	if (*ph->how_many_finished == *ph->nb_philos)
		set_dead_flag(1, ph);
	pthread_mutex_unlock(ph->meals_lock);
	ft_usleep(*ph->time_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	return (0);
}

static int	think(t_philos *ph)
{
	size_t	time;

	if (is_dead_flag(ph))
		return (1);
	time = get_current_time() - ph->start_time;
	phwrite("%zu %d is thinking\n", time, ph);
	if (time - ph->time_lmeal > *ph->time_die)
	{
		set_dead_flag(1, ph);
		dead_write(ph);
		return (1);
	}
	return (0);
}

static int	phsleep(t_philos *ph)
{
	size_t	time;

	if (is_dead_flag(ph))
		return (1);
	time = get_current_time() - ph->start_time;
	phwrite("%zu %d is sleeping\n", time, ph);
	ft_usleep(*ph->time_sleep);
	time = get_current_time() - ph->start_time;
	if (time - ph->time_lmeal > *ph->time_die)
	{
		set_dead_flag(1, ph);
		dead_write(ph);
		return (1);
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philos	*ph;

	ph = (t_philos *)philo;
	while (true)
	{
		if (!eat(ph) && !phsleep(ph) && !think(ph))
			continue ;
		return (NULL);
	}
	return (NULL);
}
