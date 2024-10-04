#include <unistd.h>
#include <iostream>
#include <sys/ioctl.h>

#include "ui/viewport.hpp"

namespace newd::ui {
    wchar_t Viewport::get_icon_by_name(const std::string& name) {
	for (auto element: elements) {
	    if (element.name == name) {
		return element.get_icon();
	    }
	}

	return 0;
    }

    void Viewport::clear() { wprintf(L"\033[2J\033[1;1H"); }

    void Viewport::move(const int row, const int column) {
	cursor_row = row;
	cursor_column = column;

	wprintf(L"\033[%d;%dH", row, column);
    }

    void Viewport::draw_container(const int row, const int column, const int width, const int height) {
	move(row, column);

	for (int y = 0; y < height; ++y) {
	    if (y == 0) {
		putwchar(L'┌');

		for (int x = 0; x < width; ++x) {
		    if (x == 4) {
			putwchar(L'┬');
		    }

		    putwchar(L'─');
		}

		putwchar(L'┐');
	    } else if (y + 1 == height) {
		putwchar(L'└');

		for (int x = 0; x < width; ++x) {
		    if (x == 4) {
			putwchar(L'┴');
		    }

		    putwchar(L'─');
		}

		putwchar(L'┘');
	    } else {
		putwchar(L'│');

		for (int x = 0; x < width; ++x) {
		    if (x == 4) {
			putwchar(L'│');
		    }

		    putwchar(L' ');
		}

		putwchar(L'│');
	    }

	    move(row + y + 1, column);
	}
    }

    void Viewport::setup() {
	tcgetattr(STDIN_FILENO, &terminal);
	termios raw = terminal;
	raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	clear();

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &dimensions);

	search_bar_row = dimensions.ws_row - 4;
	search_bar_column = dimensions.ws_col / 2 - 4;
	search_bar_width = dimensions.ws_col / 2;
	search_bar_height = 3;

	int column = 4;

	for (auto element: elements) {
	    auto icon = element.get_icon();

	    if (!icon) {
		continue;
	    }

	    if (column++ > dimensions.ws_row) {
		break;
	    } else {
		putwchar(10);
	    }

	    wprintf(L"    %lc\t%s", icon, element.name.c_str());
	}

	draw_container(search_bar_row, search_bar_column, search_bar_width, search_bar_height);

	move(search_bar_row + search_bar_height / 2, search_bar_column + 2);

	wprintf(L"\e[32m");

	move(4, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[31m	        _____                    _____                    _____                    _____          ");
	move(5, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[32m         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\         ");
	move(6, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[33m        /::\\____\\                /::\\    \\                /::\\____\\                /::\\    \\        ");
	move(7, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[34m       /::::|   |               /::::\\    \\              /:::/    /               /::::\\    \\       ");
	move(8, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[35m      /:::::|   |              /::::::\\    \\            /:::/   _/___            /::::::\\    \\      ");
	move(9, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[36m     /::::::|   |             /:::/\\:::\\    \\          /:::/   /\\    \\          /:::/\\:::\\    \\     ");
	move(10, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[37m    /:::/|::|   |            /:::/__\\:::\\    \\        /:::/   /::\\____\\        /:::/  \\:::\\    \\    ");
	move(11, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[31m   /:::/ |::|   |           /::::\\   \\:::\\    \\      /:::/   /:::/    /       /:::/    \\:::\\    \\   ");
	move(12, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[32m  /:::/  |::|   | _____    /::::::\\   \\:::\\    \\    /:::/   /:::/   _/___    /:::/    / \\:::\\    \\  ");
	move(13, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[33m /:::/   |::|   |/\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/___/:::/   /\\    \\  /:::/    /   \\:::\\ ___\\ ");
	move(14, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[34m/:: /    |::|   /::\\____\\/:::/__\\:::\\   \\:::\\____\\|:::|   /:::/   /::\\____\\/:::/____/     \\:::|    |");
	move(15, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[35m\\::/    /|::|  /:::/    /\\:::\\   \\:::\\   \\::/    /|:::|__/:::/   /:::/    /\\:::\\    \\     /:::|____|");
	move(16, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[36m \\/____/ |::| /:::/    /  \\:::\\   \\:::\\   \\/____/  \\:::\\/:::/   /:::/    /  \\:::\\    \\   /:::/    / ");
	move(17, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[37m         |::|/:::/    /    \\:::\\   \\:::\\    \\       \\::::::/   /:::/    /    \\:::\\    \\ /:::/    /  ");
	move(18, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[31m         |::::::/    /      \\:::\\   \\:::\\____\\       \\::::/___/:::/    /      \\:::\\    /:::/    /   ");
	move(19, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[32m         |:::::/    /        \\:::\\   \\::/    /        \\:::\\__/:::/    /        \\:::\\  /:::/    /    ");
	move(20, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[33m         |::::/    /          \\:::\\   \\/____/          \\::::::::/    /          \\:::\\/:::/    /     ");
	move(21, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[34m         /:::/    /            \\:::\\    \\               \\::::::/    /            \\::::::/    /      ");
	move(22, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[35m        /:::/    /              \\:::\\____\\               \\::::/    /              \\::::/    /       ");
	move(23, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[36m        \\::/    /                \\::/    /                \\::/____/                \\::/____/        ");
	move(24, search_bar_column + search_bar_width / 2 - 50);
	wprintf(L"\e[37m         \\/____/                  \\/____/                  ~~                       ~~              ");

	move(search_bar_row + search_bar_height / 3, search_bar_column + 7);
    }

    void Viewport::update() {
	move(search_bar_row + search_bar_height / 2, search_bar_column + 7);
	
	for (int x = 0; x < search_bar_width - 1; ++x) {
	    putwchar(0);
	}

	wprintf(L"\e[1m%s", search_input.c_str());

	move(search_bar_row + search_bar_height / 2, search_bar_column + 7 + input_cursor_position);
	fflush(stdout);
    }

    void Viewport::start() {
        setup();

        while (!should_close) {
	    update();
	    
	    char key;
	    read(STDIN_FILENO, &key, 1);

            switch (key) {
                case 0x1b:
		    clear();
                    should_close = true;
                    break;

		case 0x7f:
		    if (input_cursor_position) {
			wprintf(L"\b \b");
			search_input.erase(search_input.begin() + --input_cursor_position);
		    }

		    break;

		case 0x0a:
		    break;

		default:
		    input_cursor_position++;
		    search_input.push_back(key);
		    break;
            }
        }

	close();
    }

    void Viewport::close() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);  }
}
