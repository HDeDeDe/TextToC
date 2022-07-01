#include <iostream>
#include <fstream>
#include <string>

int strlen(char *p)
{
    int c=0;
    while(*p!='\0')
    {
        c++;
        *p++;
    }
    return(c);
}

std::string escaped(std::ifstream& input)
{
    std::string output;
    char c;
    while (input.get(c)) {
        switch (c) {
            case '\a':  output.append("\\a");        break;
            case '\b':  output.append("\\b");        break;
            case '\f':  output.append("\\f");        break;
            case '\n':  output.append("\\n");        break;
            case '\r':  output.append("\\r");        break;
            case '\t':  output.append("\\t");        break;
            case '\v':  output.append("\\v");        break;
            case '"':   output.append("\\\"");       break;
            case '\'':  output.append("\\'");        break;
            case '\?':  output.append("\\\?");       break;
            case '%':   output.append("%%");         break;
            default:    output.push_back(c);         break;
        }
        std::cout << c;
    }
    std::cout << std::endl;
    return output;
}

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        std::string filename;
        size_t ptr = strlen(argv[1]);
        bool check = false;
        for(char c; !check; ptr--)
        {
            c = argv[1][ptr];
            std::cout << c;
            switch(c)
            {
            case '\\':
                std::cout << std::endl;
                ptr++;
                while(c!='.' && c!='\0')
                {
                    c = argv[1][ptr];
                    filename.push_back(c);
                    std::cout << c;
                    ptr++;
                }
                std::cout << std::endl;
                check = true;
                break;
            case '/':
                std::cout << std::endl;
                ptr++;
                while(c!='.' && c!='\0')
                {
                    c = argv[1][ptr];
                    filename.push_back(c);
                    ptr++;
                }
                std::cout << std::endl;
                check = true;
                break;
            default:    break;
            }
            std::cout << std::endl;
        }
        filename.pop_back();
        std::ifstream input_file;
        input_file.open(argv[1], std::ios::binary);
        std::ofstream output_file;
        filename.append(".c");
        output_file.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc);
        filename.pop_back();
        filename.pop_back();
        output_file << "const char* " << filename << " = \"";
        output_file << escaped(input_file);
        output_file << "\"";
        output_file.close();
        input_file.close();
        std::cout << "Done!" << std::endl;
        return 0;
    }
    std::cout << "Provide file path as argument" << std::endl;
    return 0;
}