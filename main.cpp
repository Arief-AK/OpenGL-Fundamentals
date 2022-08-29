// ********************* INCLUDES *********************
#include "Chapters/Exercises.h"

// ********************* MAIN PROGRAM *********************

int main()
{
    bool quit = false;
    int response = -1;

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
        std::cout << "7) Ex 1: Upside down triangle shader\n";
        std::cout << "8) Ex 2: Shader with horizontal offset\n";
        std::cout << "9) Ex 3: Fragment colour equal to vertex position\n";

        std::cout << "\nTextures chapter:\n";
        std::cout << "\n10) Texture base implementation\n";
        std::cout << "11) Multiple textures\n";
        std::cout << "12) Ex 1: Multiple textures with happy face reversed\n";
        std::cout << "13) Ex 2: Multiple textures with multiple happy faces\n";
        std::cout << "14) Ex 3: Multiple textures with variable display\n";

        std::cout << "\nTransformations chapter:\n";
        std::cout << "\n15) Transformations base implementation\n";
        std::cout << "16) Ex 1: Reversed transformation procedure\n";

        std::cout << "\n17) Quit\n";
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
            float offset;
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
            TextureUnits();
            break;
        case 12:
            TextureExercise1();
            break;
        case 13:
            TextureExercise2();
            break;
        case 14:
            float disp_val;
            std::cout << "\nEnter texture display value:";
            std::cin >> disp_val;

            // Perform with set texture display value
            TextureExercise4(disp_val);
            break;
        case 15:
            TransformationBase();
            break;
        case 16:
            TransformationsExercise1();
            break;
        case 17:
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