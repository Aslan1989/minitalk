/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisaev <aisaev@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:14:41 by aisaev            #+#    #+#             */
/*   Updated: 2025/05/14 12:03:32 by aisaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * @brief Sends a character to the server, bit by bit, using signals.
 *
 * Sends each bit of the character `c` to the process with PID `pid`.
 * - If the bit is 1, sends SIGUSR1.
 * - If the bit is 0, sends SIGUSR2.
 * Adds a small delay to prevent signal loss.
 *
 * @param pid The process ID of the server.
 * @param c The character to send.
 */
void	send_char(pid_t pid, unsigned char c)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

/**
 * @brief Entry point of the client program.
 *
 * Checks arguments, validates the server PID, and sends a message to the server.
 * The message is sent character by character using the send_char function.
 * Ends the message with a null character to signal the end.
 *
 * @param argc The number of command-line arguments.
 * @param argv The list of arguments: [0] is the program name,
 *             [1] is the server PID, [2] is the message to send.
 *
 * @return 0 on success, 1 if there was an error with the arguments or PID.
 */
int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	int		i;

	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) == -1)
	{
		write(2, "Error: invalid PID\n", 20);
		return (1);
	}
	message = argv[2];
	i = 0;
	while (message[i])
		send_char(pid, message[i++]);
	send_char(pid, '\0');
	return (0);
}
