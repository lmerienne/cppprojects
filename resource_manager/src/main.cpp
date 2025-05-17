#include "resource_manager.hpp"
#include <iostream>
int main()
{
    try
    {
        rm::FileResource file1("test1.txt");
        rm::FileResource file2 = std::move(file1); // Déplacement
        std::cout << file2.getInfo() << "\n";
        // Vérifiez que file1 est dans un état valide (fichier fermé)
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}