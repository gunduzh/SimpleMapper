# SimpleMapper (4-Point Video Mapper for Raspberry Pi)

## Overview

SimpleMapper is a C++ application developed using openFrameworks, tailored for media playback and simple 4 points interactive video mapping. It uses `ofxOMXPlayer` for efficient video playback, making it ideal for platforms like Raspberry Pi. The application provides functionalities for video playback control, interactive adjustment of video mapping points, and system shutdown.

## Downloadable Release

A compiled and ready-to-use version of SimpleMapper is available for download. This release is convenient for users who prefer not to build the application from source. Check the [releases section](https://github.com/gunduzh/SimpleMapper/releases) for the latest downloadable version.

## Prerequisites

- openFrameworks setup and configured.
- `ofxOMXPlayer` addon installed.

## Setup

1. Clone or download the SimpleMapper application source code.
2. Place the code in your openFrameworks `apps` directory.
3. Ensure `ofxOMXPlayer` is installed in your openFrameworks environment.
4. Compile and build the application using the openFrameworks project generator or your preferred IDE.

## Video File Configuration

- The application reads the video file path from a text file named `video`.
- Place the `video` text file in the `data` folder within the application directory.
- The `video` file should contain the path to the video file, relative to the `data` folder.
- For example, if your video file is named example.mp4 and located in the data folder, the video file should contain the text example.mp4.

## Usage

1. **Starting the Application**: Run the compiled executable to start video playback if a video file is specified and available.

2. **Interactive Control**: 
   - Use keys `1` to `4` for selecting corner points of the video mapping area.
   - Use arrow keys to adjust the position of the selected corner point.
   - Press `s` to save the current points configuration.
   - Press `p` to pause or resume video playback.
   - Press `r` to reset the points to default positions.
   - Press `d` to toggle the drawing of the video.
3. **Close Application**:
   - Press `Esc` or 'Ctrl+C'.
4. **Shutdown**: 
   - Long press `q` to initiate system shutdown.

## Starting SimpleMapper on Raspberry Pi Startup

To automatically start the SimpleMapper application when you open a terminal session on Raspberry Pi, add the following line to the `.bashrc` file:

1. Open the `.bashrc` file in a text editor:
   ```bash
   nano ~/.bashrc
2. Add the following line at the end of the file:
   ```bash
   /path/to/SimpleMapper/SimpleMapper

Replace /path/to/SimpleMapper/SimpleMapper with the actual path to the SimpleMapper executable.

Save and exit the editor. (In nano, press CTRL+X, then Y to confirm, and Enter to save.)

Now, when you open a terminal session on your Raspberry Pi, the SimpleMapper application will start automatically.

## Performance

SimpleMapper utilizes `ofxOMXPlayer` for optimized video playback performance, especially on Raspberry Pi hardware. For more details and performance considerations, please refer to the [ofxOMXPlayer GitHub repository](https://github.com/jvcleave/ofxOMXPlayer).

