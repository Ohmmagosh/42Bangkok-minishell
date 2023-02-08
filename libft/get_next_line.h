/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:39:39 by psuanpro          #+#    #+#             */
/*   Updated: 2023/02/08 20:19:17 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_len_nl_gnl(char *s);
int		ft_strlen_gnl(char *s);
int		ft_chk_stash_gnl(char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strcpy_gnl(char *s);
char	*ft_clear_stash_gnl(char *s);
char	*get_next_line(int fd);

#endif
