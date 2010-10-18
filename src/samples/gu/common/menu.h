#ifndef common_menu_h
#define common_menu_h

#include <pspctrl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	MenuContainer,
	RadioButton,
	ToggleButton,
	TriggerButton
} MenuItemType;

typedef struct MenuItem
{
	const char* name;
	MenuItemType type;
	int id;
	int data;

	int state;

	struct MenuItem* parent;
	struct MenuItem* next;
	struct MenuItem* children;

	// for radio-button parents

	struct MenuItem* selected;
} MenuItem;

typedef struct MenuContext
{
	int open;
	SceCtrlData lastState;

	MenuItem* root;
	MenuItem* active;
} MenuContext;

// initialize menu for use
MenuContext* initMenu();
// destroy menu
void destroyMenu(MenuContext* context);
// add menu-item into tree
MenuItem* addMenuItem(MenuContext* context, MenuItem* parent, MenuItem* item, int id, int data);
// process menu input
// - kills input while menu is open, pass the input-structure you intend to use with the rest of input
// - returns triggered MenuItem
MenuItem* handleMenu(MenuContext* context, SceCtrlData* input);
void renderMenu(MenuContext* context,int startx, int starty);

MenuItem* createMenuContainer(const char* name);
MenuItem* createRadioButton(const char* name, int state);
MenuItem* createTriggerButton(const char* name);

#ifdef __cplusplus
}
#endif

#endif
