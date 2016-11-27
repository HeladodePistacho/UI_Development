#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UI_Image.h"
#include "UI_String.h"
#include "UI_Button.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	Other_images.add(App->tex->Load("gui/login_background.png"));

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	for (int i = 0; i < UI_elements_List.count(); i++)
		UI_elements_List[i]->Update_Draw();

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (int i = 0; i < UI_elements_List.count(); i++)
		UI_elements_List.del(UI_elements_List.At(i));
	
	UI_elements_List.clear();

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

const SDL_Texture* j1Gui::Get_Other_Textures(uint id) const
{
	if(id < Other_images.count())
		return Other_images[id];

	return nullptr;	
}

// class Gui ---------------------------------------------------

UI_element* j1Gui::CreateElement(iPoint pos, UI_TYPE type, SDL_Rect img_size, int id)
{
	UI_element* ret = nullptr;

	switch (type)
	{
	case UI_TYPE::IMAGE: ret = new UI_Image(pos, type, img_size, id); break;
	case UI_TYPE::IMAGE_NOT_IN_ATLAS: ret = new UI_Image(pos, type, img_size, id); break;
	}

	if (ret != nullptr)
		UI_elements_List.add(ret);

	return ret;
}

UI_element* j1Gui::CreateElement(iPoint pos, UI_TYPE type, const char* text)
{
	UI_element* ret = nullptr;

	switch (type)
	{
	case UI_TYPE::STRING: ret = new UI_String(pos, type, text); break;
	}

	if (ret != nullptr)
		UI_elements_List.add(ret);

	return ret;
}

UI_element* j1Gui::CreateElement(UI_element* new_element)
{
	UI_element* ret = new_element;

	if (ret == nullptr)
		return ret;

	switch (new_element->element_type)
	{
	case UI_TYPE::IMAGE:					ret = new UI_Image((UI_Image*)new_element); break;
	case UI_TYPE::IMAGE_NOT_IN_ATLAS:		ret = new UI_Image((UI_Image*)new_element); break;
	case UI_TYPE::STRING:					ret = new UI_String((UI_String*)new_element); break;
	case UI_TYPE::BUTTON:					ret = new UI_Button((UI_Button*)new_element); break;
	}

	if (ret != nullptr)
		UI_elements_List.add(ret);

	return ret;

}