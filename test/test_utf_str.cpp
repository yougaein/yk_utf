#include "../yk_utf_lib/include/unicodeStr.hpp"
#include <fstream>

int main(int argc, char** argv){

    std::ifstream fi;
    fi.open("test.txt", std::ios::in);
    if(!fi)
        exit(1);
    std::string buff;
    while (!fi.eof()){
    // read by line

        std::getline(fi, buff);
        std::cout << buff << std::endl;
        Yk::UTF::UnicodeStr us(buff);
        std::cout << std::endl;
        us.eachLineWithMatch(25, 8, U"test", Yk::UTF::TTYAttr::bgCyan | Yk::UTF::TTYAttr::fgBlack, [](std::string tout){
            std::cout << tout;
            std::cout << std::endl;
        });
    }
}

