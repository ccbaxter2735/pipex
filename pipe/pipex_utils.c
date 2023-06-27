/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terussar <terussar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:10:31 by terussar          #+#    #+#             */
/*   Updated: 2023/06/27 16:45:54 by terussar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(char *file, int rd_wr)
{
	int	fd;

	if (rd_wr == 0)
		fd = open(file, O_RDONLY, 0777);
	if (rd_wr == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error\n");
		return (-1);
	}
	return (fd);
}

char	**find_path(char **env)
{
	char	**path;

	while (strncmp("PATH", *env, 4))
		env++;
	path = ft_split(*env + 5, ':');
	return (path);
}

char	*find_cmd(char *cmd, char **env)
{
	char	*tmp;
	char	*command;
	char	**path;
	int		i;

	i = 0;
	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] != '/' && cmd[0] != '.' )
		path = find_path(env);
	else
	{
		path = &cmd;
		path[1] = NULL;
	}
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (NULL);
}
