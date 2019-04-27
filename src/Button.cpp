#include "Button.h"
#include "Font.h"
#include "Render.h"
#include "Window.h"

static Font buttonFont;
const SDL_Color buttonFgColor = WHITE;
const SDL_Color buttonBgColor = { 139, 121, 101, 0xFF };


Button::Button(const char *text, std::function<void ()> onClick): m_text(text),  m_onClick(onClick){
	m_x = 0;
	m_y = 0;
	m_width = 150;
	m_height = 80;
	m_down = false;
	m_hover = false;
}

void Button::render(){
    Font buttonFont;
    buttonFont.init("ClearSans-Bold.ttf", 25);
	SDL_Color fgColor = buttonFgColor;
    SDL_Color bgColor = buttonBgColor;
	if(m_hover){
        fgColor = buttonBgColor;
        bgColor = buttonFgColor;
    }
    Texture textTexture;
	textTexture.loadText(&buttonFont, m_text, fgColor);

	Texture texture;
	texture.createBlank(m_width, m_height, SDL_TEXTUREACCESS_TARGET);
	
	g_render.setTarget(texture.sdl_texture());
	g_render.setDrawColor(bgColor);
	g_render.clear();
    g_render.setDrawColor(buttonBgColor);
    g_render.drawRect(0, 0, m_width, m_height);
	g_render.drawRect(1, 1, m_width - 2 , m_height - 2);
	textTexture.render(	(texture.width() - textTexture.width()) / 2,(texture.height() - textTexture.height()) / 2);
	g_render.setTarget(nullptr);
	texture.render(m_x, m_y);
}

void Button::handleEvent(const SDL_Event &e){
	if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = isInside(x, y);

		if(e.type == SDL_MOUSEMOTION) {
			if(!m_hover && inside) {
				m_hover = true;
			}
			else if(m_hover && !inside) {
				m_hover = false;
			}
		}
		else if(e.type == SDL_MOUSEBUTTONDOWN) {
			if(inside)
				m_down = true;
		}
		else if(m_down) {
			m_down = false;
			if(inside)	m_onClick();
		}
        render();
        g_render.present();
	}
}

bool Button::isInside(int x, int y){
	return x >= m_x && x < m_x + m_width
		&& y >= m_y && y < m_y + m_height;
}
