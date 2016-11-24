#ifndef _UI_IMAGE_H_
#define _UI_IMAGE_H_

#include "UI_element.h"
#include "SDL\include\SDL_rect.h"

class UI_Image : public UI_element
{
public:
	SDL_Rect Image;
	int id;

public:
	UI_Image(iPoint pos, UI_TYPE type, SDL_Rect img_size, int id);
	bool Update_Draw();
};


#endif // !_UI_IMAGE_H_

