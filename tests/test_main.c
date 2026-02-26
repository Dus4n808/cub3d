#include "test.h"
#include "cub3d.h"

void	test_open_file(void);
void	test_extension(void);
void	test_all_line(void);


int	main(void)
{
	printf("🧪 Running all tests...\n");
	test_open_file();
	test_extension();
	test_all_line();
	printf("\n✅ Done.\n");
	return (0);
}
