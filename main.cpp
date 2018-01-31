#include <iomanip>
#include <iostream>
#include <functional>
#include <list>
#include <algorithm>

#include "tiny_regex.h"

struct MenuEntry {
    std::string description;
    std::function<int(void)> callback;
};

class CLIMenu {
    std::string title;
    std::vector<MenuEntry> menus;
public:
    static const int CODE_SUCCESSFUL = 0;
    static const int CODE_ERROR = 1;
    static const int CODE_EXIT = 2;

    void set_title(std::string t) {
        title = t;
    }

    void add_entry(std::string description, std::function<int(void)> callback) {
        MenuEntry entry = {
                description: description,
                callback: callback
        };

        menus.push_back(entry);
    }

    void display() const {
        while(true) {
            size_t input;

            std::cout << title << std::endl;

            for(size_t i = 0; i < menus.size(); i++) {
                std::cout << std::setw(2) << i << " : " << menus.at(i).description << std::endl;
            }
            std::cout << "99 : Quit" << std::endl;

            std::cout << "Your input : ";
            std::cin >> input;

            try {
                if(input == 99) return;

                switch(menus.at(input).callback()) {
                    case CLIMenu::CODE_SUCCESSFUL:
                        break;
                    case CLIMenu::CODE_ERROR:
                        break;
                    case CLIMenu::CODE_EXIT:
                        return;
                    default:
                        throw "";
                }
            }
            catch (const std::exception &e) {

            }

            std::cout << std::endl;
        }
    }
};

int sample_regex() {
    CLIMenu menu;
    TinyRegex regex("^a(a|b)*a$");

    menu.set_title("Sample Regex");
    menu.add_entry("Test String", [&]() {
        std::string input;
        std::cout << "Your String : ";
        std::cin >> input;

        std::cout << "Result : " << std::boolalpha << regex.test(input) << std::endl;
        return CLIMenu::CODE_SUCCESSFUL;
    });

    menu.display();

    return CLIMenu::CODE_SUCCESSFUL;
}

int arbitrary_regex() {
    CLIMenu menu;
    std::string regs = "^a(a|b)*a$";
    TinyRegex regex(regs);

    menu.set_title("Arbitrary Regex");
    menu.add_entry("Change Regex", [&]() {
        std::cout << "Your Regex : ";
        std::cin >> regs;
        regex = TinyRegex(regs);
        return CLIMenu::CODE_SUCCESSFUL;
    });
    menu.add_entry("Check Regex", [&]() {
        std::cout << "Current Regex : " << regs << std::endl;
        return CLIMenu::CODE_SUCCESSFUL;
    });
    menu.add_entry("Test String", [&]() {
        std::string input;
        std::cout << "Your String : ";
        std::cin >> input;
        std::cout << "Result : " << std::boolalpha << regex.test(input) << std::endl;

        return CLIMenu::CODE_SUCCESSFUL;
    });

    menu.display();

    return CLIMenu::CODE_SUCCESSFUL;
}

int main(int argc, const char *argv[]) {
    CLIMenu menu;

    menu.set_title("Top Menu");
    menu.add_entry("Sample Regex : ^a(a|b)*a$", []() {
        std::cout << std::endl;
        return sample_regex();
    });
    menu.add_entry("Your Arbitrary Regex", []() {
        std::cout << std::endl;
        return arbitrary_regex();
    });

    menu.display();

}