#include "../yk_utf_lib/include/unicodeStr.hpp"
#include <fstream>

struct Func{
    void operator()(std::string tout){
        std::cout << "string is" << std::endl;
        std::cout << tout;
        std::cout << std::endl;
    }
};


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
        us.eachLineWithMatch(11, 8, U"n.*関.*か", Yk::UTF::TTYAttr::bgCyan | Yk::UTF::TTYAttr::fgBlack, /*[](std::string tout){
            std::cout << "string is" << std::endl;
            std::cout << tout;
            std::cout << std::endl;
        }*/Func());
    }
}

