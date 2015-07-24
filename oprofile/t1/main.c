#include <unistd.h>
#include <sched.h>

/* Declare global data */
struct shared_data_nonalign common_aln;

/*
 * Shared data being modified by two threads running on different CPUs.
 */
/* shared structure between two threads which will be optimized later*/
struct shared_data_align {
    unsigned int num_proc1;
    unsigned int num_proc2;
};
/* 
 * Shared structure between two threads remains unchanged (non optimized)
 * This is required in order to collect some samples for the L2_LINES_IN event.
 */
struct shared_data_nonalign {
    unsigned int num_proc1;
    unsigned int num_proc2;
};

/*
 * The routine below is called by the cloned thread, to increment the num_proc2 
 * element of common and common_aln structure in loop.
 */
int func1(struct shared_data_align *com)
{
    int i, j;
    /* Increment the value of num_proc2 in loop */
    for (j = 0; j < 200; j++)
        for (i = 0; i < 100000; i++) {
            com->num_proc2++;
        }
    /* Increment the value of num_proc2 in loop */
    for (j = 0; j < 200; j++)
        for (i = 0; i < 100000; i++) {
            common_aln.num_proc2++;
        }
}

int main()
{
    /*
     * In the example program below, the parent process creates a clone
     * thread sharing its memory space. The parent thread running on one CPU 
     * increments the num_proc1 element of the common and common_aln. The cloned
     * thread running on another CPU increments the value of num_proc2 element of
     * the common and common_aln structure.
     */
    /*Declare local shared data */
    struct shared_data_align common;
    pid_t pid;
    /* Now clone a thread sharing memory space with the parent process */
    if ((pid = clone(func1, buff+8188, CLONE_VM, &common)) < 0) {
        perror("clone");
        exit(1);
    }

    /* Increment the value of num_proc1 in loop */
    for (j = 0; j < 200; j++)
        for(i = 0; i < 100000; i++) {
            common.num_proc1++;
        }
    /* Increment the value of num_proc1 in loop */
    for (j = 0; j < 200; j++)
        for(i = 0; i < 100000; i++) {
            common_aln.num_proc1++;
        }

    return 0;
}
