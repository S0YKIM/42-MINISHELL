#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

/*
 * Builtin Functions
*/
int		ft_env(t_data *data);
int		ft_pwd(void);
int		ft_export(char **cmds, t_data *data);
int		ft_cd(char **cmds, t_data *data);

#endif
