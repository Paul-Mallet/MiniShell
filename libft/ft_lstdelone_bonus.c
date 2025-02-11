/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:27:49 by abarahho          #+#    #+#             */
/*   Updated: 2024/11/01 11:47:39 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	del(void *content)
// {
// 	free(content);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	if (lst->content != NULL)
		(*del)(lst->content);
	free (lst);
}

// int	main(void)
// {
// 	t_list	*elem1 = ft_lstnew(strdup("Element 1"));
// 	t_list	*elem2 = ft_lstnew(strdup("Element 2"));
// 	t_list	*elem3 = ft_lstnew(strdup("Element 3"));

// 	elem1->next = elem2;
// 	elem2->next = elem3;
// 	ft_lstdelone(elem3, del);
// 	t_list	*current = elem1;
// 	while (current != NULL)
// 	{
// 		printf("Element: %s\n", (char *)current->content);
// 		current = current->next;
// 	}
// 	ft_lstdelone(elem2, del);
// 	ft_lstdelone(elem1, del);
// 	return (0);
// }