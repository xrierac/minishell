/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/05 14:38:31 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer(char *input, t_sh *msh)
{
	int	i;

	i = -1;
	
	while (input[++i])
	{
		if (input[i] == '|')
			msh->lex->lex[i]
			
	}
	printf("%s\n", cmd[0]);
}

void	get_input(t_sh *msh)
{
	char	*input;

	while (1)
	{
		input = readline(HGRN ":) "RESET);
		add_history(input);
		lexer(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			free_all(msh); 
			exit(0);
		}
		else if (input[0] != '\0')
		{
			printf("You entered: %s\n", input);
			free(input);
		}
		else
			printf(HRED":(\n"RESET);
	}
	clear_history();
}

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_sh	*msh;

	if (ac != 1)
		exit_error(msh, "Invalid arg amount\n", 127);
	initialise(ev, msh);
	get_input(msh);
	return (0);
}
