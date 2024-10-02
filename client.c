/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel.mes.1337@gamil.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:36:01 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/02 17:36:01 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	fail(void)
{
	write(2, "Invalid pid\n", 13);
	exit(EXIT_FAILURE);
}

void	add_null(int *binary)
{
	int	j;

	binary = malloc(sizeof(int) * 8);
	j = 0;
	while (j < 8)
	{
		binary[j] = 0;
		j++;
	}
}

int	**char_to_binary(char *s)
{
	int	**binary;
	int	i;
	int	j;
	int	temp;

	i = 0;
	binary = malloc(sizeof(int *) * (ft_strlen(s) + 2));
	if (!binary)
		exit(EXIT_FAILURE);
	while (s[i])
	{
		binary[i] = malloc(sizeof(int) * 8);
		if (!binary[i])
			exit(EXIT_FAILURE);
		temp = s[i];
		j = 8;
		while (j-- >= 0)
		{
			binary[i][j] = temp % 2;
			temp /= 2;
		}
		i++;
	}
	add_null(binary[i]);
	return (binary);
}

static void	send_signal(int **ptr, int pid)
{
	int	byte;
	int	bit;

	byte = 0;
	while (ptr[byte])
	{
		bit = 0;
		while (bit < 8)
		{
			if (ptr[byte][bit] == 1)
				if (kill(pid, SIGUSR1) == -1)
					fail();
			else
				if (kill(pid, SIGUSR2) == -1)
					fail();
			bit++;
			usleep(100);
		}
		byte++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;
	int	**ptr;

	if (ac != 3)
	{
		write(2, "Usage: program_name <pid> <message>\n", 37);
		exit(EXIT_FAILURE);
	}
	i = 0;
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		write(2, "Invalid PID\n", 13);
		exit(EXIT_FAILURE);
	}
	ptr = char_to_binary(av[2]);
	send_signal(ptr, pid);
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (0);
}
