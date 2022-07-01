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
        //Pointer for the filename. Starts at the end of the provided string
        size_t ptr = strlen(argv[1]);
        //Loop check
        bool check = false;

        //Find the name of the file by reading backwards
        for(char c; !check; ptr--)
        {
            //get current character
            c = argv[1][ptr];
            std::cout << c;
            //read the character
            switch(c)
            {
            case '/': //Both cases could apply, so they run the same code
            case '\\':
                std::cout << std::endl;
                ptr++;
                //Read the characters forward until either the string ends or a . is reached
                //NOTE: I haven't actually tested the string end scenario
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
            default:    break;
            }
            std::cout << std::endl;
        }
        //This should be done in the switch case but it crashes if I do that
        filename.pop_back();

        //---------------------------------------------------------------------------
        //Main code
        //---------------------------------------------------------------------------

        //Open the input file
        std::ifstream input_file;
        input_file.open(argv[1], std::ios::binary);

        //Open the output file
        std::ofstream output_file;
        //the output file will end in .c but the filename is still needed
        filename.append(".c");
        output_file.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc);
        filename.pop_back();
        filename.pop_back();

        //Read the contents of the input file and spit them into a const char array
        output_file << "const char* " << filename << " = \"";
        output_file << escaped(input_file);
        output_file << "\"";
        
        //Close and exit
        output_file.close();
        input_file.close();
        std::cout << "Done!" << std::endl;
        return 0;
    }
    //If a second argument is not provided
    std::cout << "Provide file path as argument" << std::endl;
    return 0;
}