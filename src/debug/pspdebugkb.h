/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  pspdebugkb.h - Simple screen debug keyboard
 *
 * Copyright (c) 2006 Mike Mallett <mike@nerdcore.net>
 *
 * $Id: pspdebugkb.h 2110 2006-12-19 14:50:27Z tyranid $
 */

#ifndef __PSPDEBUGKB_H
#define __PSPDEBUGKB_H

#ifdef __cplusplus
extern "C" {
#endif

enum PspDebugKbSettings {
  /** Maximum string length */
  PSP_DEBUG_KB_MAXLEN = 40,
  /** Place the box' upper-left corner at this location */
  PSP_DEBUG_KB_BOX_X = 6,
  PSP_DEBUG_KB_BOX_Y = 8,
  /** FG and BG colour of unhighlighted characters */
  PSP_DEBUG_KB_CHAR_COLOUR = 0xffffffff,
  PSP_DEBUG_KB_BACK_COLOUR = 0xff000000,
  /** FG and BG colour of highlighted character */
  PSP_DEBUG_KB_CHAR_HIGHLIGHT = 0xff00ff00,
  PSP_DEBUG_KB_BACK_HIGHLIGHT = 0xff101010,
  /** Indent the printed characters by (X_OFFSET,Y_OFFSET) */
  PSP_DEBUG_KB_OFFSET_X = 6,
  PSP_DEBUG_KB_OFFSET_Y = 4,
  /** Distance from one character to the next */
  PSP_DEBUG_KB_SPACING_X = 3,
  PSP_DEBUG_KB_SPACING_Y = 2,
  /** Number of columns/rows (respectively) in charTable(s) */
  PSP_DEBUG_KB_NUM_CHARS = 13,
  PSP_DEBUG_KB_NUM_ROWS = 4,
  /** Box width and height */
  PSP_DEBUG_KB_BOX_WIDTH = (PSP_DEBUG_KB_NUM_CHARS * PSP_DEBUG_KB_SPACING_X) + (2 * PSP_DEBUG_KB_OFFSET_X),
  PSP_DEBUG_KB_BOX_HEIGHT = ((PSP_DEBUG_KB_NUM_ROWS + 1) * PSP_DEBUG_KB_SPACING_Y) + PSP_DEBUG_KB_OFFSET_Y,
  /** Array index of commandRow */
  PSP_DEBUG_KB_COMMAND_ROW = 4,
  /** Number of commands on bottom row */
  PSP_DEBUG_KB_NUM_COMMANDS = 5
};

/**
 * Switch charTable when SHIFT is pressed
 *
 * @param shiftState - Pointer to an int indicating Caps Lock
 */
void pspDebugKbShift(int *shiftState);

/**
 * Draw the specified key on the keyboard.
 *
 * @param row - The row of the character to print (in charTable)
 * @param col - The column of the character to print (in charTable)
 * @param highlight - 0 for plain; otherwise highlighted
 */
void pspDebugKbDrawKey(int row, int col, int highlight);

/**
 * Draw the string at the top of the box
 *
 * @param str - The string to print
 */
void pspDebugKbDrawString(char *str);

/**
 * Clear the area where the box resides.
 * Called from pspDebugKbDrawBox and pspDebugKbInit (on exit).
 */
void pspDebugKbClearBox();

/**
 * Draw the entire box on the desbug screen.
 * Called from shift() and doInputBox(char*)
 */
void pspDebugKbDrawBox();

/**
 * Make the text box happen
 *
 * @param str - The string to edit
 */
void pspDebugKbInit(char *str);

#ifdef __cplusplus
}
#endif

#endif
