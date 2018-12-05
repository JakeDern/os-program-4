/**
 * @author Jake Dern netid: dern2 cslogin: dern
 * @author Alex Dallman netid: adallman2 cslogin: adallman
 */
#include "./537malloc.h"

int main(int argc, char **argv)
{
    void *ptr1 = malloc537(50);
    void *ptr2 = malloc537(20);
    void *ptr3 = malloc537(15);
    void *ptr4 = malloc537(16);
    free537(ptr1);
    free537(ptr2);
    free537(ptr3);
    free537(ptr4);

    return;
}