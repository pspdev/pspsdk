/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "menu.h"

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspgu.h>
#include <pspgum.h>

MenuContext* initMenu()
{
	MenuContext* context = (MenuContext*)malloc(sizeof(MenuContext));
	memset(context,0,sizeof(MenuContext));

	return context;
}

void destroyMenu(MenuContext* context)
{
	// delete items

	MenuItem* curr = context->root;
	while (curr)
	{
		if (curr->children)
			curr = curr->children;
		else
		{
			MenuItem* last = curr;
			curr = curr->next;

			if (!curr && last->parent)
			{
				MenuItem* lastParent = last->parent;
				curr = lastParent->next;

				free(lastParent);
			}

			free(last);
		}
	}

	free(context);
}

MenuItem* addMenuItem(MenuContext* context, MenuItem* parent, MenuItem* item, int id, int data)
{
	// setup item

	item->id = id;
	item->data = data;

	item->parent = parent;

	// attach to active parent

	if (parent)
	{
		MenuItem* sibling = parent->children;
		MenuItem* last = sibling;
		while (sibling)
		{
			last = sibling;
			sibling = sibling->next;
		}

		if (last)
			last->next = item;
		else
			parent->children = item;
	}
	else
	{
		MenuItem* sibling = context->root;
		MenuItem* last = sibling;
		while (sibling)
		{
			last = sibling;
			sibling = sibling->next;
		}

		if (last)
			last->next = item;
		else
		{
			context->root = item;
			context->active = item;
		}
	}

	switch (item->type)
	{
		case RadioButton:
		{
			if (item->state && item->parent)
				item->parent->selected = item;
			item->state = 0;
		}
		break;

		default:
		break;
	}

	return item;
}

MenuItem* createMenuContainer(const char* name)
{
	MenuItem* item = (MenuItem*)malloc(sizeof(MenuItem));
	memset(item,0,sizeof(MenuItem));

	item->name = name;
	item->type = MenuContainer;

	return item;
}

MenuItem* createRadioButton(const char* name, int state)
{
	MenuItem* item = (MenuItem*)malloc(sizeof(MenuItem));
	memset(item,0,sizeof(MenuItem));

	item->name = name;
	item->type = RadioButton;

	item->state = state;

	return item;
}

MenuItem* createTriggerButton(const char* name)
{
	MenuItem* item = (MenuItem*)malloc(sizeof(MenuItem));
	memset(item,0,sizeof(MenuItem));

	item->name = name;
	item->type = TriggerButton;

	return item;
}

MenuItem* handleMenu(MenuContext* context, SceCtrlData* input)
{
	int wasOpen = context->open;
	MenuItem* result = 0;

	if (context->lastState.Buttons != input->Buttons)
	{
		if (context->open && context->root)
		{
			MenuItem* active = context->active;

			if ((context->lastState.Buttons & PSP_CTRL_UP) && !(input->Buttons & PSP_CTRL_UP))
			{
				MenuItem* sibling = active->parent ? active->parent->children : context->root;
				MenuItem* last = sibling;
				while (sibling && (sibling != active))
				{
					last = sibling;
					sibling = sibling->next;
				}

				context->active = last;				
			}

			if ((context->lastState.Buttons & PSP_CTRL_DOWN) && !(input->Buttons & PSP_CTRL_DOWN))
			{
				if (active->next)
					context->active = active->next;
			}

			if ((context->lastState.Buttons & PSP_CTRL_CROSS) && !(input->Buttons & PSP_CTRL_CROSS))
			{
				switch (active->type)
				{
					case MenuContainer:
					{
						if (active->children)
						{
							active->state = 1;
							context->active = active->children;
						}
					}
					break;

					case RadioButton:
					{
						if (active->parent)
						{
							active->parent->selected = active;
							result = active;
						}
					}
					break;

					case ToggleButton:
					case TriggerButton:
					{
						result = active;
					}
					break;
				}
			}

			if ((context->lastState.Buttons & PSP_CTRL_CIRCLE) && !(input->Buttons & PSP_CTRL_CIRCLE))
			{
				if (active->parent)
				{
					context->active = active->parent;
					context->active->state = 0;
				}
				else
					context->open = 0;
			}
		}
		else
		{
			if ((context->lastState.Buttons & PSP_CTRL_CIRCLE) && !(input->Buttons & PSP_CTRL_CIRCLE))
				context->open = 1;
		}
	}

	// eat all input if menu is open

	context->lastState = *input;
	if (context->open || wasOpen)
		memset(input,0,sizeof(SceCtrlData));

	return result;
}

void renderMenu(MenuContext* context,int startx, int starty)
{
	if (context->open && context->root)
	{
		int depth = 0;
		int row = starty;

		MenuItem* curr = context->root;
		while (curr)
		{
			pspDebugScreenSetXY(startx + depth * 4, row);
			pspDebugScreenSetTextColor(curr == context->active ? 0x00ffff : 0xffffff);

			switch (curr->type)
			{
				case RadioButton:
				{
					int selected = curr->parent && (curr->parent->selected == curr);
					pspDebugScreenPrintf("[%s] %s",selected ? "*" : " ", curr->name);
				}
				break;

				case MenuContainer:
				{
					pspDebugScreenPrintf("%s%s",curr->state ? "-" : "+", curr->name);
					if (curr->selected && !curr->state)
						pspDebugScreenPrintf(": %s",curr->selected->name);
				}
				break;

				default:
				{
					pspDebugScreenPrintf(curr->name);
				}
				break;
			}

			// traverse

			if (curr->state && curr->children && (curr->type == MenuContainer))
			{
				curr = curr->children;
				++depth;
			}
			else
			{
				MenuItem* last = curr;
				curr = curr->next;

				if (!curr && last->parent)
				{
					curr = last->parent->next;
					--depth;
				}
			}

			++row;
		}

		pspDebugScreenSetXY(0,33);
		pspDebugScreenSetTextColor(0xffffff);
		pspDebugScreenPrintf("O = %s, Arrows = Move Up/Down, X = Select", context->active->parent ? "Back" : "Close Menu");
	}
	else
	{

		pspDebugScreenSetXY(0,33);
		pspDebugScreenPrintf("O = Open Debug Menu");
	}
}
