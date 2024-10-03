/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel.mes.1337@gamil.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:36:20 by moel-mes          #+#    #+#             */
/*   Updated: 2024/10/03 23:13:33 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	binary_to_char(int *binary)
{
	int	dec_value;
	int bits = 0;

	while (bits < 8)
	{
		dec_value = (dec_value << 1) + binary[bits];
        bits++;
	}
	return (dec_value);
}

int check_null(int *binary)
{
	int i;

    i = 0;
    while (i < 8)
    {
        if (binary[i] == 1)
            return (0);
        i++;
    }
    return (1);
}

void	signal_handler(int sig)
{
	static int	bits = 0;
	static int	binary[8] = {0};

	if (sig == SIGUSR1)
		binary[bits] = 1;
	else if (sig == SIGUSR2)
		binary[bits] = 0;
	bits++;
	if (bits == 8)
	{
		if (check_null(binary) == 1)
			ft_putstr("\n----------------------------------\n");
		else
			ft_putchar(binary_to_char(binary));
		bits = 0;
	}
}

int	main(void)
{
	ft_putstr("\033[1;33m\t\tServer's PID: ");
	ft_putnbr(getpid());
	ft_putstr("\033[1;0m\n");
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
