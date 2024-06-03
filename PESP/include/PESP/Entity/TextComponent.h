#pragma once
#include <PESP/Entity/Component.h>
#include <PESP/Math/Rect.h>

class TextComponent : public Component
{
public:
    TextComponent();
    virtual ~TextComponent();

    void setFont(const FontPtr& text);
    const FontPtr& getFont();

    void setText(const wchar_t* text);
    const wchar_t* getText();

    Rect getBounds();
protected:
    virtual void onCreateInternal();
private:
    std::wstring m_text = L"";
    FontPtr m_font;
};