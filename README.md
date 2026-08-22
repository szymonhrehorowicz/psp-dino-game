# PSP Game

## Game

Game for Sony PlayStation Portable. Inspired by [Dinosaur Game — Chrome Dino T-Rex Runner](https://chromedino.com/).

## Development

### SDK

Game is developed with the help of [PlayStation Portable Software Development Kit](https://pspdev.github.io/).

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
