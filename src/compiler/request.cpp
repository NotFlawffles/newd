#include <cstdlib>
#include <cstdio>

#include "request.hpp"

namespace newd::compiler::request {
    std::string read_content() {
        auto command = "wget -qO - " + std::string(UniformResourceLocator);

        auto stream = popen(command.c_str(), "r");

        std::string content;

        char buffer[128];

        while (fgets(buffer, sizeof(buffer), stream) != nullptr) {
            content.append(buffer);
        }

        return content;
    }
}