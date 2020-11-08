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

int lastThreadIdx = 0;

void kernel_late_init(void)
{
 /* Set up the first thread. For now we do not set up a process. That is
   for you to do later. */
 for (int i = 0; i < MAX_THREADS; i++) {
   threads[i].used = 0;
 }
 
 for (int i = 0; i < MAX_PROCESSES; i++) {
   processes[i].used = 0;
 }

 threads[0].eip = executable_table[0];

 processes[0].number_of_threads = 1;
 processes[0].used = 1;
 threads[0].process = &(processes[0]);
 threads[0].used = 1;
 
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
    break;
  }
  case SYSCALL_PRINTHEX:
  {
    uint32_t value = current_thread->edi;
    kprinthex(value);
    current_thread->eax = ALL_OK;
    break; 
  }
  case SYSCALL_CREATEPROCESS:
  {
    uint32_t program = current_thread->edi;
    uint8_t foundProcess = 0;
    for (uint8_t i = 0; i < MAX_PROCESSES; i++) {
      if (!processes[i].used)
      {
        int threadIdx = -1;
        for (uint8_t j = 0; j < MAX_THREADS; j++) {
          if (!threads[j].used) {
            threadIdx = j;
            break;
          }
        }
        if (threadIdx == -1) {
          current_thread->eax = ERROR;
          return;
        }
        threads[threadIdx].eip = executable_table[program];
        processes[i].number_of_threads = 1;
        processes[i].used = 1;
        threads[threadIdx].process = &(processes[i]);
        threads[threadIdx].used = 1;
        foundProcess = 1;
        break;
      }
    }
    current_thread->eax = foundProcess ? ALL_OK : ERROR;
    break;
  }
  case SYSCALL_YIELD:
  {
    int foundNextThread = 0;
    int nextThreadIdx = lastThreadIdx + 1;
    while (!foundNextThread) {
      if (nextThreadIdx >= MAX_THREADS) {
        nextThreadIdx = 0;
      }
      if (threads[nextThreadIdx].used) {
        current_thread = &(threads[nextThreadIdx]);
        lastThreadIdx = nextThreadIdx;
        foundNextThread = 1;
      }
      nextThreadIdx++;
    }
    current_thread->eax = ALL_OK;
    break;
  }
  case SYSCALL_TERMINATE:
  {
    current_thread->used = 0;
    current_thread->process->number_of_threads--;
    if (current_thread->process->number_of_threads <= 0) {
      current_thread->process->used = 0;
    }
    current_thread = 0;
    for (int i = 0; i < MAX_THREADS; i++) {
      if (threads[i].used) {
        current_thread = &(threads[i]);
        lastThreadIdx = i;
        break;
      }
    }
    if (current_thread == 0) {
      kprints("SYSTEM TERM\n");
    }
    break;
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
