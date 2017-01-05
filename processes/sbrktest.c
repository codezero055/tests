#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    printf("%10p\n",sbrk(0));
    return 0;
}
