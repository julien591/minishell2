/*
** env.h for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/include
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 14:40:32 2016 julien
** Last update Fri May 06 14:40:39 2016 julien
*/

#ifndef		ENV_H_
# define	ENV_H_

typedef struct s_envi
{
  char	**env;
  char	*envp;
  char	**path;
  char	**cmd;
}t_envi;

char	*my_getenv(char **env);
char	*my_gethome(char **env);
char	*my_get_old_pwd(char **env);
char	**copy_env(char **env);
char	**replace_env(char **env, char *line, char *to_replace);
void	new_env(t_envi *ins);

#endif /* !ENV_H_ */
