#include <PESP/Graphics/Font2D.h>
#include <PESP/Graphics/RenderSystem.h>
#include <SpriteFont.h>
#include <SpriteBatch.h>

Font2D::Font2D(const wchar_t* fullpath, RenderSystem* system)
{
    m_font = std::make_unique<DirectX::DX11::SpriteFont>(system->m_d3d_device.Get(), fullpath);
    if (!m_font)
        PESPError("creation of Font2D failed");

    auto context = system->m_imm_context.Get();
    m_batch = std::make_unique<DirectX::DX11::SpriteBatch>(context);
    if (!m_batch)
       PESPError("creation of Font2D failed");
}

Rect Font2D::getBounds(const wchar_t* text)
{
    auto rc = m_font->MeasureDrawBounds(text, DirectX::XMFLOAT2(0, 0));
    return Rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}