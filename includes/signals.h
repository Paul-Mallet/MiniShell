/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:43:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/07 11:57:30 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "./minishell.h"
# include <signal.h>

void	signals_handler(void);
void	ctrl_d_exit(t_data *data, char *prompt);

#endif