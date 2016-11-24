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

// class Gui ---------------------------------------------------

UI_element* j1Gui::CreateElement(iPoint pos, UI_TYPE type, SDL_Rect img_size)
{
	UI_element* ret = nullptr;

	switch (type)
	{
	case UI_TYPE::IMAGE: ret = new UI_Image(pos, type, img_size); break;

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