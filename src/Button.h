#ifndef Button_h
#define Button_h

#include <SDL2/SDL.h>
#include <functional>
#include "Texture.h"
#include "Render.h"

class Button {
    public:
        Button(const char *text, std::function<void ()> onClick);
        void setXY(int x, int y) { m_x = x; m_y = y; }
        void render();
        void handleEvent(const SDL_Event &e);
        int width() { return m_width; }
        int height() { return m_height; }

    private:
        const char *m_text;
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        std::function<void ()> m_onClick;
        bool m_down;
        bool m_hover;
        bool isInside(int x, int y);
};

#endif
