#ifndef game_h
#define game_h

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

class LTexture
{
	public:
		LTexture();
		~LTexture();
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 554;
        bool played = false;
		std::string pathPictureRender[12];
        bool quit;
        SDL_Event event;
        SDL_Renderer* gRenderer ;
        Mix_Music *gMusic ;
        int start, duration;
        int mouseX, mouseY;
        void pathPicture();
        void close();
        void loadMedia(std::string path,int x, int y, int w, int h);
		void init();
        void clearScreen();
        void renderPicture();
        void loadSound(std::string path);
        void openPicture();
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
        const int maxImage = 12;
        const std::string name[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
        const int posx[12] = {103, 263, 423, 583, 103, 263, 423, 583, 103, 263, 423, 583};
        const int posy[12] = {97, 97, 97, 97, 244, 244, 244, 244, 390, 390, 390, 390};
        const int pictureSize= 110;
        std::string pathPic[12];
        int signName[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int picturePos[20];
        int numberPic[20];
        int quantityOfPictureIsOpen = 0;
        bool checkOpen = false;
        SDL_Window* gWindow = NULL;
        SDL_Texture* gTexture = NULL;
        SDL_Point mPosition;
        Mix_Chunk *gSound = NULL;
        TTF_Font *gFont = NULL;
        int countPic = 0;
        void loadText(std::string time);
        std::string randomPathPicture(int i);
        int mouseInsize(int x, int y);
		SDL_Texture* loadFromFile( std::string path );
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		void free();
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		int getWidth();
		int getHeight();
};

#endif // game_h
