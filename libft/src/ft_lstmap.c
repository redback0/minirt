/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:30 by njackson          #+#    #+#             */
/*   Updated: 2024/03/18 16:11:04 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*out;
	t_list	**out_last;
	void	*next_content;

	if (!lst || !f || !del)
		return (0);
	out_last = &out;
	while (lst)
	{
		next_content = (*f)(lst->content);
		*out_last = ft_lstnew(next_content);
		if (!(*out_last) || !next_content)
		{
			if (next_content)
				del(next_content);
			ft_lstclear(&out, del);
			return (0);
		}
		out_last = &(*out_last)->next;
		lst = lst->next;
	}
	return (out);
}
