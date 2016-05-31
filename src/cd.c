/*
** cd.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:51:36 2016 julien
** Last update Thu May 26 18:30:44 2016 Julien Leleu
*/

#include	<dirent.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"str.h"

int		find_in_env(char **env, char *value)
{
  int		i;

  i = 0;
  if (env != NULL)
    {
      while (env[i] != NULL)
	{
	  if (my_strcmp(env[i], value) == 0)
          	return (1);
	  i++;
	}
    }
  return (-1);
}

void		cd_home(t_envi *ins, char *home)
{
  char		dir[1024];

  if (find_in_env(ins->env, "OLDPWD=") == 1)
    ins->env = replace_env(ins->env, "OLDPWD=", getcwd(dir, sizeof(dir)));
  if (home != NULL)
    chdir(home);
  else
    write(2, "No home directory\n", 18);
  if (find_in_env(ins->env, "PWD=") == 1)
    ins->env = replace_env(ins->env, "PWD=", getcwd(dir, sizeof(dir)));
}

void		cd_before(t_envi *ins, char *old)
{
  char		dir[1024];
  DIR*		folder;

  if (old != NULL)
    {
      folder = opendir(old);
      if (folder)
	{
	  if (find_in_env(ins->env, "OLDPWD=") == 1)
	    ins->env = replace_env(ins->env, "OLDPWD=", getcwd(dir, sizeof(dir)));
	  chdir(old);
	  if (find_in_env(ins->env, "PWD=") == 1)
	    ins->env = replace_env(ins->env, "PWD=", getcwd(dir, sizeof(dir)));
	}
      else
	my_put_error("cd", old);
      closedir(folder);
    }
}

void		cd_normal(t_envi *ins)
{
  char		dir[1024];
  DIR		*folder;

  folder = opendir(ins->cmd[1]);
  if (folder)
    {
      if (find_in_env(ins->env, "OLDPWD=") == 1)
	ins->env = replace_env(ins->env, "OLDPWD=", getcwd(dir, sizeof(dir)));
      chdir(ins->cmd[1]);
      if (find_in_env(ins->env, "PWD=") == 1)
	ins->env = replace_env(ins->env, "PWD=", getcwd(dir, sizeof(dir)));
    }
  else
    my_put_error("cd", ins->cmd[1]);
  closedir(folder);
}

void		builtin_cd(t_envi *instuctions, int nb_arg)
{
  char		*home;
  char		*old;

  home = my_gethome(instuctions->env);
  old = my_get_old_pwd(instuctions->env);
  if (nb_arg == 1)
      cd_home(instuctions, home);
  else if (nb_arg == 2 && my_strcmp(instuctions->cmd[1], "-") == 0)
    cd_before(instuctions, old);
  else if (nb_arg == 2 && my_strcmp(instuctions->cmd[1], "-") != 0)
    cd_normal(instuctions);
  free(old);
  free(home);
}
