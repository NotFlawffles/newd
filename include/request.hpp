#pragma once

#include <string>

namespace newd::compiler::request {
    static constexpr char *UniformResourceLocator = (char *) "https://www.nerdfonts.com/assets/css/webfont.css";

    std::string read_content();
}