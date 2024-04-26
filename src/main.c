/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/26 10:59:45 by tcampbel         ###   ########.fr       */
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
			// if (msh->error == 1)
			// 	free(input);
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
=======
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/quotes.c
/*   Created: 2024/04/11 15:00:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/22 17:27:05 by tcampbel         ###   ########.fr       */
=======
/*   Created: 2024/03/12 16:49:31 by xriera-c          #+#    #+#             */
/*   Updated: 2024/03/12 16:50:11 by xriera-c         ###   ########.fr       */
>>>>>>> a6a4aeae7e2605c1a5007d28e96446c3f67c5fe4:src/main.c
/*                                                                            */
/* ************************************************************************** */


<<<<<<< HEAD:src/quotes.c
int	find_quote(char *str, char q, int i)
{
	while (str[i] != q && str[i])
		++i;
	return (i + 1);
}

char	set_quote(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
	}
	return (0);
}

void	count_quotes(t_sh *msh, char *str)
{
	int		i;
	char	q;

	msh->count = 0;
	i = -1;
	q = set_quote(str);
	while (str[++i])
	{
		if (str[i] == q)
			msh->count++;
	}
	if (msh->count % 2 != 0)
	{
		ft_printf(2, "Close your quotes puta!\n");
		msh->error = 1;
	}
}
=======
>>>>>>> a6a4aeae7e2605c1a5007d28e96446c3f67c5fe4:src/main.c
>>>>>>> a6a4aeae7e2605c1a5007d28e96446c3f67c5fe4
