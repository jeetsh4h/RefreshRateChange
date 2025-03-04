#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

int main()
{
    // Get the current display settings first
    DEVMODE dmCurrent = { 0 };
    dmCurrent.dmSize = sizeof(DEVMODE);
    if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmCurrent)) {
        std::cerr << "Failed to get current display settings." << std::endl;
        return 1;
    }

    std::cout << "Available display modes with same resolution and color depth as current mode:\n";
    std::cout << "-----------------------------------------------------------------\n";
    std::cout << std::left << std::setw(25) << "Resolution" 
              << std::setw(20) << "Color Depth" 
              << std::setw(20) << "Refresh Rate" << "\n";
    std::cout << "-----------------------------------------------------------------\n";

    // iModeNum is 0-based index for display mode
    int iModeNum = 0;
    int displayedModes = 0;
    DEVMODE dm = { 0 };
    dm.dmSize = sizeof(DEVMODE);

    // Loop through all available display modes
    while (EnumDisplaySettings(NULL, iModeNum, &dm))
    {
        // Check if resolution and color depth match the current settings
        if (dm.dmPelsWidth == dmCurrent.dmPelsWidth && 
            dm.dmPelsHeight == dmCurrent.dmPelsHeight &&
            dm.dmBitsPerPel == dmCurrent.dmBitsPerPel)
        {
            // Format the display information
            std::string resolution = std::to_string(dm.dmPelsWidth) + " x " + std::to_string(dm.dmPelsHeight);
            std::string colorDepth = std::to_string(dm.dmBitsPerPel) + " bits";
            std::string refreshRate = std::to_string(dm.dmDisplayFrequency) + " Hz";
            
            // Check if this is the current mode
            bool isCurrentMode = (dm.dmDisplayFrequency == dmCurrent.dmDisplayFrequency);
            
            // Highlight current mode with asterisks
            if (isCurrentMode) {
                std::cout << "* " << std::left << std::setw(23) << resolution
                          << std::setw(20) << colorDepth
                          << std::setw(20) << refreshRate << " *\n";
            } else {
                std::cout << "  " << std::left << std::setw(23) << resolution
                          << std::setw(20) << colorDepth
                          << std::setw(20) << refreshRate << "\n";
            }
            
            displayedModes++;
        }

        iModeNum++;
    }

    std::cout << "-----------------------------------------------------------------\n";
    std::cout << "Current mode is marked with *" << std::endl;

    return 0;
}