/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaroni <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:19:55 by lubaroni          #+#    #+#             */
/*   Updated: 2026/04/13 17:19:56 by lubaroni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdio.h>

# define TEST(name, condition) \
	if (condition) \
		printf("✅ PASS: %s\n", name); \
	else \
		printf("❌ FAIL: %s\n", name);
#endif
