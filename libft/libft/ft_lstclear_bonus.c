/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:35:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:41:43 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// void	del(void *content)
// {
// 	free(content);
// }

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

// int main(void) {
//     t_list *head;
//     t_list *second;
//     t_list *third;
//     int *val1;
//     int *val2;
//     int *val3;
//     val1 = malloc(sizeof(int));
//     val2 = malloc(sizeof(int));
//     val3 = malloc(sizeof(int));
//     *val1 = 42;
//     *val2 = 123;
//     *val3 = 561;
//     head = ft_lstnew(val1);
//     second = ft_lstnew(val2);
//     third = ft_lstnew(val3);
//     head->next = second;
//     second->next = third;
//     printf("Avant ft_lstclear :\n");
//     t_list *temp = head;
//     while (temp != NULL)
//     {
//         printf("%d\n", *(int *)temp->content);
//         temp = temp->next;
//     }
//     ft_lstclear(&head, del);
//     return (0);
// }