#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

int main()
{
    DEVMODE dm = { 0 };
    dm.dmSize = sizeof(DEVMODE);

    std::cout << "Available display modes:\n";
    std::cout << "-----------------------------------------------------------------\n";
    std::cout << std::left << std::setw(25) << "Resolution" 
              << std::setw(20) << "Color Depth" 
              << std::setw(20) << "Refresh Rate" << "\n";
    std::cout << "-----------------------------------------------------------------\n";

    // iModeNum is 0-based index for display mode
    int iModeNum = 0;
    int displayedModes = 0;

    // Loop through all available display modes
    while (EnumDisplaySettings(NULL, iModeNum, &dm))
    {
        // Format and print information about the display mode
        std::cout << std::left << std::setw(25) 
                  << (std::to_string(dm.dmPelsWidth) + " x " + std::to_string(dm.dmPelsHeight))
                  << std::setw(20) << (std::to_string(dm.dmBitsPerPel) + " bits")
                  << std::setw(20) << (std::to_string(dm.dmDisplayFrequency) + " Hz") << "\n";
        
        displayedModes++;
        iModeNum++;
    }

    std::cout << "-----------------------------------------------------------------\n";
    std::cout << "Total display modes: " << displayedModes << std::endl;

    return 0;
}