/*
** main.c for 42sh in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Thu May 26 21:45:20 2016 
** Last update Mon May 30 17:08:19 2016 
*/

#include		"42sh.h"

int			main(int ac, char **av, char **env)
{
  int			i;
  t_plist		plist;
  t_list		*list;
  char			*exit_value;
  char			**my_env;

  (void)ac;
  (void)av;
  my_env = NULL;
  if (env[0] == NULL)
    return (0);
  if (init_list(&plist, &list) == -1)
    return (0);
  i = -1;
  while (env[++i] != NULL)
    env_to_list(&plist, env[i]);
  exit_value = prompt(my_env, &plist);
  free_list(&plist, list);
  return (my_getnbr(exit_value));
}