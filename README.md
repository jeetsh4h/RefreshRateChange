# RefreshRateChange

This program changes the refresh rate of your monitor via a CLI.

## Usage

Download the built executable from the _Releases_ tab on the right. You can build it yourself using Visual Studio, the `sln` and `vcxproj` files are included.  
Run the executable with the refresh rate you want to change to as an argument.

Moreover, will update the README file to include the steps that let you automatically run this executable if your laptop is plugged or unplugged from the power source.

The program has only been tested for a single-monitor use-case.

### Example

```pwsh
.\RefreshRateChange.exe <refresh rate>
```