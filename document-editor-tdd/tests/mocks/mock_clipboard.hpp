#ifndef MOCK_CLIPBOARD_HPP
#define MOCK_CLIPBOARD_HPP

#include "gmock/gmock.h"

#include "clipboard.hpp"

struct MockClipboard : Clipboard
{
    MOCK_METHOD(std::string, content, (), (const, override));
    MOCK_METHOD(void, set_content, (const std::string&), (override));
};

#endif //MOCK_CLIPBOARD_HPP
