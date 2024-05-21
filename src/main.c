/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/21 14:30:29 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    print_arr(char **str)
{
    int i = -1;

    while (str[++i])
        printf("%s\n", str[i]); 
}

void	print_lex(t_sh *msh, t_lex	***lex)
{
	int	i = 0;
	int	j = 0;

	while (i < msh->processes)
	{
		j = 0;
		while (msh->tok_count > j)
		{
			print_arr(lex[i][j]->cmd_arr);
			j++;
		}
		i++;
	}
}

void	get_input(t_sh *msh)
{
	char	*input;
	char	*temp;

	while (1)
	{
		temp = readline(GRN"TOTO"RED"ROJO"GRN":) "END);
		if (!temp)
			exit_error(msh, "readline", 127);
		if (temp)
			add_history(temp);
		if (ft_strncmp(temp, "exit", 5) == 0 && ft_strlen(temp) == 4)
		{
			//free_all(msh);
			exit(0);
		}
		if (temp[0] != '\0')
		{
			input = syntax_check(msh, temp);
			if (msh->error == 0)
			{
				lexer(input, msh);
				//print_lex(msh, msh->lex_arr);
				//execution_branch(msh);
				free_lex(msh, msh->lex_arr);
			}
			free(input);
			msh->error = 0;
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	t_sh	*msh;

	if (ac != 1)
	{
		ft_printf(2, "Invalid arg amount\n");
		exit(1);
	}
	msh = init_msh(ev);
	get_input(msh);
	return (0);
}
