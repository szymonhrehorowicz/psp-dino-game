# PSP Game

## Development

### Building

Run `build.sh` to build the software. This script consists of:

```sh
#!/bin/bash
cd ./build
psp-cmake ..
make
```

### Run in emulator

Programs can be run on desktop in emulated environment provided by "PPSSPP" with the `run.sh` script, which consists of:

```sh
#!/bin/bashs
flatpak run org.ppsspp.PPSSPP 
./build/EBOOT.PBP
```

#### Controls

- up - up
- down - down
- left - left
- right - right
- O - x
- X - z
- [  ] - a
- /\ - s
