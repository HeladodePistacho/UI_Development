#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "UI_element.h"

#define CURSOR_WIDTH 2

struct SDL_Texture;

// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	UI_element* CreateElement(iPoint pos, UI_TYPE type, SDL_Rect img_size, int id = -1);
	UI_element* CreateElement(iPoint pos, UI_TYPE type, const char* text);
	UI_element* CreateElement(UI_element* new_element);

	const SDL_Texture* GetAtlas() const;
	const SDL_Texture* Get_Other_Textures(uint id) const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2List<SDL_Texture*> Other_images;
	p2List<UI_element*> UI_elements_List;

};

#endif // __j1GUI_H__