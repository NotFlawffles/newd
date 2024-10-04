#include "ui/element.hpp"

namespace newd::ui {
    wchar_t Element::get_icon() {
	if (content.length() == 0) {
	    return 0;
	}

	return static_cast<wchar_t>(std::strtoul(content.substr(1).c_str(), nullptr, 16));
    }
}
