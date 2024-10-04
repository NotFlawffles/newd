#pragma once

#include <ncurses.h>
#include <sys/ioctl.h>
#include <vector>
#include <termios.h>

#include "element.hpp"

namespace newd::ui {
    class Viewport {
        public:
	  bool should_close;
	  struct winsize dimensions;
	  int rows, columns;
	  termios terminal;
	  std::vector<Element> elements;
	  std::string search_input;

	  int input_cursor_position = 0;

	  int cursor_row;
	  int cursor_column;

	  int search_bar_row;
	  int search_bar_column;
	  int search_bar_width;
	  int search_bar_height;

	public:
	  Viewport(const std::vector<Element>& elements): elements(elements) {}

        public:
          void start();
        
        private:
	  wchar_t get_icon_by_name(const std::string& name);
	  void clear();
	  void move(const int row, const int column);
	  void draw_container(const int y1, const int x1, const int y2, const int x2);
          void setup();
          void update();
          void close();
    };
}
