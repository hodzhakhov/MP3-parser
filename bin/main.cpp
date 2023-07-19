#include "lib/MP3parser.h"

int main(int argc, char* argv[]) {
    //ID3 parser;

    std::string input_file = static_cast<std::string>(argv[1]);
    std::string output_file = static_cast<std::string>(argv[2]);

    /*std::ifstream input(input_file, std::ios::binary);
    std::ofstream output(output_file);

    if (!input.is_open()) {
        throw std::invalid_argument("No such file");
    }

    parser.Parse(input);
    parser.Output(output);*/

    MP3 pars;

    pars.Load(input_file);

    return 0;
}
