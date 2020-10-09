/* Copyright (c) 1997-2017, FenixOS Developers
   All Rights Reserved.

   This file is subject to the terms and conditions defined in
   file 'LICENSE', which is part of this source code package.
 */

/*! \file kernel_customization.c This file holds definitions
  for the kernel that you can change and alter. */

#include <stdint.h>
#include <instruction_wrappers.h>
#include <sysdefines.h>

#include "kernel.h"

void kernel_late_init(void)
{
 /* Set up the first thread. For now we do not set up a process. That is
   for you to do later. */
 threads[0].eip = executable_table[0];

 processes[0].number_of_threads = 1;
 threads[0].process = &(processes[0]);
 
 /* Go to user space. */
 go_to_user_space();
}

void handle_system_call(void)
{
 switch (current_thread->eax)
 {
  case SYSCALL_VERSION:
  {
   current_thread->eax = 0x00010000;
   break;
  }
  case SYSCALL_PRINTS:
  {
    char *string = (char *) current_thread->edi;
    kprints(string);
    current_thread->eax = ALL_OK; 
  }
  case SYSCALL_PRINTHEX:
  {
    uint32_t value = current_thread->edi;
    kprinthex(value);
    current_thread->eax = ALL_OK; 
  }

  default:
  {
   /* Unrecognized system call. Not good. */
   current_thread->eax = ERROR_ILLEGAL_SYSCALL;
  }
 }

 go_to_user_space();
}

/* Add more definitions here if you need. */
