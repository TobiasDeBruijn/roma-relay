# roma-relay
STM32-based relay controller for the Roma project.

## Compiling
Requirments:
- `gcc-arm-linux-gnueabihf`
- `openocd`
- `cmake`
- `make`

From the repository root:
1. `cmake -B build -DCMAKE_BUILD_TYPE=Release`
2. `cd build/`
3. `make`

## Uploading
From the repository root:
1. `openocd -f openocd-stlink.cfg -c "program build/smartbathroom-static-flusher.elf verify reset exit"`