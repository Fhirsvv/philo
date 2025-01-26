/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:33:19 by ecortes-          #+#    #+#             */
/*   Updated: 2025/01/26 13:28:46 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// ./philo [nb philos] [time die] [time eat] [time sleep] [[max meals]]
// ./philo 5 300 100 100 5 | grep "1 is eating" | wc -l
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
