/*
** cd.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:51:36 2016 julien
** Last update Fri May 06 11:00:59 2016 julien
*/

#include	<dirent.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"str.h"

void	cd_home(t_envi *ins, char *home)
{
  char	dir[1024];

  ins->env = replace_env(ins->env, "OLDPWD=", getcwd(dir, sizeof(dir)));
  if (home != NULL)
    chdir(home);
  ins->env = replace_env(ins->env, "PWD=", getcwd(dir, sizeof(dir)));
}

void	cd_before(t_envi *ins, char *old)
{
  char	dir[1024];
  DIR*	folder;

  folder = opendir(old);
  if (folder)
    {
      ins->env = replace_env(ins->env, "OLDPWD=", getcwd(dir, sizeof(dir)));
      if (old != NULL)
	chdir(old);
      ins->env = replace_env(ins->env, "PWD=", getcwd(dir, sizeof(dir)));
    }
  else
    my_put_error("cd", old);
  closedir(folder);
}

void	cd_normal(t_envi *ins)
{
  char	dir[1024];
  DIR	*folder;

  folder = opendir(ins->cmd[1]);
  if (folder)
    {
      ins->env = replace_env(ins->env, "OLDPWD=", getcwd(dir, sizeof(dir)));
      chdir(ins->cmd[1]);
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
