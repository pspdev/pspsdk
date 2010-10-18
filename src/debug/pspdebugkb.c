/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  pspdebugkb.c - Simple screen debug keyboard
 *
 * Copyright (c) 2006 Mike Mallett <mike@nerdcore.net>
 *
 * $Id: pspdebugkb.c 2112 2006-12-22 10:53:20Z tyranid $
 */
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>
#include "pspdebugkb.h"

static char loCharTable[PSP_DEBUG_KB_NUM_ROWS][PSP_DEBUG_KB_NUM_CHARS] = {
  { '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=' },
  { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\' },
  { '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\0' },
  { '\0', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0', '\0' }
};

static char hiCharTable[PSP_DEBUG_KB_NUM_ROWS][PSP_DEBUG_KB_NUM_CHARS] = {
  { '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+' },
  { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '|' },
  { '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '\0' },
  { '\0', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\0', '\0' }
};

static char *commandRow[] = { "Shift", "[    ]", "Back", "Clear", "Done" };

char charTable[PSP_DEBUG_KB_NUM_ROWS][PSP_DEBUG_KB_NUM_CHARS];

/* Switch charTable when Shift is pressed */
void pspDebugKbShift(int* shiftState) {
  int i, j;

  if (*shiftState != 0) {
    for (i=0; i<PSP_DEBUG_KB_NUM_ROWS; i++) {
      for (j=0; j<PSP_DEBUG_KB_NUM_CHARS; j++) {
	charTable[i][j] = loCharTable[i][j];
      }
    }
    *shiftState = 0;
  } else {
    for (i=0; i<PSP_DEBUG_KB_NUM_ROWS; i++) {
      for (j=0; j<PSP_DEBUG_KB_NUM_CHARS; j++) {
	charTable[i][j] = hiCharTable[i][j];
      }
    }
    *shiftState = 1;
  }
  pspDebugKbDrawBox();
}

void pspDebugKbDrawKey(int row, int col, int highlight) {
  int i;
  int spacing = 0;
  int charsTo = 0;
  int charsTotal = 0;

  if (highlight) {
    pspDebugScreenSetTextColor(PSP_DEBUG_KB_CHAR_HIGHLIGHT);
    pspDebugScreenSetBackColor(PSP_DEBUG_KB_BACK_HIGHLIGHT);
  } else {
    pspDebugScreenSetTextColor(PSP_DEBUG_KB_CHAR_COLOUR);
    pspDebugScreenSetBackColor(PSP_DEBUG_KB_BACK_COLOUR);
  }

  if (row == PSP_DEBUG_KB_COMMAND_ROW) {
    for (i=0; i<PSP_DEBUG_KB_NUM_COMMANDS; i++) {
      charsTotal += strlen(commandRow[i]);
      if (i < col) { charsTo += strlen(commandRow[i]); }
    }
    spacing = (PSP_DEBUG_KB_BOX_WIDTH - charsTotal) / (PSP_DEBUG_KB_NUM_COMMANDS + 1);
    pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + (spacing * (col + 1)) + charsTo, PSP_DEBUG_KB_BOX_Y + (PSP_DEBUG_KB_SPACING_Y * (row + 2)));
    pspDebugScreenPrintf("%s", commandRow[col]);
  } else {
    pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + PSP_DEBUG_KB_OFFSET_X + (PSP_DEBUG_KB_SPACING_X * col), PSP_DEBUG_KB_BOX_Y + (PSP_DEBUG_KB_SPACING_Y * (row + 2)));
    if (charTable[row][col] == '\0') {
      pspDebugScreenPrintf(" ");
    } else {
    pspDebugScreenPrintf("%c", charTable[row][col]);
  }
  }
}

void pspDebugKbClearBox() {
  int i, j;

  pspDebugScreenSetTextColor(PSP_DEBUG_KB_CHAR_COLOUR);
  pspDebugScreenSetBackColor(PSP_DEBUG_KB_BACK_COLOUR);

  for (i = PSP_DEBUG_KB_BOX_X; i <= PSP_DEBUG_KB_BOX_X + PSP_DEBUG_KB_BOX_WIDTH; i++) {
    for (j = PSP_DEBUG_KB_BOX_Y; j <= PSP_DEBUG_KB_BOX_Y + PSP_DEBUG_KB_BOX_HEIGHT; j++) {
      pspDebugScreenSetXY(i, j);
      pspDebugScreenPrintf(" ");
    }
  }
}

void pspDebugKbDrawBox() {
  int i, j;

  pspDebugScreenSetTextColor(PSP_DEBUG_KB_CHAR_COLOUR);
  pspDebugScreenSetBackColor(PSP_DEBUG_KB_BACK_COLOUR);

  pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X, PSP_DEBUG_KB_BOX_Y);
  pspDebugScreenPrintf("+");
  pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X, PSP_DEBUG_KB_BOX_Y + PSP_DEBUG_KB_BOX_HEIGHT);
  pspDebugScreenPrintf("+");
  pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + PSP_DEBUG_KB_BOX_WIDTH, PSP_DEBUG_KB_BOX_Y);
  pspDebugScreenPrintf("+");
  pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + PSP_DEBUG_KB_BOX_WIDTH, PSP_DEBUG_KB_BOX_Y + PSP_DEBUG_KB_BOX_HEIGHT);
  pspDebugScreenPrintf("+");

  for (i = 1; i < PSP_DEBUG_KB_BOX_WIDTH; i++) {
    pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + i, PSP_DEBUG_KB_BOX_Y);
    pspDebugScreenPrintf("-");
    pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + i, PSP_DEBUG_KB_BOX_Y + PSP_DEBUG_KB_BOX_HEIGHT);
    pspDebugScreenPrintf("-");
  }

  for (i = 1; i < PSP_DEBUG_KB_BOX_HEIGHT; i++) {
    pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X, PSP_DEBUG_KB_BOX_Y + i);
    pspDebugScreenPrintf("|");
    pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + PSP_DEBUG_KB_BOX_WIDTH, PSP_DEBUG_KB_BOX_Y + i);
    pspDebugScreenPrintf("|");
  }

  for (i = 0; i < PSP_DEBUG_KB_NUM_ROWS; i++) {
    for (j = 0; j < PSP_DEBUG_KB_NUM_CHARS; j++) {
      pspDebugKbDrawKey(i, j, 0);
    }
  }

  for (i = 0; i < PSP_DEBUG_KB_NUM_COMMANDS; i++) {
    pspDebugKbDrawKey(PSP_DEBUG_KB_COMMAND_ROW, i, 0);
  }
}

void pspDebugKbDrawString(char* str) {
  int i;

  pspDebugScreenSetTextColor(PSP_DEBUG_KB_CHAR_COLOUR);
  pspDebugScreenSetBackColor(PSP_DEBUG_KB_BACK_COLOUR);

  pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + ((PSP_DEBUG_KB_BOX_WIDTH - PSP_DEBUG_KB_MAXLEN) / 2), PSP_DEBUG_KB_BOX_Y + 1);
  for (i=0; i<PSP_DEBUG_KB_MAXLEN; i++) {
    pspDebugScreenPrintf("_");
  }

  pspDebugScreenSetXY(PSP_DEBUG_KB_BOX_X + ((PSP_DEBUG_KB_BOX_WIDTH - PSP_DEBUG_KB_MAXLEN) / 2), PSP_DEBUG_KB_BOX_Y + 1);
  pspDebugScreenPrintf("%s", str);
}

void pspDebugKbInit(char* str) {
  int row = PSP_DEBUG_KB_COMMAND_ROW;
  int col = PSP_DEBUG_KB_NUM_COMMANDS - 1;
  int shifted = 1;
  int inputDelay = 200000;

  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

  SceCtrlData input, lastinput;
  sceCtrlReadBufferPositive(&input, 1);
  sceCtrlReadBufferPositive(&lastinput, 1);

  unsigned int inputTime = input.TimeStamp;

  pspDebugKbClearBox();

  // Initialize charTable
  pspDebugKbShift(&shifted);

  pspDebugKbDrawBox();
  pspDebugKbDrawKey(row, col, 1);
  pspDebugKbDrawString(str);

  while (1) {
    sceCtrlReadBufferPositive(&input, 1);

    if (input.Buttons & PSP_CTRL_LEFT && col > 0
	&& (row == PSP_DEBUG_KB_COMMAND_ROW || charTable[row][col - 1])
	&& (input.Buttons != lastinput.Buttons || input.TimeStamp >= inputTime + inputDelay)) {
      // Unhighlight the old character
      pspDebugKbDrawKey(row, col, 0);

      // Print the new character highlighted
      pspDebugKbDrawKey(row, --col, 1);

      // Update inputTime
      inputTime = input.TimeStamp;
    }
    if (input.Buttons & PSP_CTRL_RIGHT
	&& ((row == PSP_DEBUG_KB_COMMAND_ROW && col < PSP_DEBUG_KB_NUM_COMMANDS - 1)
	    || (row != PSP_DEBUG_KB_COMMAND_ROW && col < PSP_DEBUG_KB_NUM_CHARS - 1
		&& charTable[row][col + 1]))
	&& (input.Buttons != lastinput.Buttons || input.TimeStamp >= inputTime + inputDelay)) {
      pspDebugKbDrawKey(row, col, 0);
      pspDebugKbDrawKey(row, ++col, 1);
      inputTime = input.TimeStamp;
    }
    if (input.Buttons & PSP_CTRL_UP && row > 0
	&& (input.Buttons != lastinput.Buttons || input.TimeStamp >= inputTime + inputDelay)) {
      if (row == PSP_DEBUG_KB_COMMAND_ROW) {
	pspDebugKbDrawKey(row, col, 0);
	if (col == PSP_DEBUG_KB_NUM_COMMANDS - 1) {
	  col = PSP_DEBUG_KB_NUM_CHARS - 1;
	} else {
	  col = (col * (PSP_DEBUG_KB_NUM_CHARS - 1)) / (PSP_DEBUG_KB_NUM_COMMANDS - 1);
	}
	do {
	  row--;
	} while (charTable[row][col] == '\0' && row > 0);
	pspDebugKbDrawKey(row, col, 1);
      } else if (charTable[row - 1][col]) {
	pspDebugKbDrawKey(row, col, 0);
	pspDebugKbDrawKey(--row, col, 1);
      }
      inputTime = input.TimeStamp;
    }
    if (input.Buttons & PSP_CTRL_DOWN && row != PSP_DEBUG_KB_COMMAND_ROW
	&& (input.Buttons != lastinput.Buttons || input.TimeStamp >= inputTime + inputDelay)) {
      pspDebugKbDrawKey(row, col, 0);
      do {
	row++;
      } while (charTable[row][col] == '\0' &&
	       row != PSP_DEBUG_KB_COMMAND_ROW);
      if (row == PSP_DEBUG_KB_COMMAND_ROW) {
	col = (col * (PSP_DEBUG_KB_NUM_COMMANDS - 1)) / (PSP_DEBUG_KB_NUM_CHARS - 1);
      }
      pspDebugKbDrawKey(row, col, 1);
      inputTime = input.TimeStamp;
    }

    if (input.Buttons != lastinput.Buttons && input.Buttons & PSP_CTRL_SELECT) {
      pspDebugKbShift(&shifted);
      pspDebugKbDrawKey(row, col, 1);
    }

    if (input.Buttons != lastinput.Buttons
	&& (input.Buttons & PSP_CTRL_CROSS || input.Buttons & PSP_CTRL_CIRCLE)) {
      if (row == PSP_DEBUG_KB_COMMAND_ROW) {
	switch(col) {
	case 0: // Shift
	  pspDebugKbShift(&shifted);
	  pspDebugKbDrawKey(row, col, 1);
	  break;
	case 1: // Space
	  if (strlen(str) < PSP_DEBUG_KB_MAXLEN) {
	    snprintf(str, strlen(str)+2, "%s ", str);
	    pspDebugKbDrawString(str);
	  }
	  break;
	case 2: // Back
	  if (strlen(str) > 0) {
	    str[strlen(str)-1] = '\0';
	    pspDebugKbDrawString(str);
	  }
	  break;
	case 3: // Clear
	  bzero(str, PSP_DEBUG_KB_MAXLEN);
	  pspDebugKbDrawString(str);
	  break;
	case 4:
	  // Clean up the screen
	  pspDebugKbClearBox();
	  return;
	};
      } else {
	if (strlen(str) < PSP_DEBUG_KB_MAXLEN) {
	  snprintf(str, strlen(str)+2, "%s%c", str, charTable[row][col]);
	  pspDebugKbDrawString(str);
	}
      }
    }

    if (input.Buttons != lastinput.Buttons
	&& (input.Buttons & PSP_CTRL_TRIANGLE || input.Buttons & PSP_CTRL_SQUARE)) {
      if (strlen(str) > 0) {
	str[strlen(str)-1] = '\0';
	pspDebugKbDrawString(str);
      }
    }

    lastinput = input;
  }
}
