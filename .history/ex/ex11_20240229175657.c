#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = 0;
    while(i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
        i++;
    }

    i = argc;
    printf("argc=%d\n", argc);
	while(i>=0){
        printf("arg %d: %s\n", i, argv[i]);
        i--;
    }
    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };
    
    int num_states = 4;
    i = 0;  // watch for this
    while(i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }
	//将argv中的值复制到states中，限制复制的数量避免溢出
    int max_copy=0;
    max_copy=num_states<argc?num_states:argc;
    i=0;
    while(i<max_copy){
        states[i] = argv[i];
        i++;
    }
    printf("复制")
    for(i=0;i<max_copy;i++){
        printf("state %d: %s\n", i, states[i]);
    }
    return 0;
}
