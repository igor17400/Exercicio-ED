#include <stdio.h>
#include <stdlib.h>

char *return_and_pass(char s[])	// OR char return_and_pass(char *s)
{
	s[0]='A'; //modify passed string
	return s;	//return it
}

int main()
{
	char a[]="Hello!";
	printf("%s",return_and_pass(a));
	return 0;
}
