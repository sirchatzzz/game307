#include "UIElement.h"



UIElement::UIElement(std::string name_, const char* file, Vec3 position_, float scale_, float orientation_, int row_, int col_)
{ 
	name = name_;
	image = IMG_Load(file);
	position = position_;
	scale = scale_;
	orientation = orientation_;

	if (row_ > 0 && col_ > 0)
	{
		isSpriteSheet = true;
		row = row_;
		col = col_;
	}

}

UIElement::~UIElement()
{
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texture);

	delete scene;

	flagOnCreate = false;
}

bool UIElement::LoadImage()
{
	if (image == nullptr) {
		std::cerr << "Can't open the image of " << name << std::endl;
		return false;
	}
	
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture)
	{
		std::cerr << "Can't create texture of " << name << std::endl;
		return false;
	}

	if (isSpriteSheet)
	{
		sprite.w = image->w / col;
		sprite.h = image->h / row;
	}
	

	return true;
}

bool UIElement::OnCreate(Scene* scene_)
{
	scene = scene_;
	flagOnCreate = LoadImage();
	return flagOnCreate;
}

void UIElement::SelectSprite(int x, int y)
{
	sprite.x = x * sprite.w;
	sprite.y = y * sprite.h;
}

void UIElement::Render()
{
	if (!flagOnCreate)
	{
		std::cerr << "OnCreate() not called! Cannot Render " << name << " UIElement. " << std::endl;
		return;
	}

	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	

	// Convert character orientation from radians to degrees.
	orientation = orientation * 180.0f / M_PI;

	if (!isSpriteSheet)
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
		w = static_cast<int>(w * scale);
		h = static_cast<int>(h * scale);
		screenCoords = projectionMatrix * position;
		square.x = static_cast<int>(screenCoords.x - 0.5f * w);
		square.y = static_cast<int>(screenCoords.y - 0.5f * h);
		square.w = w;
		square.h = h;

		SDL_RenderCopyEx(renderer, texture, nullptr, &square,
			orientation, nullptr, SDL_FLIP_NONE);
	}
	else
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &sprite.w, &sprite.h);
		sprite.w = static_cast<int>(sprite.w * scale);
		sprite.h = static_cast<int>(sprite.h * scale);
		screenCoords = projectionMatrix * position;
		sprite.x = static_cast<int>(screenCoords.x - 0.5f * sprite.w);
		sprite.y = static_cast<int>(screenCoords.y - 0.5f * sprite.h);

		SDL_RenderCopyEx(renderer, texture, nullptr, &sprite,
			orientation, nullptr, SDL_FLIP_NONE);
	}
	

}
