# golioth-pio
Minimal template for PlatformIO/ESP-IDF/Arduino projects

# Setup
VSCode + PlatformIO

To clone:

        git clone https://github.com/atfox98/golioth-pio --recursive

# Usage
This project is the golioth "Hello" example using the Arduino framework. To get it working, just add your WiFi credentials and golioth PSK ID/PSK to the top of main.cpp:

        #define WIFI_SSID       ("SSID")
        #define WIFI_PASS       ("PASS")
        #define GOLIOTH_PSK_ID  ("PSK ID")
        #define GOLIOTH_PSK     ("PSK")

See the [ESP-IDF examples](https://github.com/golioth/golioth-firmware-sdk/tree/main/examples/esp_idf) provided by golioth for more complex use cases.

# Notes on project creation, initialization
[This golioth blog post](https://blog.golioth.io/how-to-add-golioth-to-any-esp-idf-project/) does a pretty good job of explaining how to add golioth to an ESP-IDF project. However, there are a few extra steps when using Golioth with PlatformIO and `framework = arduino, espidf`. Here are all the steps I took to create this project:

- I edited the menuconfig from the blank PlatformIO project to use Arduino setup & loop. I renamed the main source file to `main.cpp`, added the setup and loop functions, and included `Arduino.h`

- I named the `third-party` directory from the blog post `components`. This is in line with what PlatformIO expects, [per their documentation](https://docs.platformio.org/en/latest/frameworks/espidf.html#esp-idf-components). 
  - The actual component directory resides deeper in this folder, so you will still have to edit CMakeLists.txt like the blog post linked talks about.
  - All of the menuconfig options listed in the blog post were set too.

- Add the following line the environment configuration in platformio.ini:

        board_build.embed_txtfiles = components/golioth-firmware-sdk/src/isrgrootx1.der

- When including golioth headers, wrap them in `extern "C" { }`:

        extern "C" {
        #include "golioth/client.h"
        }

This last bullet point may not be the case forever. See [this issue](https://github.com/golioth/golioth-firmware-sdk/issues/524) for more details.