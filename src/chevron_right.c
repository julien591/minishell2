/*
** chevron_right.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:52:10 2016 julien
** Last update Fri May 06 11:03:23 2016 julien
*/

#include	<fcntl.h>
#include	<sys/wait.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"env.h"
#include	"free.h"
#include	"str.h"

int	is_right_chevron(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '>')
	{
	  if (str[i + 1] == '>')
	    return (2);
	  else
	    return (1);
	}
      i++;
    }
  return (0);
}

char	*get_path(char **path, char *s)
{
  int	i;
  char	*test;

  i = 0;
  if (access(s, F_OK) == 0)
    return (s);
  else if (path != NULL)
    {
      while (path[i] != '\0')
	{
	  test = my_strcat(path[i], s);
	  if (access(test, F_OK) == 0)
	    {
	      free(s);
	      return (test);
	    }
	  else
	    free(test);
	  i++;
	}
      my_put_error(s, ": Command not found.\n");
      free(s);
    }
  return (NULL);
}

int	open_the_file(char *file, int code)
{
  int	fd;

  fd = -1;
  fd = (access(file, F_OK) != 0) ? open(file, O_CREAT | O_RDWR, 0644) : fd;
  fd = (code == 1 && fd == -1) ? open(file, O_RDWR, 0644) : fd;
  fd =  (code == 2 && fd == -1) ? open(file, O_RDWR | O_APPEND, 0644) : fd;
  if (fd == -1)
    {
      write(2, file, my_strlen(file));
      write(2, ": Acces denied\n", 15);
      return (-1);
    }
  return (fd);
}

void	right_redir(char **cmd, char **env, char *file, int code)
{
  int	fd;
  pid_t	pid;
  int	status;

  if (((fd = open_the_file(file, code)) != -1) && cmd[0] != NULL)
    {
      pid = fork();
      if (pid > 0)
	waitpid(pid, &status, 0);
      else
	{
	  dup2(fd, 1);
	  execve(cmd[0], cmd, env);
	  exit(0);
	}
      if (WIFSIGNALED(status))
	{
	  if (WTERMSIG(status) == 11)
	    write(2, "Segmentation fault\n", 19);
	}
      close(fd);
    }
}

void	right_chevron(char *s, t_envi *instuctions, int code)
{
  char	**tmp;
  char	**cmd;
  int	i;

  i = 0;
  tmp = my_str_to_wordtab(s, '>');
  while (tmp[i] != NULL)
    {
      tmp[i] = del_space(tmp[i]);
      i++;
    }
  cmd = my_str_to_wordtab(tmp[0], ' ');
  cmd[0] = get_path(instuctions->path, cmd[0]);
  right_redir(cmd, instuctions->env, tmp[i - 1], code);
  free_cmd(cmd);
  free_cmd(tmp);
}
