/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/09 17:12:37 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_input(t_sh *msh)
{
	char	*input;

	while (1)
	{
		input = readline(HGRN ":) "RESET);
		add_history(input);
		count_pipes(msh, input);
		msh->lex_arr = init_lex(msh);
		lexer(input, msh);
//		count_tokens(input, msh);
		if (ft_strncmp(input, "exit", 4) == 0 && ft_strlen(input) == 4)
		{
			free(input);
			free_all(msh); 
			exit(0);
		}
		// else if (input != NULL)
		//  	printf("%s\n", input);
		else
			printf(HRED":(\n"RESET);
		free(input);
		free_lex(msh->lex_arr);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_sh	*msh;

	if (ac != 1)
		exit_error(msh, "Invalid arg amount\n", 127);
	msh = initialise(ev);
	get_input(msh);
	return (0);
}
