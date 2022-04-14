#ifndef UTIL_H
# define UTIL_H

void	init_data(t_data *data);

void	free_env_list(t_data *data);
void	free_token_list(t_data *data);
void	free_astree(t_ast *ast);

#endif
