#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int myunsetenv(const char *name){
    int i,found=0;
    extern char **environ;
    char **tp=environ;
    char buff[256];
    sprintf(buff,"%s=",name);
    while(*(tp)!=NULL){
        if(strstr(*(tp), buff)!=NULL){
            found=1;
            break;
        }
        tp++;
    }

    if(found){
        do{
            *(tp)=*(tp+1);
            tp++;
        }while(*tp!=NULL);

        return 0;
    }
    return -1;
}

int mysetenv(const char *name, const char *value, int overwrite){
    char *buff=malloc(256);
    sprintf(buff,"%s=%s",name,value);

    if(overwrite>0){
        myunsetenv(name);
        return putenv(buff);
    }else{
        return putenv(buff);
    }
}

int main(int argc, char *argv[], char *env[]){\
    putenv("test=beast");
    putenv("test2=best2");
    mysetenv("test3","beast3",1);
    printf("%s\n",getenv("test"));
    printf("%s\n",getenv("test3"));
    myunsetenv("test");

    printf("---%s\n",getenv("test2"));

    return 0;
}
