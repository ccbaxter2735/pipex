/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terussar <terussar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:03:41 by terussar          #+#    #+#             */
/*   Updated: 2023/05/22 14:07:40 by terussar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (ac < 1)
		return (1);
	if (pipe(fd) == -1)
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
	if (pid1 == 0) //child
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(av[1], av + 1, env);
	}
	pid2 = fork();
	if (pid2 == -1) //2eme child
	{
		perror("fork");
		return (2);
	}
	if (pid2 == 0)
	{
		dup2(fd[1], 0);
		close(fd[0]);
		close(fd[1]);
		execve(av[2], av + 2, env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

// int	main(int argc, char *argv[], char *env[])
// {
// 	int	pid1;
// 	int	fd[2];
	
//   if (pipe(fd) == -1)
//   {
//     perror("pipe");
// 		return 1;
//   }
// 	pid
//   if ((pid = fork()) == -1)
//     {
//       perror("fork");
//       return 1;
//     }
//   else if (pid == 0)
//     {
//       close(pipe_fd[0]);
//       if (dup2(pipe_fd[1], 1) == -1)
//       perror("dup2");
//       else if (execve(argv[1], argv + 1, env) == -1)
//       perror("execve");
//       return 1;
//     }
//   else
//     {
//       char      buffer[1024];
//       int       ret;
//       // int       status;

//       close(pipe_fd[1]);

//       while ((ret = read(pipe_fd[0], buffer, 1023)) != 0)
//       {
//         printf("%d\n", ret);
//         buffer[ret] = 0;
//         printf("%s\n", buffer);
//       }
//     }

//   return 0;
// }

// int	main(int argc, char *argv[])
// {
//   pid_t	pid;
//   // int	status;
//   int	pipe_fd[2];
// 	char	buffer[1024];
//   int		ret;

//   if (argc < 2)
//     return 1;

//   if (pipe(pipe_fd) == -1)
//     {
//       perror("pipe");
//       return 1;
//     }

//   if ((pid = fork()) == -1)
//     {
//       perror("fork");
//       return 1;
//     }
//   else if (pid == 0)
//     {
// 			printf("test enfant, pid = %d", pid);
//       close(pipe_fd[0]);
//       write(pipe_fd[1], argv[1], strlen(argv[1]));
//       close(pipe_fd[1]);
//       return 1;
//     }
//   else
//     {
// 			printf("test parent, pid = %d", pid);
//       close(pipe_fd[1]);
//       while ((ret = read(pipe_fd[0], buffer, 1023)))
//         {
//           buffer[ret] = 0;
//           printf("%s\n", buffer);
//         }
//       close(pipe_fd[0]);
//     }

//   return 0;
// }
		// pid_t	pid;

		// if ((pid = fork()) == -1)
		// 	{
		// 		perror("fork");
		// 		return 1;
		// 	}
		// else if (pid == 0)
		// 	printf("Je suis le fils, et mon pid = %d\n", getpid());
		// else
		// 	printf("Je suis le pere, et mon pid = %d. Le pid de mon fils = %d\n", getpid(), pid);

		// execve(argv[1], argv + 1, env); //execute pas le reste si fonctionne donc if inutile
		// perror("execve");
		// printf("My pid is: %d\n", getpid());