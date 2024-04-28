#ifndef boa
#define boa

#include <iostream>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#ifdef _WIN32
    #include <Windows.h>
    void wait(unsigned s){
        Sleep(s * 1000);
    }
    bool canColorCode() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) {
            return false; // Failed to get the handle
        }
        
        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) {
            return false; // Failed to get console mode
        }
        
        // Check if ENABLE_VIRTUAL_TERMINAL_PROCESSING is supported
        return (dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
    }
    void assemble() {
        system("nasm -f win64 out.asm");
        system("C:\\msys64\\mingw64\\bin\\ld.exe -o out.exe out.obj");
        system("del out.obj && del out.asm");
    }
#elif __APPLE__
    #include <unistd.h>
    void wait(unsigned s){
        sleep(s);
    }
    bool canColorCode() {
        // Check if TERM environment variable is set to a terminal type that likely supports ANSI color codes
        const char* termType = std::getenv("TERM");
        if (termType != nullptr && (strstr(termType, "xterm") != nullptr || strstr(termType, "rxvt") != nullptr)) {
            return true;
        }

        // Check if stdout is connected to a terminal
        return isatty(fileno(stdout)) != 0;
    }
    void assemble() {
        system("nasm -f macho64 out.asm");
        system("ld -o out out.o");
        system("rm out.o && rm out.asm");
    }
#elif __linux__
    #include <unistd.h>
    void wait(unsigned s){
        sleep(s);
    }
    bool canColorCode() {
        // Check if TERM environment variable is set to a terminal type that likely supports ANSI color codes
        const char* termType = std::getenv("TERM");
        if (termType != nullptr && (strstr(termType, "xterm") != nullptr || strstr(termType, "rxvt") != nullptr)) {
            return true;
        }

        // Check if stdout is connected to a terminal
        return isatty(fileno(stdout)) != 0;
    }
    void assemble() {
        system("nasm -f elf64 out.asm");
        system("ld -o out out.o");
        system("rm out.o && rm out.asm");
    }
#else
    int main() {
        std::cout << "This code cannot be run on your operating system.";
        return 1;
    }
#endif


typedef std::string string;

namespace bsc {
    double getRand(int min, int max) {
        srand(time(NULL));
        do {return (rand() % max) + 1;} while ((rand() % max) < min);
    }

    struct Vector3 {
        int x;
        int y;
        int z;
    };
    struct Vector2 {
        int x;
        int y;
    };
    int throwErr(std::string message, bool forArgs = false) {
        if (canColorCode()) {
            std::cerr << "\033[1;31mBoa Exception:\033[0m\n";
        } else {
            std::cerr << "Boa Exception:\n";
        }
        std::cerr << message << '\n';
        if (forArgs){
            std::cout << "\nCorrect Usage:\nboa <input.boa>\n";
        }
    }
} // bsc


#endif