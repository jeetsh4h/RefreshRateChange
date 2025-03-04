# RefreshRateChange

RefreshRateChange is a command-line tool that changes the display refresh rate for your monitor. You can run the executable with the desired refresh rate as a command-line argument.

## Usage

1. **Command-line tool**  

    Open your terminal and run:  

    ```powershell
    "path\to\RefreshRateChange.exe" <refresh_rate>
    ```

    Replace `<refresh rate>` with the desired refresh rate (e.g., `60`).  
    Replace `path\to\RefreshRateChange.exe` to the path where you have downloaded and stored your executable.

> You can download the executable from the release tab in the github repository. [Here is the link of the current latest release.](https://github.com/jeetsh4h/RefreshRateChange/releases/tag/v0.1.0)

2. **Scheduled Task Registration**

   Two XML configuration files are provided within the repository. This is primarily for laptop users as it switches refresh rate of your current monitor based on whether you are plugged into power or not.

    Here are the two commands:

    ```powershell
    Register-ScheduledTask -TaskName "RefreshRateHigh" -TaskPath "\RefreshRateChange\" -Xml (Get-Content "path\to\RefreshRateHigh.xml" -Raw)

    Register-ScheduledTask -TaskName "RefreshRateLow" -TaskPath "\RefreshRateChange\" -Xml (Get-Content "path\to\RefreshRateLow.xml" -Raw)
    ```

    **REMEMBER** to replace the executable path *within* the XML files too. This is what it currently looks like in the file:  
    
    ```xml
    <Exec>
        <Command>path\to\RefreshRateChange.exe</Command>
        <Arguments>your_LOW_int</Arguments>
    </Exec>
    ```

    Update the refresh rate to one relevant to your setup. _In **BOTH** XML files._

## Troubleshooting

After you have registered your task, but the refresh rate is still not changing as expected then open `Task Scheduler` (use Windows search to get there).  
On the right-hand side of the menu, there is a folder called `RefreshRateChange` which stores both your tasks. You can check what error messages are coming on that screen.  
If you have realised your mistake and want to unregister the task via the terminal (powershell), then run:

```powershell
Unregister-ScheduledTask -TaskName "RefreshRateHigh" -TaskPath "\RefreshRateChange\" -Confirm:$false

Unregister-ScheduledTask -TaskName "RefreshRateLow" -TaskPath "\RefreshRateChange\" -Confirm:$false
```

You can re-run above the above registration command after fixing your mistakes.

> Black screen while changing refresh rate is expected.  
> Terminal icon flashing in the Windows start bar is expected.