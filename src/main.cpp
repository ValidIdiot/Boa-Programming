/*

    Copyright 2024 ValidIdiot (More commonly known as Jerraf2p0)

        Permission is hereby granted, free of charge, to any person 
    obtaining a copy of this software and associated documentation 
    files (the “Software”), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge, 
    publish, distribute, sublicense, and/or sell copies of the Software, 
    and to permit persons to whom the Software is furnished to do so, subject 
    to the following conditions:

        The above copyright notice and this permission
    notice shall be included in all copies
    or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT
    LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.


    Boa (Boalang or BoaScript) was created because
    I believe that I could code more productively
    in my own language. Also, it's easier to code when you can literally
    just change the source code of the compiler.


*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include "boa.hpp"
#include "tokenization.hpp"
#include "parser.hpp"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        bsc::throwErr("Invalid Amount of Arguments.",true);
        exit(1);
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }
    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();
    
    Parser parser(std::move(tokens));
    std::optional<NodeExit> tree = parser.parse();

    if (!tree.has_value()) {
        bsc::throwErr("Segmentation Fault\n");
        exit(1);
    }


    Generator generator(tree.value());
    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.generate();
    }
    assemble();

    return 0;
}