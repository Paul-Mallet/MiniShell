/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:27:45 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/10 11:43:55 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

// int	main(void)
// {
// 	t_list	*elem1 = ft_lstnew("Element 1");
// 	t_list	*elem2 = ft_lstnew("Element 2");
// 	t_list	*elem3 = ft_lstnew("Element 3");
// 	t_list	*new_elem = ft_lstnew("New Element");
// 	elem1->next = elem2;
// 	elem2->next = elem3;
// 	ft_lstadd_back(&elem1, new_elem);
// 	t_list	*current = elem1;
// 	while (current != NULL)
// 	{
// 		printf("Element: %s\n", (char *)current->content);
// 		current = current->next;
// 	}
// 	free(elem1);
// 	free(elem2);
// 	free(elem3);
// 	free(new_elem);
// 	return (0);
// }