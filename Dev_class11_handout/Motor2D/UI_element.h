#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include "p2Point.h"
#include "p2List.h"

enum UI_TYPE
{
	IMAGE,
	IMAGE_NOT_IN_ATLAS,
	STRING,
	BUTTON,
	INTERACTIVE_STRING
};

class UI_element
{
public:

	UI_TYPE element_type;
	iPoint position;
	p2List<UI_element*> Childs;
	UI_element* Parent;

public:

	UI_element(iPoint position, UI_TYPE type);
	UI_element(const UI_element* other_element);
	
	virtual bool Update() { return true; };
	virtual bool Update_Draw();
	virtual bool Handle_input() { return true; };

	UI_element* AddChild(const UI_element* new_child);
	UI_element* Set_Parent(const UI_element& parent);

	void Set_Position(const iPoint& new_pos);
};



#endif // !_UI_ELEMENT_H_
