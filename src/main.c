/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/06 15:14:54 by tcampbel         ###   ########.fr       */
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

	while (i < msh->len)
	{
		//printf("i = %i processes=%i\n", i, msh->len);
		j = 0;
		while (msh->tok_count > j)
		{
			//printf("j=%i tok=%i\n", j, msh->tok_count);
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
		add_history(temp);
		if (ft_strncmp(temp, "exit", 4) == 0 && ft_strlen(temp) == 4)
		{
			//free_all(msh);
			exit(0);
		}
		if (temp[0] != '\0')
		{
			input = syntax_check(msh, temp);
			if (msh->error == 0)
			{
				//free(temp);
				lexer(input, msh);
			}
			if (msh->error == 1)
				free(input);
			// if (msh->error == 1)
			// 	free(input);
			execution_branch(msh);
			msh->error = 0;
		}
		//print_lex(msh, msh->lex_arr);
		//free_lex(msh, msh->lex_arr);
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
