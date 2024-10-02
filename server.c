/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel.mes.1337@gamil.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:36:20 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/02 17:36:21 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	binary_to_char(int num)
{
	int	dec_value;
	int	base;
	int	temp;
	int	last_digit;

	dec_value = 0;
	base = 1;
	temp = num;
	last_digit = 0;
	while (temp)
	{
		last_digit = temp % 10;
		temp = temp / 10;
		dec_value += last_digit * base;
		base = base * 2;
	}
	return (dec_value);
}

void	print_pid(int pid)
{
	write(1, "\t\t\t     pid :", 14);
	ft_putnbr(pid);
	write(1, "\n", 1);
	write(1, "\t⊱ ────────────────── {.⋅ ✯ ⋅.} ─────────────────── ⊰\n\n", 140);
}

void	signal_handler(int sig)
{
	static int	bits = 0;
	static int	binary;

	if (sig == SIGUSR1)
		binary = (binary * 10) + 1;
	else if (sig == SIGUSR2)
		binary *= 10;
	bits++;
	if (bits == 8)
	{
		if (binary_to_char(binary) == '\0')
			ft_putchar('\n');
		else
			ft_putchar(binary_to_char(binary));
		binary = 0;
		bits = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	print_pid(pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
