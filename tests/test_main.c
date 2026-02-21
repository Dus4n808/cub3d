#include "test.h"

void	test_open_file(void);
void	test_extension(void);
void	test_fill_map(void);

int	main(void)
{
	printf("🧪 Running all tests...\n");
	test_open_file();
	test_extension();
	test_fill_map();
	printf("\n✅ Done.\n");
	return (0);
}
