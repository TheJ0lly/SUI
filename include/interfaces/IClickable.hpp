#pragma once

#include <thread>

#include "../core_GL/core.hpp"
#include "../core_GL/opengl_wrapper.hpp"

namespace SUI::Widget {
    typedef struct {
        f64 xpos, ypos;
        s32 action, button, mods;
    } MouseEvent;

    typedef enum {
        // No highlight.
        NONE = 0,
        // The default behaviour.
        DEFAULT,
        /*
        A custom highlight behaviour.
        If you haven't set a custom function, `DefaultHighlightingFunc` will be used.
        */
        CUSTOM
    } HighlightType;

    // A generic function that is used for all click events.
    typedef void (*ClickFunc)(void *sender, void *eventArgs);

    // A generic function that is used to create custom highlighting.
    typedef void (*HighlightFunc)(GLW::Color &bkg, GLW::Color &fg);

    // The default highlighting function.
    const HighlightFunc DefaultHighlightingFunc = [](GLW::Color &bkg, GLW::Color &fg) -> void {
        bkg.b.red -= bkg.b.red < 28 ? 128 : bkg.b.red / 2;
        bkg.b.green -= bkg.b.green < 28 ? 128 : bkg.b.green / 2;
        bkg.b.blue -= bkg.b.blue < 28 ? 128 : bkg.b.blue / 2;
    };

    // This class represents a widget that can be clicked.
    class IClickable {
        public:
            IClickable(HighlightType ht)
                : m_highlightType(ht), m_highlightFunc(nullptr), m_clickFunc(nullptr) {};
            ~IClickable() {};

            virtual void Click(void) = 0;
            void SetClickFunc(ClickFunc func) { m_clickFunc = func; }
            void SetHighlightFunc(HighlightFunc func) { m_highlightFunc = func; }
        protected:
            HighlightType m_highlightType;
            HighlightFunc m_highlightFunc;
            ClickFunc m_clickFunc;
            std::thread m_clickThread;
    };
}