# Read Me
## 3D Game Engine using DirectX11 as the graphics API
[![Build Status](https://img.shields.io/badge/Build_Status-passing-green)](https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP-)

![ScreenShots](https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP-/blob/main/screenshots/s1.png)

![ScreenShots](https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP-/blob/main/screenshots/s2.png)

# PESP Version 1.01 is a DirectX11 3D Game engine that supports basic rendering and is my first attempt on making a game engine.
***Disclaimer** This is not a stand-alone 3D game engine editor, this 3D game engine I tried making that supports basic rendering 
and currently is abandonded for my second iteration on this project. Unfortunately, further development will be 
close source for now.. feel free to check this repo, thank you!*

## Requirements

- **IDE:** any **C++17** *IDE*
- **Platform OS:** Windows
- **Graphics API:** DirectX11

## Features

- Externally import textures/materials/meshes
- 3D rendering capabilities of textures/materials/meshes
- Load object meshes into the world/game environment
- Add materials and textures onto meshes
- Camera movement with real-time text coordinates within the game world

## Info

*PESP* design is based off the ECS architecture (entity component system)
3D Game Engine desgin follows best industry practices and is written in **C++**  
by [Arben Temaj] and also checkout my [website][ATemaj Web]

> PESP is still under close repo development,
> No more features will be added to this repo but
> for now this project is my limited first iteration.
> To be clear this legacy code from my first attempt!
> Rest assured this 3D graphical engine is more than capable,
> Even with these limited features!

## Installation

 ```sh
 git clone https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP-/
 ```
 
### Download sources
 
 - DirectX11 graphics API link for download  [DirectX11](https://www.microsoft.com/en-us/download/details.aspx?id=17431)

 - DirectX Tool Kit link for download  [DirectXTK](https://github.com/microsoft/DirectXTK) 
 
##### tinyobjloader
 
This project uses tiny_obj_loader.h for its object parser download [tinyobjloader]

```sh
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

'in the cpp file where you load objects/meshes or just use mesh.cpp from the repo'
```

tiny_obj_loader.h must be include in your *IDE*   directories for the project to work!

## Development

Will try to contribute and update this repo with youtube video dev logs!
*PESP* development process will likely change and here are some 
exciting changes that will be coming soon...

- collision detection physics
- player character model animations

There are a lot more development changes in the works! The
Dev logs will be posted in youtube.

## Showcase
To view the My current 3D game engine project showcase click this link [youtube]

My dev logs will be under updates, please just subscribe to my youtube
to stay more updated.
 
## Updates

*Here are the most current posted updates from this repo*
```sh
'Will share more youtube links on my dev logs'
```

[//]: #

   [git-repo-url]: <https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP->
   [Arben Temaj]: <https://www.linkedin.com/in/arben-temaj/>
   [ATemaj Web]: <https://arbentemaj.github.io/>
   [tinyobjloader]: <https://github.com/tinyobjloader/tinyobjloader>
   [DirectX11]: <https://www.microsoft.com/en-us/download/details.aspx?id=17431>
   [DirectXTK]: <https://github.com/microsoft/DirectXTK>
   [youtube]: <https://www.youtube.com/watch?v=8NThtLEN47I&t=14s>
