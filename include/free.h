/*
** free.h for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/include
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 14:40:45 2016 julien
** Last update Thu May 26 18:36:02 2016 Julien Leleu
*/

#ifndef		FREE_H_
# define	FREE_H_

void		free_all(t_envi *instuctions, char *s);
void		free_command(char *s, char **cmd);
void		free_path(char *envp, char **path);
void		free_env(char **env);
void		free_cmd(char **cmd);
void		special_free(char ***command, int nb);

#endif /* !FREE_H_ */
