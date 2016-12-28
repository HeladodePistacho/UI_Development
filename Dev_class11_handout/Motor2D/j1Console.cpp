#include "j1Console.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "UI_Image.h"
#include "p2Log.h"
#include "j1Render.h"


j1Console::j1Console()
{
	name.create("console");
}

bool j1Console::Awake(pugi::xml_node& config)
{
	LOG("Setting Console features");
	
	console_screen.x = config.child("Position").attribute("x").as_int();
	console_screen.y = config.child("Position").attribute("y").as_int();
	console_screen.w = config.child("Size").attribute("width").as_int();
	console_screen.h = config.child("Size").attribute("height").as_int();

	Background.r = config.child("Color").attribute("r").as_int();
	Background.g = config.child("Color").attribute("g").as_int();
	Background.b = config.child("Color").attribute("b").as_int();
	Background.a = config.child("Color").attribute("a").as_int();

	LOG("Setting console text box");

	int width;
	App->font->CalcSize("Set", width, height, Console_font);

	Input_text = new UI_Text_Box(UI_TYPE::TEXT_BOX, { console_screen.x, (console_screen.y + console_screen.h), console_screen.w, height }, "", nullptr);
	

	LOG("Desactivating console");
	active = false;

	return true;
}

bool j1Console::Start()
{
	int num_labels = Labels.Count();

	for (int i = 0; i < num_labels; i++)
		Labels[i]->Start();
	
	Big_texture = Create_image();

	return true;
}

bool j1Console::Update(float dt)
{
	Input_text->Update();
	Input_text->Handle_input();

	check_state();

	if (state == MOUSE_OVER)
		drag_console();

	return true;
}

bool j1Console::PostUpdate()
{
	App->render->DrawQuad(console_screen, Background.r, Background.g, Background.b, Background.a);
	App->render->DrawQuad(Input_text->Interactive_box, 0, 0, 255, Background.a);

	//Change viewport
	SDL_RenderSetViewport(App->render->renderer, &console_screen);

	Big_texture->Update_Draw();
	
	SDL_RenderSetViewport(App->render->renderer, nullptr);

	


	Input_text->Update_Draw();
	return true;
}

bool j1Console::CleanUp()
{
	delete Input_text;
	return true;
}

void j1Console::Active_console()
{
	if (App->console->active)
	{
		App->console->active = false;
		SDL_StopTextInput();
	}
	else
	{
		App->console->active = true;
		App->gui->element_selected = Input_text;
		SDL_StartTextInput();
	}
}

void j1Console::Add_Label(const char * new_text)
{
	UI_String* new_label = new UI_String(UI_TYPE::STRING, { 0,0,0,0 }, (char*)new_text);
	
	if (new_label)
		Labels.PushBack(new_label);
}

UI_Image* j1Console::Create_image()
{
	
	int num_of_labels = Labels.Count();

	if (num_of_labels)
	{
		Labels_pre_update_phase = SDL_CreateTexture(App->render->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, console_screen.w, height * num_of_labels);
		SDL_SetRenderTarget(App->render->renderer, Labels_pre_update_phase);


		SDL_Rect temp = { 0,0,0, height };
		for (int i = 0; i < num_of_labels; i++)
		{
			int width;
			App->font->CalcSize(Labels[i]->text.GetString(), width, height);
			temp.w = width;
			int lol = SDL_RenderCopy(App->render->renderer, Labels[i]->text_texture, nullptr, &temp);
			temp.y += height;
		}
		SDL_SetRenderTarget(App->render->renderer, nullptr);
		
		for (int i = 0; i < num_of_labels; i++)
		{
			UI_String* vaya;
			Labels.Pop(vaya);
		}

		UI_Image* ret = new UI_Image(UI_TYPE::IMAGE_NOT_IN_ATLAS, { 0,0,0,0 }, { 0,0,console_screen.w, temp.y }, true, NO_SCROLL, App->gui->AddTexture(Labels_pre_update_phase));
		return ret;
	}
	return nullptr;
}

void j1Console::check_state()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if (((x > console_screen.x) && (x <= (console_screen.x + console_screen.w)) && (y > console_screen.y) && (y <= (console_screen.y + console_screen.h))))
		state = MOUSE_OVER;
	else state = MOUSE_NOT_OVER;
	
}

void j1Console::drag_console()
{
	int y;
	App->input->GetMouseWheel(y);

	Big_texture->Interactive_box.y += y;

}

