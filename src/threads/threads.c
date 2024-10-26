/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:31:26 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/26 18:38:46 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	threads(t_program *pr)
{
	size_t	i;

	pr->dead_flag = 0;
	i = 0;
	while (i < pr->nb_philos)
	{
		if (pthread_create(&pr->philos[i].thread, NULL, &routine,
			(void *)&pr->philos[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	while (++i < pr->nb_philos)
	{
		pthread_join(pr->philos[i].thread, NULL);
		i++;
	}
}

void	set_dead_flag(int i, t_philos *ph)
{
	pthread_mutex_lock(ph->dead_lock);
	*ph->dead_flag = i;
	pthread_mutex_unlock(ph->dead_lock);
}

int	is_dead_flag(t_philos *ph)
{
	int	i;

	pthread_mutex_lock(ph->dead_lock);
	if (*ph->dead_flag == 1)
	{
		pthread_mutex_unlock(ph->dead_lock);
		return (1);	
	}
	pthread_mutex_unlock(ph->dead_lock);
	return (0);
}
