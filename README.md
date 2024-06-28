# golioth-pio
Minimal template for PlatformIO/ESP-IDF/Arduino projects

# Setup
VSCode + PlatformIO

To clone:

        git clone https://github.com/atfox98/golioth-pio --recursive

# Problems
To add golioth to this project, I've been following [this golioth blog post](https://blog.golioth.io/how-to-add-golioth-to-any-esp-idf-project/).

I've run into the following issues:
1) ~~From step 3: `CONFIG_MBEDTLS_KEY_EXCHANGE_PSK` does not appear to be an option in menuconfig (open a PlatformIO terminal and type `pio run -t menuconfig` to access the menuconfig)~~ Fixed with push on 6/18/2024
2) From step 4: `golioth.h` doesn't appear to exist. Instead, I include `golioth/client.h` at the top of my code.
3) ~~During compilation, an assembly language file appears to be missing:~~

        ...
        Compiling .pio\build\esp32dev\components\golioth-firmware-sdk\src\golioth_debug.o
        Compiling .pio\build\esp32dev\components\golioth-firmware-sdk\src\ringbuf.o
        Compiling .pio\build\esp32dev\components\golioth-firmware-sdk\src\event_group.o
        Compiling .pio\build\esp32dev\components\golioth-firmware-sdk\src\mbox.o
        Compiling .pio\build\esp32dev\components\golioth-firmware-sdk\src\fw_block_processor.o
        Compiling .pio\build\esp32dev\components\golioth-firmware-sdk\src\coap_blockwise.o
        Compiling .pio\build\esp32dev\components\golioth-firmware-sdk\src\zcbor_utils.o
        *** [.pio\build\esp32dev\.pio\build\esp32dev\isrgrootx1.der.o] Source `.pio\build\esp32dev\isrgrootx1.der.S' not found, needed by target `.pio\build\esp32dev\.pio\build\esp32dev\isrgrootx1.der.o'.
        ===================================================== [FAILED] Took 35.83 seconds =====================================================

   ~~Note: I did find `isrgrootx1.der` in `golioth-firmware-sdk/src` and in the CMake configuration (`goliath-firmware-sdk/port/esp_idf/components/golioth-sdk/CMakeLists.txt`, line 51). I haven't really dug into the configuration/build process but it looks like something that should be happening isn't.~~

   PlatformIO board_build.embed_txtfiles takes care of this. The project succesfully compiles with an empty setup and loop.

4) Linker Problems! Golioth shows up in the esp-idf menuconfig, gets built with the firmware, but all the calls to the components functions result in undefined reference errors. I have verified that the library is getting built: `.pio/build/esp32dev/esp-idf/golioth_sdk/libgolioth_sdk.a` exists, and using `nm` shows all of the functions that are being showed as undefined by the linker step. When using verbose build, it looks like this archive is included correctly. The functions do not appear in the map file that is generated during the build. Here is what I have tried to get this working:

- Change LINK_INTERFACE_MULTIPLICITY in CMakeLists.txt for the golioth component. The [build system](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) page in the espressif documentation under "Circular Dependencies" mentions this can fix some undefined reference problems. Even making the value ridiciously high (100+) doesn't work.
- Add the linker flags manually in PlatformIO build flags (-Lpath/to/golioth_sdk and -lgolioth_sdk.a)
- Use a pre: script to pass the same link flags as above, per [this documentation](https://docs.platformio.org/en/latest/scripting/examples/extra_linker_flags.html)


