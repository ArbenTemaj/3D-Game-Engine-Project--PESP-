#include <PESP/Entity/TextComponent.h>
#include <PESP/Entity/Entity.h>
#include <PESP/Game/World.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>
#include <PESP/Graphics/Font2D.h>
#include <PESP/Resource/Font.h>

TextComponent::TextComponent() = default;

TextComponent::~TextComponent()
{
    m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void TextComponent::setFont(const FontPtr& font)
{
    m_font = font;
}

const FontPtr& TextComponent::getFont()
{
    return m_font;
}

void TextComponent::setText(const wchar_t* text)
{
    m_text = text;
}

const wchar_t* TextComponent::getText()
{
    return m_text.c_str();
}

Rect TextComponent::getBounds()
{
    return m_font->getFont()->getBounds(m_text.c_str());
}

void TextComponent::onCreateInternal()
{
    m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}