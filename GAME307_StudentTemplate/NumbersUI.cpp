#include "NumbersUI.h"



NumbersUI::NumbersUI()
{
	//Init Variables
	ones = 0;
	tens = 0;
	hundreds = 0;
	thousands = 0;
	screenX = 0.0f;
	screenY = 0.0f;

	imageOne, imageTwo, imageThree, imageFour, imageFive, imageSix, imageSeven, imageEight, imageNine, imageZero = nullptr;
	textureOne, textureTwo, textureThree, textureFour, textureFive, textureSix, textureSeven, textureEight, textureNine, textureZero = nullptr;

}

void NumbersUI::OnCreate(SDL_Renderer* renderer_, bool RoundorZombieUI)
{
	
	if (RoundorZombieUI)
	{
		//Load imageOne 
		imageOne = IMG_Load("Assets/UI/HUD/level number/1.png");
		renderer = renderer_;
		textureOne = SDL_CreateTextureFromSurface(renderer, imageOne);
		if (imageOne == nullptr) {
			std::cerr << "Can't open the imageOne image" << std::endl;

		}

		//Load imageTwo
		imageTwo = IMG_Load("Assets/UI/HUD/level number/2.png");
		textureTwo = SDL_CreateTextureFromSurface(renderer, imageTwo);
		if (imageTwo == nullptr) {
			std::cerr << "Can't open the imageTwo image" << std::endl;

		}

		//Load imageThree 
		imageThree = IMG_Load("Assets/UI/HUD/level number/3.png");
		textureThree = SDL_CreateTextureFromSurface(renderer, imageThree);
		if (imageThree == nullptr) {
			std::cerr << "Can't open the imageThree image" << std::endl;

		}

		//Load imageFour
		imageFour = IMG_Load("Assets/UI/HUD/level number/4.png");
		textureFour = SDL_CreateTextureFromSurface(renderer, imageFour);
		if (imageOne == nullptr) {
			std::cerr << "Can't open the imageFour image" << std::endl;

		}

		//Load imageFive
		imageFive = IMG_Load("Assets/UI/HUD/level number/5.png");
		textureFive = SDL_CreateTextureFromSurface(renderer, imageFive);
		if (imageOne == nullptr) {
			std::cerr << "Can't open the imageFive image" << std::endl;

		}

		//Load imageSix 
		imageSix = IMG_Load("Assets/UI/HUD/level number/6.png");
		textureSix = SDL_CreateTextureFromSurface(renderer, imageSix);
		if (imageOne == nullptr) {
			std::cerr << "Can't open the imageSix image" << std::endl;

		}

		//Load imageSeven 
		imageSeven = IMG_Load("Assets/UI/HUD/level number/7.png");
		textureSeven = SDL_CreateTextureFromSurface(renderer, imageSeven);
		if (imageSeven == nullptr) {
			std::cerr << "Can't open the imageSeven image" << std::endl;

		}

		//Load imageEight 
		imageEight = IMG_Load("Assets/UI/HUD/level number/8.png");
		textureEight = SDL_CreateTextureFromSurface(renderer, imageEight);
		if (imageEight == nullptr) {
			std::cerr << "Can't open the textureEight image" << std::endl;

		}

		//Load imageNine 
		imageNine = IMG_Load("Assets/UI/HUD/level number/9.png");
		textureNine = SDL_CreateTextureFromSurface(renderer, imageNine);
		if (imageNine == nullptr) {
			std::cerr << "Can't open the imageNine image" << std::endl;

		}

		//Load imageZero 
		imageZero = IMG_Load("Assets/UI/HUD/level number/0.png");
		textureZero = SDL_CreateTextureFromSurface(renderer, imageZero);
		if (imageZero == nullptr) {
			std::cerr << "Can't open the imageZero image" << std::endl;

		}
	}
	else
	{
		//Load imageOne 
		imageOne = IMG_Load("Assets/UI/HUD/level number/health1.png");
		renderer = renderer_;
		textureOne = SDL_CreateTextureFromSurface(renderer, imageOne);
		if (imageOne == nullptr) {
			std::cerr << "Can't open the imageOne image" << std::endl;

		}

		//Load imageTwo
		imageTwo = IMG_Load("Assets/UI/HUD/level number/health2.png");
		textureTwo = SDL_CreateTextureFromSurface(renderer, imageTwo);
		if (imageTwo == nullptr) {
			std::cerr << "Can't open the imageTwo image" << std::endl;

		}

		//Load imageThree 
		imageThree = IMG_Load("Assets/UI/HUD/level number/health3.png");
		textureThree = SDL_CreateTextureFromSurface(renderer, imageThree);
		if (imageThree == nullptr) {
			std::cerr << "Can't open the imageThree image" << std::endl;

		}

		//Load imageFour
		imageFour = IMG_Load("Assets/UI/HUD/level number/health4.png");
		textureFour = SDL_CreateTextureFromSurface(renderer, imageFour);
		if (imageOne == nullptr) {
			std::cerr << "Can't open the imageFour image" << std::endl;

		}

		//Load imageFive
		imageFive = IMG_Load("Assets/UI/HUD/level number/health5.png");
		textureFive = SDL_CreateTextureFromSurface(renderer, imageFive);
		if (imageOne == nullptr) {
			std::cerr << "Can't open the imageFive image" << std::endl;

		}

		//Load imageSix 
		imageSix = IMG_Load("Assets/UI/HUD/level number/health6.png");
		textureSix = SDL_CreateTextureFromSurface(renderer, imageSix);
		if (imageOne == nullptr) {
			std::cerr << "Can't open the imageSix image" << std::endl;

		}

		//Load imageSeven 
		imageSeven = IMG_Load("Assets/UI/HUD/level number/health7.png");
		textureSeven = SDL_CreateTextureFromSurface(renderer, imageSeven);
		if (imageSeven == nullptr) {
			std::cerr << "Can't open the imageSeven image" << std::endl;

		}

		//Load imageEight 
		imageEight = IMG_Load("Assets/UI/HUD/level number/health8.png");
		textureEight = SDL_CreateTextureFromSurface(renderer, imageEight);
		if (imageEight == nullptr) {
			std::cerr << "Can't open the textureEight image" << std::endl;

		}

		//Load imageNine 
		imageNine = IMG_Load("Assets/UI/HUD/level number/health9.png");
		textureNine = SDL_CreateTextureFromSurface(renderer, imageNine);
		if (imageNine == nullptr) {
			std::cerr << "Can't open the imageNine image" << std::endl;

		}

		//Load imageZero 
		imageZero = IMG_Load("Assets/UI/HUD/level number/health0.png");
		textureZero = SDL_CreateTextureFromSurface(renderer, imageZero);
		if (imageZero == nullptr) {
			std::cerr << "Can't open the imageZero image" << std::endl;

		}
	}

	
	
}

void NumbersUI::Render(SDL_Renderer* renderer_, float scale, int number, float screenX_, float screenY_)
{
	//Assign renderer
	renderer = renderer_;
	
	if (number < 10)
	{
		selectNumber(renderer, scale, number, screenX_, screenY_);

	}
	else if (number < 100)
	{
		//Break dowwn the number
		ones = number / 10;
		tens = number % 10;

		selectNumber(renderer, scale, ones, screenX_, screenY_);
		//Screen Coords - move number to right
		screenX += 50;
		selectNumber(renderer, scale, tens, screenX, screenY_);
	}
	else if (number < 1000)
	{
		//Break dowwn the number
		ones = number / 100;
		tens = (number % 100) / 10;
		hundreds = number % 10;

		selectNumber(renderer, scale, ones, screenX_, screenY_);
		screenX += 40;
		selectNumber(renderer, scale, tens, screenX, screenY_);
		screenX += 50;
		selectNumber(renderer, scale, hundreds, screenX, screenY_);
	}
	
}

void NumbersUI::selectNumber(SDL_Renderer* renderer_, float scale, int number, float screenX_, float screenY_)
{

	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	screenX = screenX_;
	screenY = screenY_;

	switch (number)
	{
	case 0:
		//Get image width and height and adjust it to scale
		w = imageZero->w * scale;
		h = imageZero->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureZero, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;

	case 1:
		//Get image width and height and adjust it to scale
		w = imageOne->w * scale;
		h = imageOne->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureOne, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	case 2:
		//Get image width and height and adjust it to scale
		w = imageTwo->w * scale;
		h = imageTwo->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureTwo, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	case 3:
		//Get image width and height and adjust it to scale
		w = imageThree->w * scale;
		h = imageThree->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureThree, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	case 4:
		//Get image width and height and adjust it to scale
		w = imageFour->w * scale;
		h = imageFour->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureFour, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	case 5:
		//Get image width and height and adjust it to scale
		w = imageFive->w * scale;
		h = imageFive->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureFive, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	case 6:
		//Get image width and height and adjust it to scale
		w = imageSix->w * scale;
		h = imageSix->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureSix, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	case 7:
		//Get image width and height and adjust it to scale
		w = imageSeven->w * scale;
		h = imageSeven->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureSeven, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	case 8:
		//Get image width and height and adjust it to scale
		w = imageEight->w * scale;
		h = imageEight->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureEight, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	case 9:
		//Get image width and height and adjust it to scale
		w = imageNine->w * scale;
		h = imageNine->h * scale;

		//Create Square
		square.x = static_cast<int>(screenX);
		square.y = static_cast<int>(screenY);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

		/////////////////////////////////
		//Render Saling
		/////////////////////////////////
		square.w *= scale;
		square.h *= scale;

		/////////////////////////////////
		//RENDER
		//////////////////////////////////.
		SDL_RenderCopyEx(renderer, textureNine, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
		break;
	}

}
