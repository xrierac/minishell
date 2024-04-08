/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/08 17:19:01 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	is_op(char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] == '<') \
		|| (str[i] == '>' && str[i + 1] == '>'))
		return (true);
	else if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '$')
		return (true);
	return (false);
}
t_bool	is_cmd(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && )
	{
		
	}
}

void	count_tokens(char *input, t_sh *msh)
{
	int	i;

	i = -1;
	msh->tok_count = 0;
	while (input[++i])
	{
		if (is_op(input, i))
			msh->tok_count++;
		 if (is_cmd(input))
		 	msh->tok_count++;
		
	}
}

void	lexer(char *input, t_sh *msh)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (msh->lex[++i])
	{
		msh->lex[i]->lex_arr[j] = "Hello";
	}
}

void	get_input(t_sh *msh)
{
	char	*input;

	while (1)
	{
		input = readline(HGRN ":) "RESET);
		add_history(input);
		init_lex(input, msh);
		lexer(input, msh);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			//free_all(msh); 
			exit(0);
		}
		else if (input != NULL)
		 	printf("%s\n", input);
		else
			printf(HRED":(\n"RESET);
	}
	clear_history();
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
