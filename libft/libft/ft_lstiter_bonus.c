/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:36:24 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:35:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		(*f)(current->content);
		current = current->next;
	}
}

// static void	replace_a_with_o(void *content)
// {
//     char *str;
//     int i;

// 	str = (char *)content;
// 	i = 0;
//     while (str[i] != '\0')
//     {
//         if (str[i] == 'a')
//             str[i] = 'o';
//         i++;
//     }
// }
// int main(void)
// {
//     t_list *elem1;
//     t_list *elem2;
//     t_list *elem3;
// 	t_list *current;

// 	elem1 = ft_lstnew(ft_strdup("apple"));
// 	elem2 = ft_lstnew(ft_strdup("banana"));
// 	elem3 = ft_lstnew(ft_strdup("avocado"));
//     elem1->next = elem2;
//     elem2->next = elem3;
// 	current = elem1;
//     printf("Before ft_lstiter :\n");
//     while (current != NULL)
//     {
//         printf("%s\n", (char *)current->content);
//         current = current->next;
//     }
//     ft_lstiter(elem1, replace_a_with_o);
//     printf("\nAfter ft_lstiter :\n");
//     current = elem1;
//     while (current != NULL)
//     {
//         printf("%s\n", (char *)current->content);
//         current = current->next;
//     }
//     ft_lstclear(&elem1, free);
//     return (0);
// }
// cc ft_lstnew.c ft_lstiter.c ft_strdup.c ft_lstclear.c ft_strlen.c