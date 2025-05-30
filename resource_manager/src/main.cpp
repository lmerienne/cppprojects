#include "resource_manager.hpp"
#include <iostream>

int main()
{
    try
    {
        rm::ResourceManager manager;
        manager.add(rm::FileResource("test1.txt"));
        manager.add(rm::FileResource("test2.txt"));
        manager.remove(0);
        manager.printResources();
        try
        {
            manager.remove(10); // Doit lever une exception
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Expected error: " << e.what() << "\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}