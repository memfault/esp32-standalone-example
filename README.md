# ESP32 Standalone Memfault Demo Application

This Demo App is based on the example in the Memfault Firmware SDK:

https://github.com/memfault/memfault-firmware-sdk/tree/0.39.0/examples/esp32

It also showcases including the Memfault SDK as a submodule for an ESP-IDF
project.

The submodule was added with this command:

```bash
❯ git submodule add https://github.com/memfault/memfault-firmware-sdk.git \
  third-party/memfault-firmware-sdk
```

When cloning this repo, either use the `--recursive` flag or update submodules
after cloning:

```bash
❯ git clone --recursive https://github.com/memfault/esp32-standalone-example
# or
❯ git clone https://github.com/memfault/esp32-standalone-example
❯ cd esp32-standalone-example
❯ git submodule update --init --recursive
```

## Building

Can be built using `idf.py build` as usual.
