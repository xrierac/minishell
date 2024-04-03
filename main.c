/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:50:13 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/03 12:12:50 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <strings.h>

int	main(void)
{
	char	*input;

	input = readline(":) " );

	while (1)
	{
		if (strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit(0);
		}
		else if (input[0] != '\0')
		{
			printf("You entered: %s", input);
			free(input);
		}
		else
			printf(":( Booo!");
		
	}
	return (0);
}

