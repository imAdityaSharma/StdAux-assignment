// Question-3 Which line will show error and why?
#include<stdio.h>
int main() {
    char *a = "India";
    char b[] = "India";
    a = a+1;//line 5:::
    b = b+1;//line 6::: will throw an error
    return 0;
}



/*
Here in line 'char *a="india";' is a pointer so line 5 will not result in any error ass a=a+1 will increment pointer a to next character.
Where as in line 'char b[]="India";' it is declared as a literal string. So line 6 is trying to modify a constant string which is not possible.

The difference between line 5 and line 6 is that line 5 increments the pointer 'a' to point to the next character in the string, 
while line 6 increments the array b as a whole.

*/