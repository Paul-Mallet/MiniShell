/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:19:51 by abarahho          #+#    #+#             */
/*   Updated: 2024/10/29 09:35:46 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(*element));
	if (element == NULL)
		return (NULL);
	element->content = content;
	element->next = NULL;
	return (element);
}

// int main()
// {
//     char *str = "Git Push-Up!";
//     t_list *element = ft_lstnew((void *)str);
//     printf("Content: %s\n", (char *)element->content);
//     printf("Pointeur next : %s\n", (char *)element->next);
//     return (0);
// }
