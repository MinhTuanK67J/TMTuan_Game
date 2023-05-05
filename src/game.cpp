#include "game.h"

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

SDL_Texture *LTexture::loadFromFile(std::string path)
{
	free();
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return newTexture;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	free();
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

void LTexture::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) >= 0)
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		gWindow = SDL_CreateWindow("Bright Eyes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow != NULL)
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer != NULL)
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if ((IMG_Init(imgFlags) & imgFlags))
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
						printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				}
			}
		}
	}
}

void LTexture::loadSound(std::string path)
{
	gSound = Mix_LoadWAV(path.c_str());
	Mix_PlayChannel(-1, gSound, 0);
}

std::string LTexture::randomPathPicture(int i)
{
	std::string path = ".png";
	int randPic = rand() % (maxImage);
	while (signName[randPic] > 0)
		randPic = rand() % (maxImage);
	signName[randPic]++;
	path.insert(0, name[randPic]);
	numberPic[i] = randPic;
	path = "image_game/" + path;
	return path;
}

void LTexture::clearScreen()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

void LTexture::pathPicture()
{
	for (int i = 0; i < 12; i++)
	{
		pathPic[i] = randomPathPicture(i);
	}
}

int LTexture::mouseInsize(int x, int y)
{
	for (int i = 0; i < 12; i++)
	{
		if ((x >= posx[i]) && (x <= posx[i] + pictureSize) && (y >= posy[i]) && (y <= posy[i] + pictureSize))
			return i;
	}
	return -1;
}

void LTexture::openPicture()
{
	checkOpen = false;
	int number = mouseInsize(mouseX, mouseY);
	if (number != -1)
	{
		picturePos[quantityOfPictureIsOpen] = number;
		quantityOfPictureIsOpen++;
		renderPicture();
		loadSound("sound/clickPictureSound.wav");
	}
	if (quantityOfPictureIsOpen == 2)
	{
		if (abs(numberPic[picturePos[0]] - numberPic[picturePos[1]]) == 6)
		{
			SDL_Delay(500);
			loadSound("sound/rightSound.wav");
			countPic += 2;
			checkOpen = false;
			pathPictureRender[picturePos[0]] = pathPic[picturePos[0]];
			pathPictureRender[picturePos[1]] = pathPic[picturePos[1]];
		}
		else
		{
			SDL_Delay(800);
			checkOpen = true;
			renderPicture();
		}
		quantityOfPictureIsOpen = 0;
	}
}
