/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz </var/spool/mail/bkuntz>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:08:25 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/04 15:09:17 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include "../devs/dev.h"

void	create_thread(t_dev *coders, int len, int *queue);
int	close_threads(t_dev *coders, int len);
#endif
