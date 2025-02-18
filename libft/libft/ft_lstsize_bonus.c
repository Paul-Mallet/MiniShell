/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:27:57 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:42:03 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// int	main(void)
// {
// 	int size;
// 	t_list *elem1 = ft_lstnew("Element 1");
// 	t_list *elem2 = ft_lstnew("Element 2");
// 	t_list *elem3 = ft_lstnew("Element 3");
// 	elem1->next = elem2;
// 	elem2->next = elem3;
// 	size = ft_lstsize(elem1);
// 	printf("La taille de la liste est : %d\n", size);
// 	free(elem1);
// 	free(elem2);
// 	free(elem3);
// 	return (0);
// }