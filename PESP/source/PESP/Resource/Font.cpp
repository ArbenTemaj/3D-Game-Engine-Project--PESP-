#include <PESP/Resource/Font.h>
#include <PESP/Resource/ResourceManager.h>
#include <PESP/Game/Game.h>
#include <PESP/Graphics/GraphicsEngine.h>
#include <PESP/Graphics/RenderSystem.h>
#include <sstream>
#include <regex>
#include <filesystem>

Font::Font(const wchar_t* fullpath, ResourceManager* manager) : Resource(fullpath, manager)
{
    m_font = manager->getGame()->getGraphicsEngine()->getRenderSystem()->createFont(fullpath);
}

const Font2DPtr& Font::getFont()
{
    return m_font;
}

bool FontUtility::createFont(const wchar_t* fontName, f32 fontSize, const wchar_t* outputPath)
{
    std::wstringstream p;
    std::wstring s = std::regex_replace(fontName, std::wregex(L"\\s+"), L"");
    p << outputPath << s << ".font";

    if (!std::filesystem::exists(p.str()))
    {
        std::wstringstream command;
        command << "PESP\\vendor\\DirectXTK\\bin\\MakeSpriteFont ";
        command << "\"" << fontName << "\" ";
        command << p.str() << " ";
        command << "/FontSize:" << fontSize;

        if (_wsystem(command.str().c_str()) != 0)
            PESPError("Creation of the font " << fontName << " failed");
        return true;
    }
    return true;
}