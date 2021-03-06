/*! \file \brief The first user program - simply tests the thread creation routine
 *
 */
#include <scwrapper.h>

void thread(void)
{
 prints("Thread started! \n");
 
 terminate();
}

char thread_stack[4096];

int 
main(int argc, char* argv[])
{

 while(1) {
  if (ALL_OK != createthread(thread, thread_stack+4096))
  {
    prints("createthread failed!\n");
    return 1;
  }

  yield();
 }

 return 0;
}
