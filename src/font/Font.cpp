#include "Font.h"
#include "SDL_FontCache.h"
#include "FontManager.h"
#include <stdarg.h>
#include "UserLog.h"

Font::Font(Font_t fontID, SDL_Renderer *renderer, std::uint32_t size, std::uint8_t r, std::uint8_t g, std::uint8_t b,
        std::uint8_t a) :
    _font(nullptr),
    _renderer(renderer),
    _isValid(true) {

    _font = FC_CreateFont();

    if(fontID >= FONT_TOTAL) {
        _isValid = false;
        LOG_WARNING("Font ID invalid");
    } else {
        FC_LoadFont(_font, _renderer, font_manager->GetFontPath(fontID).c_str(), size, FC_MakeColor(r, g, b, a),
                    TTF_STYLE_NORMAL);
    }
}

Font::~Font() {
    FC_FreeFont(_font);
}

void Font::Render(float x, float y, std::string prefix) {

    if(_isValid) {
        FC_Draw(_font, _renderer, x, y, "%s", prefix.c_str());
    }
}

void Font::Render(float x, float y, std::string prefix, int value, std::string postfix) {

    if(_isValid) {
        FC_Draw(_font, _renderer, x, y, "%s%d%s", prefix.c_str(), value, postfix.c_str());
    }
}

void Font::Render(float x, float y, std::string prefix, float value, std::string postfix) {

    if(_isValid) {
        FC_Draw(_font, _renderer, x, y, "%s%f%s", prefix.c_str(), value, postfix.c_str());
    }
}