#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<pwd.h>

#ifndef PATH_SIZE
#define PATH_SIZE 254 //default
#endif // PATH_SIZE

int main(int argc, char *argv[]){

    struct passwd *pw;
    struct stat st;
    struct DIR *dir;
    struct dirent *d;
    char path[PATH_SIZE],tpath[PATH_SIZE];
    FILE *tf;
    sprintf(path,"/proc");

    if(argc==1 || strcmp(argv[1], "--help")==0){
        fprintf(stderr,"%s < user_name >\n",argv[0]);
        exit(-1);
    }

    if((pw=getpwnam(argv[1]))==NULL){
        fprintf(stderr, "error : not able to look at user %s info\n",argv[1]);
        exit(-1);
    }

    if((dir=(struct DIR*)opendir(path))==NULL){
        fprintf(stderr, "error : not able to open the %s\n",path);
        exit(-1);
    }

    while((d=readdir((DIR*)dir))!=NULL){
        sprintf(tpath,"%s/%s",path,d->d_name);
        if(stat(tpath, &st)==-1){
            fprintf(stderr, "error: not able to stat %s\n.",tpath);
            continue;
        }
        if(isdigit(d->d_name[0])!=0 && (st.st_uid==pw->pw_uid)){
            char buff[256];
            sprintf(tpath, "%s/%s/comm",path,d->d_name);
            if((tf=fopen(tpath, "r"))==NULL){
                fprintf(stderr, "error : not able to read %s\n",tpath);
            }
            fgets(buff, 256,tf);
            fclose(tf);

            buff[strlen(buff)-1]='\0';
            printf("%s : %s\n",buff,d->d_name);
        }
    }
    printf("\n");
    closedir((DIR*)dir);

    return 0;
}
