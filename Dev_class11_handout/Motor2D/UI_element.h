#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include "p2Point.h"
#include "p2List.h"
#include "j1Input.h"
#include "SDL\include\SDL_rect.h"

enum UI_TYPE
{
	SCREEN,
	IMAGE,
	IMAGE_NOT_IN_ATLAS,
	STRING,
	BUTTON,
	INTERACTIVE_STRING
};

enum INTERACTIVE_STATE
{
	NOTHING,
	OVER_ELEMENT,
	CLICK_ELEMENT
};


class UI_element
{
public:

	UI_TYPE element_type;
	SDL_Rect Interactive_box;

	INTERACTIVE_STATE state = INTERACTIVE_STATE::NOTHING;
	p2List<UI_element*> Childs;
	UI_element* Parent;

public:

	UI_element(UI_TYPE type, SDL_Rect detection_box);
	UI_element(const UI_element* other_element);
	
	virtual bool Update() { return true; };
	virtual bool Update_Draw();
	virtual bool Handle_input() { return true; };

	UI_element* AddChild(const UI_element* new_child);
	UI_element* Set_Parent(const UI_element& parent);

	bool Mouse_is_in(const iPoint& mouse_pos);

};



#endif // !_UI_ELEMENT_H_
