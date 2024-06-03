# Read Me
## PESP ---> "Project ESP" 3D Game/Engine

![ScreenShots](https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP-/blob/main/screenshots/s1.png)

![ScreenShots](https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP-/blob/main/screenshots/s2.png)

[![Build Status](https://img.shields.io/badge/Build_Status-passing-green)](https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP-)

# PESP is a DirectX11 3D Game Independent Project
***Disclaimer** This is not a stand-alone 3D game engine editor, this 3D game engine is for an independent game 
that currently is under development and files are subject to change. Unfortunately, further development will be 
close source for now.. feel free to check this repo, thank you!*

## Requirements

- **IDE:** Visual Studio 2022 Community or any **C++** *IDE*
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

> PESP is still under development,
> more features will be added but
> for now this project is limited.
> To be clear this is a 3D game first
> and may not have all the features of
> a 3D game engine. Rest assured this 3D
> graphical engine is more than capable,
> Even with these limited features!

## Installation

 - GitHub repo link 
 
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

Will try to contribute and update this repo as much as possible!
*PESP* development process will likely change and here are some 
exciting changes that will be coming soon...

- collision detection physics
- player character model animations
- Game hud images and rendering of images
- Cmake GUI (currently using Windows GUI)

There are a lot more development changes in the works! The
graphics API will continue to be *DirectX* and going to update
from *DirectX11* to *DirectX12* shortly after these changes.
 
## Updates

*Here are the most current posted updates from this repo*
```sh
'coming soon =)'
````

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/ArbenTemaj/3D-Game-Engine-Project--PESP->
   [Arben Temaj]: <https://www.linkedin.com/in/arben-temaj/>
   [ATemaj Web]: <https://arbentemaj.github.io/>
   [tinyobjloader]: <https://github.com/tinyobjloader/tinyobjloader>
   [DirectX11]: <https://www.microsoft.com/en-us/download/details.aspx?id=17431>
   [DirectXTK]: <https://github.com/microsoft/DirectXTK>
