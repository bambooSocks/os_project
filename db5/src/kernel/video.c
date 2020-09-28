/* Copyright (c) 1997-2017, FenixOS Developers
   All Rights Reserved.

   This file is subject to the terms and conditions defined in
   file 'LICENSE', which is part of this source code package.
 */

/*! \file video.c This file holds implementations of functions
  presenting output to the VGA screen. */
#include <stdint.h>

/*! Max number of columns in the VGA buffer. */
#define MAX_COLS                (80)
/*! Max number of rows in the VGA buffer. */
#define MAX_ROWS                (25)

struct screen_position
{
 unsigned char character; /*!< The character part of the byte tuple used for
                               each screen position. */
 unsigned char attribute; /*!< The attribute part of the byte tuple used for
                               each screen position. i.e. background and foreground color */
};
/*!< Defines a VGA text mode screen position. */

struct screen
{
 struct screen_position positions[MAX_ROWS][MAX_COLS];
 /*!< The VGA screen. It is organized as a two dimensional array. */
};
/*!< Defines a VGA text mode screen. */

/*! points to the VGA screen. */
static struct screen* const
screen_pointer = (struct screen*) 0xB8000;

int currentRow = 0;
int currentColumn = 0;

void
kprints(const char* string)
{
  while (*string != 0) {
    struct screen_position character = {*string, 0};
    screen_pointer->positions[currentRow][currentColumn] = character;
    currentColumn++;
    string++;
  }
}

void
kprinthex(const register uint32_t value)
{
 /* Implement me! */
}
