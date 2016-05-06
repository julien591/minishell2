/*
** chevron_d_left.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:51:54 2016 julien
** Last update Fri May 06 14:43:55 2016 julien
*/

#include	<fcntl.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<sys/stat.h>
#include	<sys/wait.h>
#include	<unistd.h>
#include	"env.h"
#include	"free.h"
#include	"str.h"

int	fill_tmp(char *end)
{
  char	*s;
  int	fd;

  fd = open("/tmp/minishell2_tmp", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1)
    {
      write(2, "Error, cannot create tmp file\n", 30);
      return (-1);
    }
  my_putstr("? ");
  while (my_strcmp((s = my_read()), end) != 0)
    {
      my_putstr("? ");
      write(fd, s, my_strlen(s));
      free(s);
      write(fd, "\n", 1);
    }
  free(s);
  return (fd);
}

int	double_left_redir(char *bin, char **cmd, char **env, char *end)
{
  int	fd;
  int	status;
  pid_t	pid;

  if ((fd = fill_tmp(end)) == -1)
    return (0);
  lseek(fd, 0, SEEK_SET);
  pid = fork();
  if (pid > 0)
    waitpid(pid, &status, 0);
  else if (bin != NULL)
    {
      dup2(fd, 0);
      execve(bin, cmd, env);
      exit(0);
    }
  if (WIFSIGNALED(status))
    {
      if (WTERMSIG(status) == 11)
	write(2, "Segmentation fault\n", 19);
    }
  close(fd);
  remove("/tmp/minishell2_tmp");
  return (0);
}

void	double_left_chevron(char *s, t_envi *instuctions)
{
  char	**tmp;
  char	**cmd;
  char	*bin;
  int	i;

  i = 0;
  tmp = my_str_to_wordtab(s, '<');
  while (tmp[i] != NULL)
    {
      tmp[i] = del_space(tmp[i]);
      i++;
    }
  cmd = my_str_to_wordtab(tmp[0], ' ');
  bin = get_path(instuctions->path, cmd[0]);
  double_left_redir(bin, cmd, instuctions->env, tmp[i - 1]);
  if (bin != NULL && my_strcmp(bin, cmd[0]) != 0)
    free(bin);
  free_cmd(cmd);
  free_cmd(tmp);
}
