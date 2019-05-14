#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Window.h"
#include "Render.h"
#include "Font.h"

Texture::Texture(){
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
}

Texture::~Texture(){
	free();
}

bool Texture::loadText(Font *font, const char *text, SDL_Color fgColor){
	free();

	SDL_Texture *newTexture = NULL;

	SDL_Surface *textSurface = font->renderLatin(text, fgColor);
	if(textSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		newTexture = g_render.createTextureFromSurface(textSurface);
		if(newTexture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			m_width = textSurface->w;
			m_height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	m_texture = newTexture;
	return m_texture != NULL;
}

void Texture::free(){
	if(m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::setBlendMode(SDL_BlendMode blending){
	SDL_SetTextureBlendMode(m_texture, blending);
}

void Texture::setAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(m_texture, alpha);
}

void Texture::render(int x, int y, SDL_Rect *clip){
	SDL_Rect renderQuad = { x, y, m_width, m_height };

	if(clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	g_render.copy(m_texture, clip, &renderQuad);
}

void Texture::renderScaled(int x, int y, double ratio){
	SDL_Rect dstRect = {
		x, y,
		static_cast<int>(m_width * ratio), static_cast<int>(m_width * ratio)
	};

	g_render.copy(m_texture, NULL, &dstRect);
}

bool Texture::createBlank(int width, int height, SDL_TextureAccess access){
	m_texture = g_render.createTexture(SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if( m_texture == NULL ){
        printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
    }
    else{
        m_width = width;
        m_height = height;
    }

    return m_texture != NULL;
}
