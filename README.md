# Enhanced Export3DToHtml Sample for HOOPS Publish

## Overview

This sample extends the standard `Export3DToHtml` example included in the HOOPS Publish SDK. The original sample functions as a basic template for a 3D Web viewer, suitable for web visualization. This enhanced version adds greater flexibility and extensibility to serve as a richer template for creating standalone, monolithic HTML viewers.<br>

### Key Enhancements

- Provides a customizable template that allows:
  - **Toggle display** of UI components such as **Model Tree**, **Toolbar**, **Axis Triad**, and **Navigation Cube**
  - **Injection of user-defined UI elements**, **JavaScript**, and **CSS styles** into the HTML template
  - Export of a **monolithic HTML** file that contains all 3D data, viewer logic, custom UI, and styling in a single distributable file

### Flowchart
<p align="left">
  <img src="readme_images/flowchart.png" alt="Flowchart" width="450"><br>
</p>
- HtmlTemplateBuilder<br>
A newly added class designed to dynamically generate a HTML template at runtime during the export process.

## Use Case Example: Exporting HOOPS Animation Creator Results

A key use case for this enhanced sample is the ability to export results created with **Animation Creator**. The sample can capture animation sequences and embed them directly into the monolithic HTML, enabling:
- Visualization of animated technical procedures
- Sharing of simulation scenarios
- Offline review of dynamic 3D content

## Dependencies
### SDKs in Use (Version)
* HOOPS Communicator: 2025.5.0
* HOOPS Exchange_Publish: 2025.5.0

### Tested Server Platforms
* Windows 11
* Ubuntu Server 24.04 LTS (AWE EC2 instance)

## Setup
### Demo folders
The project is organized as follows:
Export3DToHtml_temp_build/              # Root folder<br>
├── bin/                        <br>
│   └── Export3DToHtml                 # Monolithic HTML converter executable<br>
├── Export3DToHtml/                     # Project and sorce code<br>
│   ├── Export3DToHtml.cpp              # Main sorce code<br>
│   └── HtmlTemplateBuilder.cpp & .h    # HTML template builder source files<br>
├── template/                           # Split template files (HTML/JS/CSS)<br>
├── _VS2019.bat                         # Solution launcher batch file (for Windows)<br>
├── Export3DToHtml.sln                  #  Visual Studio solution file (for Windows)<br>
└── Makefile                            # Build script for Linux<br>

### Build Instructions
#### Windows
1. Edit `_VS2019.bat` according to your environment <br>
2. Double-click `_VS2019.bat` to open the Visual Studio solution <br>
2. Build the `Export3DToHtml` project <br>
3. The output executable will be located in `bin/` <br>

#### Linux
1. Edit `Makefile` according to your environment <br>
2. Open a terminal in the root directory (`Export3DToHtml_temp_build/`) <br>
3. Run `make` to build the project <br>
4. The resulting binary will appear in `bin/` <br>

> **Note:** Before building, ensure that the HOOPS Publish SDK include and library paths are correctly configured for your development environment.

### Run Instructions

After building the project, follow these steps to run the `Export3DToHtml` converter:<br>
1. Copy Required Runtime Files<br>
   Copy the necessary runtime files from the HOOPS Publish SDK `bin` folder into the executable directory.<br>
     Copy all files from `<HOOPS_PUBLISH_SDK>/bin/win64_v142/` or `linux64/` to`Export3DToHtml_temp_build/bin/`<br>
2. Open a Terminal and navigate to the executable directory:<br>
    `cd Export3DToHtml_temp_build/bin/`<br>
3. Run the Executable with Arguments
    `./Export3DToHtml [INPUT] [HTML_TEMPLATE_DIR] [OPTIONS] [OUTPUT] [LOG_FILE]`<br>
4. Verify Output<br>
   - The resulting monolithic HTML file will be created at the `[OUTPUT]` path<br>
   - Check `[LOG_FILE]` for conversion status or error messages<br>

#### Argument Descriptions

- `[INPUT]`: The 3D CAD file to embed in the HTML (e.g., `.prc`, `.stp`, `.jt`)<br>
- `[HTML_TEMPLATE_DIR]`: Path to the templates directory (usually `../template/`)<br>
- `[OPTIONS]`: Optional flags (e.g., toolbar/UI toggles)<br>
- `[OUTPUT]`: Path to save the resulting monolithic HTML file<br>
- `[LOG_FILE]`: Path to save the log file for conversion details<br>

#### Option Flags

The `[OPTIONS]` argument is a 7-character bit flag (e.g., `0011111`) used to control the viewer layout and custom behaviors.<br>

Each bit enables or disables a specific UI feature or customization. The flags are read from **left to right (bit 1 to bit 7)**:<br>

| Bit | Description | Value `1` = Enabled | Value `0` = Disabled |<br>
|-----|-------------|----------------------|-----------------------|<br>
| 1   | **Standard UI** (model tree, toolbar, axis triad, nav cube) | Show all standard UI | Disable → Use bits 2–4 to control individually |<br>
| 2   | Toolbar (only used when bit 1 = 0) | Show toolbar | Hide toolbar |<br>
| 3   | Axis Triad (only used when bit 1 = 0) | Show axis triad | Hide axis triad |<br>
| 4   | Navigation Cube (only used when bit 1 = 0) | Show nav cube | Hide nav cube |<br>
| 5   | Custom styles/scripts from `15_custom_style_script.html` | Inject custom CSS/classes | Do not inject |<br>
| 6   | Pre-start custom JS from `17_custom_script_before_start_viewer.js` | Run before viewer starts | Do not run |<br>
| 7   | Custom body UI from `21_custom_body.html` | Add UI elements inside `<body>` | Do not add |<br>

#### Examples

- `1000000`  <br>
  Enable **Standard UI** (model tree, toolbar, triad, nav cube), no custom scripts or UI.<br>

- `0111000`  <br>
  Disable Standard UI, but enable **Toolbar**, **Triad**, and **Nav Cube** individually.<br>

- `0001111`  <br>
  Disable Standard UI, hide all default UI, but **enable all custom extensions** (style, script before viewer, and custom body UI).<br>

> **Note:** The `template/` folder must include the corresponding files (`15_*.html`, `17_*.js`, `21_*.html`) for the custom bits (5–7) to take effect.<br>