/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:33:19 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/26 18:33:10 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// ./philo [nb philos] [time die] [time eat] [time sleep] [[max meals]]
int	main(int argc, char **argv)
{
	t_program	pr;

	if ((argc != 5 || argc != 6) && check_argvs(argv) != 0)
		return (printf("Number of args or args is incorrect\n"));
	init(&pr, argv);
	threads(&pr);
	free_program(&pr);
	return (0);
}

void	dead_write(t_philos *ph)
{
	size_t	time;

	time = get_current_time() - ph->start_time;
	pthread_mutex_lock(ph->write_lock);
	printf("%zu %d died\n", time, ph->id);
	pthread_mutex_unlock(ph->write_lock);
}
