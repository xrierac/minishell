/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/28 12:57:41 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <signal.h>
#include <strings.h>

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
		receive_signal(1);
		temp = readline("MiNiH3LL> ");
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
				msh->exit_code = execution_branch(msh);
				printf("%d\n", msh->exit_code);
				free_lex(msh->lex_arr);
			}
			free(input);
			msh->error = 0;
			//rl_replace_line("", 100);
			//rl_on_new_line();
			//rl_redisplay();
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
