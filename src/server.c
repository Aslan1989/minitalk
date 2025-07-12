/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisaev <aisaev@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:07:32 by aisaev            #+#    #+#             */
/*   Updated: 2025/05/14 13:58:51 by aisaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * @brief Handles incoming signals from the client.
 *
 * Builds a character from 8 bits received through signals.
 * - SIGUSR1 represents bit 1.
 * - SIGUSR2 represents bit 0.
 * When 8 bits are received, prints the character.
 * If the character is null ('\0'), prints a newline.
 *
 * @param signal The signal received (SIGUSR1 or SIGUSR2).
 */
void	receive_signal(int signal)
{
	static unsigned char	character = 0;
	static int				bit_count = 0;

	if (signal == SIGUSR1)
		character |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &character, 1);
		if (character == '\0')
			write(1, "\n", 1);
		bit_count = 0;
		character = 0;
	}
}

/**
 * @brief Entry point of the server program.
 *
 * Prints the server PID so clients know where to send messages.
 * Sets up signal handlers for SIGUSR1 and SIGUSR2.
 * Waits for incoming signals indefinitely.
 *
 * @return Always returns 0.
 */
int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, receive_signal);
	signal(SIGUSR2, receive_signal);
	while (1)
		pause();
}
