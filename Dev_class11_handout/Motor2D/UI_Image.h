#ifndef _UI_IMAGE_H_
#define _UI_IMAGE_H_

#include "UI_element.h"
#include "SDL\include\SDL_rect.h"

class UI_Image : public UI_element
{
public:
	SDL_Rect Image;
	int id;
	bool printable;

public:
	UI_Image(UI_TYPE type, SDL_Rect detection_box, SDL_Rect img_size, bool print, int id = -1);
	UI_Image(const UI_Image* other);
	bool Update_Draw();
};


#endif // !_UI_IMAGE_H_

