#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

void printUsage() {
	std::cout << "Usage: RefreshRateChange <refresh_rate>\n";
	std::cout << "Example: RefreshRateChange 60\n";
}

int main(int argc, char* argv[]) {
	// Check for command line arguments
	if (argc != 2) {
		std::cout << "Error: Invalid number of arguments.\n";
		printUsage();
		return 1;
	}

	// Parse the target refresh rate
	int targetRefreshRate;
	try {
		targetRefreshRate = std::stoi(argv[1]);
		if (targetRefreshRate <= 0) {
			throw std::invalid_argument("Refresh rate must be positive");
		}
	}
	catch (const std::exception&) {
		std::cout << "Error: Invalid refresh rate specified.\n";
		printUsage();
		return 1;
	}

	// Get the current display settings
	DEVMODE dmCurrent = { 0 };
	dmCurrent.dmSize = sizeof(DEVMODE);
	if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmCurrent)) {
		std::cerr << "Failed to get current display settings." << std::endl;
		return 1;
	}

	// Current display information
	std::cout << "Current display mode:\n";
	std::cout << "Resolution: " << dmCurrent.dmPelsWidth << " x " << dmCurrent.dmPelsHeight << "\n";
	std::cout << "Color Depth: " << dmCurrent.dmBitsPerPel << " bits\n";
	std::cout << "Refresh Rate: " << dmCurrent.dmDisplayFrequency << " Hz\n\n";

	// Look for a matching mode with the desired refresh rate
	DEVMODE dmTarget = { 0 };
	dmTarget.dmSize = sizeof(DEVMODE);
	bool modeFound = false;
	int iModeNum = 0;

	// Loop through all available display modes
	while (EnumDisplaySettings(NULL, iModeNum, &dmTarget)) {
		// Check if this mode matches the current resolution and color depth but with desired refresh rate
		if (dmTarget.dmPelsWidth == dmCurrent.dmPelsWidth &&
			dmTarget.dmPelsHeight == dmCurrent.dmPelsHeight &&
			dmTarget.dmBitsPerPel == dmCurrent.dmBitsPerPel &&
			dmTarget.dmDisplayFrequency == targetRefreshRate) {
			modeFound = true;
			break;
		}
		iModeNum++;
	}

	if (!modeFound) {
		std::cout << "Error: No display mode found with refresh rate " << targetRefreshRate << " Hz "
			<< "at current resolution " << dmCurrent.dmPelsWidth << "x" << dmCurrent.dmPelsHeight
			<< " and color depth " << dmCurrent.dmBitsPerPel << " bits.\n";

		// List available refresh rates at the current resolution and color depth
		std::cout << "\nAvailable refresh rates for current resolution:\n";
		iModeNum = 0;
		dmTarget = { 0 };
		dmTarget.dmSize = sizeof(DEVMODE);

		while (EnumDisplaySettings(NULL, iModeNum, &dmTarget)) {
			if (dmTarget.dmPelsWidth == dmCurrent.dmPelsWidth &&
				dmTarget.dmPelsHeight == dmCurrent.dmPelsHeight &&
				dmTarget.dmBitsPerPel == dmCurrent.dmBitsPerPel) {
				std::cout << "  " << dmTarget.dmDisplayFrequency << " Hz\n";
			}
			iModeNum++;
		}
		return 1;
	}

	// Prepare the fields for changing the display settings
	DEVMODE dmChange = { 0 };
	dmChange.dmSize = sizeof(DEVMODE);
	dmChange.dmPelsWidth = dmCurrent.dmPelsWidth;
	dmChange.dmPelsHeight = dmCurrent.dmPelsHeight;
	dmChange.dmBitsPerPel = dmCurrent.dmBitsPerPel;
	dmChange.dmDisplayFrequency = targetRefreshRate;
	dmChange.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;

	std::cout << "Attempting to change refresh rate to " << targetRefreshRate << " Hz...\n";

	// Test the settings first
	LONG result = ChangeDisplaySettings(&dmChange, CDS_TEST);
	if (result != DISP_CHANGE_SUCCESSFUL) {
		std::cout << "Error: The display settings cannot be applied.\n";
		switch (result) {
		case DISP_CHANGE_BADMODE:
			std::cout << "The specified graphics mode is not supported.\n";
			break;
		case DISP_CHANGE_BADPARAM:
			std::cout << "An invalid parameter was passed.\n";
			break;
		case DISP_CHANGE_FAILED:
			std::cout << "The display driver failed the specified graphics mode.\n";
			break;
		case DISP_CHANGE_RESTART:
			std::cout << "The computer must be restarted for the graphics mode to work.\n";
			break;
		default:
			std::cout << "Unknown error occurred.\n";
			break;
		}
		return 1;
	}

	// If test passed, apply the settings permanently
	result = ChangeDisplaySettings(&dmChange, CDS_UPDATEREGISTRY);
	if (result != DISP_CHANGE_SUCCESSFUL) {
		std::cout << "Error: Failed to change display settings.\n";
		return 1;
	}

	std::cout << "Successfully changed refresh rate to " << targetRefreshRate << " Hz.\n";
	return 0;
}
