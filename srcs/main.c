/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:42:53 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/13 22:41:08 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	cleanup(t_data *data)
{
	int	i;

	if (data->philo)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			pthread_mutex_destroy(&data->philo[i].right_fork);
			i++;
		}
		free(data->philo);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->stop_mutex);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (is_not_valid(ac, av))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (init_structs(&data, ac, av) != 0)
	{
		printf("Error: failed to initialize\n");
		return (1);
	}
	// Créer le thread monitor et tous les threads philosophes
	if (init_threads(&data) != 0)
	{
		printf("Error: failed to create threads\n");
		cleanup(&data);
		return (1);
	}
	// Attendre la fin du monitor
	if (data.monitor_created)
		pthread_join(data.monitor, NULL);
	// Attendre la fin de tous les philosophes
	for (i = 0; i < data.number_of_philo; i++)
		pthread_join(data.philo[i].thread, NULL);
	// Clean memory and mutex
	cleanup(&data);
	return (0);
}
