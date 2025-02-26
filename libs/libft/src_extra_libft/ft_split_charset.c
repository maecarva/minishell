/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:38:01 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 21:40:09 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_is_char_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_words(char *str, char *charset)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (ft_is_char_in_charset(str[i], charset))
			i++;
		if (!ft_is_char_in_charset(str[i], charset) && str[i] != '\0')
		{
			words++;
			while (!ft_is_char_in_charset(str[i], charset) && str[i] != '\0')
				i++;
		}
	}
	return (words);
}

char	*ft_add_word(char *str, char *charset, int *j)
{
	int		current_word_len;
	char	*word;
	int		i;

	i = 0;
	current_word_len = 0;
	while (ft_is_char_in_charset(str[*j], charset))
		(*j)++;
	while (!ft_is_char_in_charset(str[*j + current_word_len], charset)
		&& str[*j + current_word_len] != '\0')
		current_word_len++;
	word = malloc(sizeof(char) * (current_word_len + 1));
	if (!word)
		return (NULL);
	while (i < current_word_len)
	{
		word[i] = str[*j];
		i++;
		*j += 1;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**result;
	int		i;
	int		j;
	int		words;

	i = 0;
	j = 0;
	words = ft_count_words(str, charset);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	while (i < words)
	{
		result[i] = ft_add_word(str, charset, &j);
		i++;
	}
	result[i] = NULL;
	return (result);
}
