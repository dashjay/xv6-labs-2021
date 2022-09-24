#include "kernel/types.h"
#include "user/user.h"


void prime(int *p_left){
    int from_left;
    if (read(p_left[0], &from_left,4) == 0){
        exit(0);
    }else{
        printf("prime %d\n", from_left);
    }
    int p_right[2];
    if (pipe(p_right)<0){
        exit(1);
    }

    if (fork() == 0){
        close(p_right[1]);
        prime(p_right);
        close(p_right[0]);
    }else{
        close(p_right[0]);
        int next;
        while(read(p_left[0], &next, 4)!=0){
                if (next %from_left != 0){
                    write(p_right[1], &next, 4);
                }
        }
        close(p_right[1]);
        wait(0);
        exit(0);
    }
}

int main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    if (fork() > 0){
        close(p[0]);
        for(int i = 2; i <= 35;i ++){
            write(p[1], &i, 4);
        }
        close(p[1]);
        wait(0);
        exit(0);
    }else{
        close(p[1]);
        prime(p);
        close(p[0]);
        exit(0);
    }
}