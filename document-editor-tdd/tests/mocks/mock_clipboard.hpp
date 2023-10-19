#ifndef MOCK_CLIPBOARD_HPP

#include <trompeloeil.hpp>

#include "clipboard.hpp"

struct MockClipboard : Clipboard
{
    MAKE_CONST_MOCK0(content, std::string());
    MAKE_MOCK1(set_content, void (const std::string&));
};

#endif // MOCK_CLIPBOARD_HPP
