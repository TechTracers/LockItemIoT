# LockItem project

This is a project for test the LockItem solution.

## Use

### Wokwi project

The wokwi project is limited, but you can try it [here](https://wokwi.com/projects/414544996826301441)

### VS Code 

#### Required extensions
* [Wokwi Simulator](https://docs.wokwi.com/vscode/getting-started/) 
* [PlatformIO IDE](https://docs.platformio.org/en/latest/integration/ide/vscode.html#quick-start)

In order to test the project locally with vs code, follow the steps below:


Clone the repo:

```bash
git clone https://github.com/TechTracers/LockItemIoT.git
```
Open the project in VS Code and edit the credentials and other variables inside the **src/main.cpp**

Open in the terminal (with base path in {path_to}/LockItemIoT) 
and build the project with:

```bash
pio run
```
> If the `pio` command is not recognized, you may need to install [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html) 
> and add it to the PATH environment variable.

After the successful build of the project, test the wokwi simulator by pressing F1 and then start simulaton.

### Using other positions

This project obtains the position of a simulated chip using NMEA expressions.

#### Wokwi project.

You can change these positions by replacing the value of the variable **gps_tx_data** in the file **gps-neo6m.chip.c**. 

#### VS Code

Similar to wokwi project, you can change these positions by replacing the value of the
**gps_tx_data** variable in the **gps-neo6m.chip.c** file in any of the folders inside the **chips** folder. 
But additionally, you need to compile this file to binary (.wasm).

Inside the chips folder, there is a python script (windows) to compile the .c files to .wasm. This works by taking 
the .nmea files inside **chips/data**, mapping the expressions to an array and creates the .c files according to the template. 
Then it compiles them using [wasi-sdk](https://github.com/WebAssembly/wasi-sdk). And the result is found in **chips/{nmea_filename}/**. You can generate .nmea files with [nmeagen](https://nmeagen.org/)

After generating the .wasm files, you must replace the **binary** value for the gps-neo6m chip in the **wokwi.toml** file 
with the path to the desired .wasm file. 