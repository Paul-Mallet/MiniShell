/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:27:52 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:41:52 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int main(void)
// {
//     t_list *elem1 = ft_lstnew("Element 1");
//     t_list *elem2 = ft_lstnew("Element 2");
//     t_list *elem3 = ft_lstnew("Element 3");
//     elem1->next = elem2;
//     elem2->next = elem3;
//     t_list *last = ft_lstlast(elem1);
//     printf("The last element is : %s\n", (char *)last->content);
//     free(elem1);
//     free(elem2);
//     free(elem3);
//     return (0);
// }