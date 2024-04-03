/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:50:13 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/03 16:56:12 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include "inc/minishell.h"


void	lexer(char **cmd)
{
	printf("%s\n", cmd[0]);
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	if (ac == 1 && env != NULL && av != NULL)
	{
		while (1)
		{
			input = readline(HGRN ":) "reset);
			add_history(input);
//			lexer(av);
			if (strncmp(input, "exit", 4) == 0)
			{
				free(input);
				exit(0);
			}
			else if (input[0] != '\0')
			{
				printf("You entered: %s\n", input);
				free(input);
			}
			else
				printf(HRED":(\n"reset);
		}
		clear_history();
	}
	else
		exit(-1);
	return (0);
}

