/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:58:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:41:57 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// void	del(void *content)
// {
// 	free(content);
// }

static t_list	*create_new_elem(void *(*f)(void *), void *content)
{
	t_list	*new_elem;
	void	*new_cntnt;

	new_cntnt = f(content);
	new_elem = ft_lstnew(new_cntnt);
	if (new_elem == NULL)
	{
		free(new_cntnt);
		return (NULL);
	}
	return (new_elem);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;
	t_list	*current;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_elem = create_new_elem(f, lst->content);
	if (new_elem == NULL)
		return (NULL);
	new_list = new_elem;
	current = new_list;
	lst = lst->next;
	while (lst)
	{
		new_elem = create_new_elem(f, lst->content);
		if (new_elem == NULL)
		{
			ft_lstclear(&new_list, del);
			break ;
		}
		current->next = new_elem;
		current = new_elem;
		lst = lst->next;
	}
	return (new_list);
}

// void *get_length(void *content)
// {
//     int *length = malloc(sizeof(int));
//     if (length == NULL)
//         return (NULL);
//     *length = strlen((char *)content);
//     return length;
// }
// void print_list(t_list *lst)
// {
//     while (lst)
//     {
//         printf("%d -> ", *(int *)lst->content);
//         lst = lst->next;
//     }
//     printf("NULL\n");
// }
// int main()
// {
//     t_list *list = ft_lstnew(strdup("hello!"));
//     ft_lstadd_back(&list, ft_lstnew(strdup("world")));
//     ft_lstadd_back(&list, ft_lstnew(strdup("this")));
//     ft_lstadd_back(&list, ft_lstnew(strdup("is")));
//     ft_lstadd_back(&list, ft_lstnew(strdup("libft")));
//     t_list *new_list = ft_lstmap(list, get_length, del);
//     printf("Lengths of strings in the list:\n");
//     print_list(new_list);
//     ft_lstclear(&list, del);
//     ft_lstclear(&new_list, free);
//     return (0);
// }