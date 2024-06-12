#include <Yk/utf/unicodeStr.hpp>
#include <iostream>
#include <fstream>

struct Func{
    void operator()(std::string tout, size_t pad_size, std::vector<size_t> cpPosList){
        std::cout << tout;
		std::cout << pad_size;
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
        Yk::UTF::UnicodeStr us(buff);
        std::cout << buff << std::endl;
//        std::cout << us.lineCount(25, 8) << std::endl;
				
//        us.eachLineWithMatch(2, 8, "n.*?関.*?が", Yk::UTF::TTYAttr::bgCyan | Yk::UTF::TTYAttr::fgBlack, /*[](std::string tout){
        us.eachLineWithMatch(25, 8, "T.*か", Yk::UTF::TTYAttr::bgCyan | Yk::UTF::TTYAttr::fgBlack, /*[](std::string tout){
//        us.eachLineWithMatch(200, 8, "n.*?関", Yk::UTF::TTYAttr::bgCyan | Yk::UTF::TTYAttr::fgBlack, /*[](std::string tout){
            std::cout << "string is" << std::endl;
            std::cout << tout;
            std::cout << std::endl;
        }*/Func());
    }
}

