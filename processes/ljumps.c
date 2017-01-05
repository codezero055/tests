#include<stdio.h>
#include<setjmp.h>

jmp_buf jb;


void f1(void){
    if(setjmp(jb)==1){
        printf("returned to ");
    }
    printf("f1() \n");
    //return;
}
void f2(void){
    printf("f2() \n");
}

void f3(void){
    printf("f3() \n");
}

int main(){
    printf("in main\n");
    f1();
    f2();
    f3();
    longjmp(jb,1);

    //this funcs not working Y ??  test karun bag 1 vela (down vale funcs not working.)
    f1();
    f2();
    f3();

    return 0;
}

