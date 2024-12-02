#include <string>

namespace SUI {
namespace Widget {
    // This class represents a widget that contains text.
    class ITextArea {
        public:
            ITextArea(const char *text)
                :m_text(text) {};
            ~ITextArea() {};
            
            // Sets the text of the label.
            virtual void ChangeText(const char *text) = 0;
            std::string GetText() { return m_text; }

        protected:
            std::string m_text;
    };
}    
}