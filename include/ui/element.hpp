#pragma once

#include <string>

namespace newd::ui {
    class Element {
        public:
          const std::string name;
          const std::string content;

        public:
          Element(const std::string& name, const std::string& icon): name(name), content(icon) {}

	public:
	  wchar_t get_icon();
    };
}
