/*
** execute.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:53:37 2016 julien
** Last update Fri May 06 11:09:01 2016 julien
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	"env.h"
#include	"str.h"

void	my_put_error(char *str, char *command)
{
  if (my_strcmp(str, "cd") == 0)
    {
      write(2, command, my_strlen(command));
      write(2, ": No such file or directory.\n", 29);
    }
  else
    {
      write(2, str, my_strlen(str));
      write(2, command, 21);
    }
}

void	execute(char *file, t_envi *instuctions, char **cmd)
{
  pid_t pid;
  int	status;

  pid = fork();
  if (pid > 0)
    waitpid(pid, &status, 0);
  else
    {
      execve(file, cmd, instuctions->env);
      exit(0);
    }
  if (WIFSIGNALED(status))
    {
      if (WTERMSIG(status) == 11)
	write(2, "Segmentation fault\n", 19);
    }
}

int	my_test(t_envi *instuctions, char **cmd)
{
  int	i;
  char	*test;

  i = 0;
  if (access(cmd[0], F_OK) == 0)
    execute(cmd[0], instuctions, cmd);
  else if (instuctions->path != NULL)
    {
      while (instuctions->path[i] != '\0')
	{
	  test = my_strcat(instuctions->path[i], cmd[0]);
	  if (access(test, F_OK) == 0)
	    {
	      execute(test, instuctions, cmd);
	      free(test);
	      return (0);
	    }
	  else
	    free(test);
	  i++;
	}
      my_put_error(cmd[0], ": Command not found.\n");
    }
  return (0);
}
