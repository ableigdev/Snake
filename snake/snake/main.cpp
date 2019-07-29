#include <memory>
#include "IMenu.h"
#include "ConsoleMenuImpl.h"

int main()
{
    auto menu(std::make_unique<menu_impl::console_menu_impl::ConsoleMenuImpl>());
    menu->show();

    return 0;
}