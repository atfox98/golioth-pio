# golioth-pio
Minimal template for PlatformIO/ESP-IDF/Arduino projects

# Problems
To add golioth to this project, I've been following [this golioth blog post](https://blog.golioth.io/how-to-add-golioth-to-any-esp-idf-project/).

I've run into the following issues:
1) From step 3: `CONFIG_MBEDTLS_KEY_EXCHANGE_PSK` does not appear to be an option in menuconfig (open a PlatformIO terminal and type `pio run -t menuconfig` to access the menuconfig)
2) From step 4: `golioth.h` doesn't appear to exist. Instead, I include `golioth/client.h` at the top of my code.
3) During compilation, an assembly language file appears to be missing:

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
