#ifndef TEST_H
# define TEST_H

# include <stdio.h>

# define TEST(name, condition) \
	if (condition) \
		printf("✅ PASS: %s\n", name); \
	else \
		printf("❌ FAIL: %s\n", name);
#endif
