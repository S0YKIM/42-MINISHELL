/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:43:51 by sokim             #+#    #+#             */
/*   Updated: 2022/05/03 18:05:51 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# define TRUE		1
# define FALSE		0
# define ERROR		-1
# define SUCCESS	0
# define FAILURE	1

# define REMOVE		-2
# define CONTINUE	-3

# define T_CMD	0
# define T_RDR	1
# define T_PL	2
# define T_PIPE	3

# define READ	0
# define WRITE	1

# define SHELL_NAME	"microshell"

# define HEREDOC_PATH	".heredoc"
# define ART_PATH		"art.txt"

# define BUFFER_SIZE 1024
# define MAX_FD 256
# define FLAG_ERROR -1
# define FLAG_SUCCESS 1
# define FLAG_EOF 0

#endif
