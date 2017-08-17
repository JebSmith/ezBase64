#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ezBase64.h"

int main()
{
	char*Greeting = "Hello World";
	char*Encoded = ezBase64Encode(Greeting,strlen(Greeting));
	char*Decoded = ezBase64Decode(Encoded,strlen(Encoded));
	printf("%s\n%s\n%s\n",Greeting,Encoded,Decoded);
	system("pause");
	free(Decoded); //free da memory, man
	free(Encoded);
	return 0;
}

