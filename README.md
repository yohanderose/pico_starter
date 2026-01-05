# Raspberry Pi Pico Project Boilerplate

A minimal Raspberry Pi Pico starter with fast rebuild/flash workflow via software-triggered BOOTSEL from host.

## Prerequisites

- [Pico SDK](https://github.com/raspberrypi/pico-sdk) (clone with `--recurse-submodules`)
- CMake 3.13+, ARM GCC toolchain
- `picotool` for flashing

## Setup

1. **Clone the SDK**:

   ```bash
   git clone --recurse-submodules https://github.com/raspberrypi/pico-sdk.git
   ```

2. **Set environment variable**:

   ```bash
   export PICO_SDK_PATH=/path/to/pico-sdk
   ```

3. **Copy SDK import file**:

   ```bash
   cp $PICO_SDK_PATH/external/pico_sdk_import.cmake .
   ```

4. **Specify your board** in `Makefile` (line ~15):

   ```cmake
   cmake -DPICO_BOARD=pico_w ..  # or pico, pico2, etc.
   ```

## Build & Flash

The Makefile `reset` command triggers software BOOTSEL over serial, eliminating manual button presses during development.

```bash
make build # Cmake and make project, warning on failure
make flash  # Resets, builds, and flashes in one command
```


## Common Pitfalls

- **Submodules**: Forgot `--recurse-submodules`? Run `git submodule update --init` in the SDK directory
- **PICO_SDK_PATH**: Must be set before building. Add to `.bashrc`/`.zshrc` for persistence
- **Wrong board**: Build fails? Check `PICO_BOARD` matches your hardware
- **Serial permissions**: Add user to `dialout` group: `sudo usermod -a -G dialout $USER` (logout required)

## Resources

- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- [Getting Started Guide](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
- [Pico C/C++ SDK Book](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
