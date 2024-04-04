/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:50:13 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/04 16:53:03 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer(char **cmd)
{
	printf("%s\n", cmd[0]);
}

void	exit_error(t_sh *msh, char *msg, int status)
{
	if (msh)
	{
//		free_all(msh);
		ft_printf(2, HRED":( %s\n"reset, msg);
	}
	exit(status);
}

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_sh	msh;

//	msh = NULL;
	if (ac == 1 && ev != NULL && av != NULL)
	{
		initialise(ev, &msh);
		while (1)
		{
			input = readline(HGRN ":) "reset);
			add_history(input);
//			lexer(av);
			if (ft_strncmp(input, "exit", 4) == 0)
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
