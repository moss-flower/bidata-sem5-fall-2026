#include <stdio.h>
#include <stdlib.h>

int main() {
	char buff[32];
	fgets(buff,32,stdin);
	printf(buff);
}
