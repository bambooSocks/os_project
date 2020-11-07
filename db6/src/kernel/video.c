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
    if (*string == '\n') {
      currentRow++;
      currentColumn = 0;
    } else {
      struct screen_position character = {*string, 0x0F};
      screen_pointer->positions[currentRow][currentColumn] = character;
      currentColumn++;
    }
    string++;
  }
}

void
kprinthexdigit(uint32_t digit) {
  char output[2] = {0};
  if (digit >= 0 && digit <=9 ) {
    output[0] = '0' + digit;
  } else if (digit >= 10 && digit <= 15) {
    output[0] = 'A' + (digit - 10);
  } else {
    return;
  }
  kprints(output);
}

void
kprinthex(const register uint32_t value)
{
  uint32_t output[4] = {0};
  uint32_t decimal = value;

  if (decimal == 0) {
    kprinthexdigit(0);
    return;
  }
  
  uint8_t hex_digit_count = 0;
  while (decimal != 0) {
    output[hex_digit_count] = decimal % 16;
    decimal /= 16;
    hex_digit_count++;
  }

  for (int i = hex_digit_count; i < 0; i--) {
    kprinthexdigit(output[i]);
  }
  kprints("skurvenina\n");
}
