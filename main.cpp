//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

int strlen(char *p) //I don't want to include its header
{
    int c=0;
    while(*p!='\0')
    {
        c++;
        *p++;
    }
    return(c);
}

//Read every character and replace any escapable characters
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

//---------------------------------------------------------------------------
// Main
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    //Don't run if a file path is not provided.
    //This can do weird things if you provide an invalid path, but it shouldn't harm anything
    if(argc == 2)
    {
        //---------------------------------------------------------------------------
        //Variables
        //---------------------------------------------------------------------------

        //The name of the file you put in
        std::string filename;
        //Pointer for the filename.
        size_t ptr = strlen(argv[1]);
        //Loop check
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