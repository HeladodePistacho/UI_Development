#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include "p2Point.h"
#include "p2List.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_rect.h"

enum UI_TYPE
{
	SCREEN,
	IMAGE,
	IMAGE_NOT_IN_ATLAS,
	STRING,
	BUTTON,
	TEXT_BOX,
	SCROLL
};

enum INTERACTIVE_STATE
{
	NOTHING,
	OVER_ELEMENT,
	CLICK_ELEMENT
};

enum SCROLL_TYPE
{
	NO_SCROLL = 0,
	FREE_SCROLL,
	Y_SCROLL,
	X_SCROLL
};

struct j1Module;

class UI_element
{
public:

	UI_TYPE element_type;
	SDL_Rect Interactive_box;

	INTERACTIVE_STATE state = INTERACTIVE_STATE::NOTHING;

	p2List<UI_element*> Childs;
	const UI_element* Parent = nullptr;

	uint layer = 1;
	int tab_order = 0;

	bool active;
	SCROLL_TYPE draggable;

	j1Module* my_module;

public:

	UI_element(UI_TYPE type, SDL_Rect detection_box, bool active = true, SCROLL_TYPE draggable = FREE_SCROLL);
	UI_element(const UI_element* other_element);
	
	virtual bool Start() { return true; };
	virtual bool Update();
	virtual bool Update_Draw();
	virtual bool Handle_input() { return true; };

	UI_element* AddChild(UI_element* new_child);
	const UI_element* Set_Parent(const UI_element* parent);

	void Child_Update_Draw();
	void Child_Update();

	bool Mouse_is_in(const iPoint& mouse_pos);
	void Check_state();
	void Drag_element();

	void Add_to_Tab();

	UI_element* get_higher_child();
	void setmodule(j1Module* lol);
};


#endif // !_UI_ELEMENT_H_
