// ********************* INCLUDES *********************
#include "Chapters/Exercises.h"

// ********************* MAIN PROGRAM *********************

int main()
{
    bool quit = false;
    int response = -1;
    float offset = -1.0f;

    while (!quit)
    {
        std::cout << "\n********************* MENU *********************\n";
        std::cout << "\nHello triangle chapter:\n";
        std::cout << "0) Hello triangle!\n";
        std::cout << "1) Exercise 1\n";
        std::cout << "2) Exercise 2\n";
        std::cout << "3) Exercise 3\n";

        std::cout << "\nShader chapter:\n";
        std::cout << "\n4) Shader with uniform variables\n";
        std::cout << "5) Coloured vertices\n";
        std::cout << "6) Shader class implementation\n";
        std::cout << "7) Upside down triangle shader\n";
        std::cout << "8) Shader with horizontal offset\n";
        std::cout << "9) Fragment colour equal to vertex position\n";

        std::cout << "\nTextures chapter:\n";
        std::cout << "\n10) Texture base implementation\n";

        std::cout << "\n11) Quit\n";
        std::cout << "\nOption:";
        std::cin >> response;

        switch (response)
        {
        case 0: 
            Base();
            break;
        case 1:
            Exercise1();
            break;
        case 2:
            Exercise2();
            break;
        case 3:
            Exercise3();
            break;
        case 4:
            BaseUniformShader();
            break;
        case 5:
            ColouredVertex();
            break;
        case 6:
            ShaderClassImplementation();
            break;
        case 7:
            ShaderExercise1();
            break;
        case 8:
            std::cout << "\nEnter a horizontal offset:";
            std::cin >> offset;

            // Perform with set offset
            ShaderExercise2(offset);
            break;
        case 9:
            ShaderExercise3();
            break;
        case 10:
            TexturesBase();
            break;
        case 11:
            quit = true;
            break;
        default:
            Base();
            break;
        }
    }

    std::cout << "\nGood-bye!";
    return 0;
}