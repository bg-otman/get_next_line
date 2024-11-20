#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>
int main()
{
	int fd = open("tst.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("error");
		return 1;
	}
	char *line;
	while((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
		line = NULL;
	}
	printf("|%s|", line);
	close(fd);
	return 0;
}
