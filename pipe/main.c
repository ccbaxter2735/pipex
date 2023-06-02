/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terussar <terussar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:03:41 by terussar          #+#    #+#             */
/*   Updated: 2023/05/30 16:58:07 by terussar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_option(char **option)
{
	int	i;

	i = 0;
	while (option[i])
	{
		free(option[i]);
		i++;
	}
	free(option);
}

void	child1(char **av, int *pfd, char **env)
{
	int		fd;
	char	*cmd;
	char	**option;

	fd = open_file(av[1], 0);
	dup2(pfd[1], 1);
	close(pfd[0]);
	dup2(fd, 0);
	option = ft_split(av[2], ' ');
	cmd = find_cmd(option[0], env);
	if (!cmd)
	{
		free_option(option);
		perror("Error\nfirst command not found\n");
		exit(1);
	}
	execve(cmd, option, env);
}

void	child2(char **av, int *pfd, char **env)
{
	int		fd;
	char	*cmd;
	char	**option;

	fd = open_file(av[4], 1);
	dup2(pfd[0], 0);
	close(pfd[1]);
	dup2(fd, 1);
	option = ft_split(av[3], ' ');
	cmd = find_cmd(option[0], env);
	if (!cmd)
	{
		free_option(option);
		perror("Error\nsecond command not found\n");
		exit(1);
	}
	execve(cmd, option, env);
}

int	main(int ac, char **av, char **env)
{
	int		pid1;
	int		pid2;
	int		pfd[2];

	if (ac != 5)
	{
		perror("Error\nwrong number of arguments\n");
		return (0);
	}
	if (pipe(pfd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		return (2);
	}
	if (pid1 == 0)
		child1(av, pfd, env);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		return (2);
	}
	if (pid2 == 0)
		child2(av, pfd, env);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
