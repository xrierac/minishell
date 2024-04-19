/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/19 17:53:10 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_input(t_sh *msh)
{
	char	*input;
	char	*temp;

	while (1)
	{
		temp = readline(GRN"TOTO"RED"ROJO"GRN":) "END);
		add_history(temp);
		if (temp[0] != '\0')
		{
			input = syntax_check(msh, temp);
			if (msh->error == 0)
				lexer(input, msh);
			//free(input);
			msh->error = 0;
		}
		if (ft_strncmp(temp, "exit", 4) == 0 && ft_strlen(temp) == 4)
		{
			free_all(msh);
			exit(0);
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	t_sh	*msh;

	if (ac != 1)
		exit_error(msh, "Invalid arg amount\n", 127);
	msh = init_msh(ev);
	get_input(msh);
	return (0);
}
