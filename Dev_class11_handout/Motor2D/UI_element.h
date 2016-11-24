#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include "p2Point.h"

enum UI_TYPE
{
	IMAGE,
	IMAGE_NOT_IN_ATLAS,
	STRING
};

class UI_element
{
public:
	UI_TYPE element_type;
	iPoint position;

public:

	UI_element(iPoint position, UI_TYPE type);
	

	virtual bool Update() { return true; };
	virtual bool Update_Draw() { return true; };
	virtual bool Handle_input() { return true; };
	void Set_Position(const iPoint& new_pos);
};



#endif // !_UI_ELEMENT_H_
