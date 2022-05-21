# Jumps & Coins
<br/>

<p align="center">
  <img src="http://emanuelecarrino.altervista.org/images/portfolio/platform_1280x720.png" />
</p>
<br/>

## Development
**IDE:** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Microsoft Visual Studio  
**Language:** &nbsp;&nbsp; C++  
**Libraries:** &nbsp;&nbsp;&nbsp;&nbsp; SDL2 (Simple DirectMedia Layer)
<br/>
> Platform 2D videogame.  
> Multiple scene implemented with Object Oriented State Machine:  
> inheritance, polymorphism, operator overloading.  
> Time based movement (frame indipendent), multiple collision detection.  
> File writing and file reading to implement saves.  
> Stages designed with customizable tiling.  
> Multiple source files. 1280x720 pixels resolution.  

## Features
* Triple scene game with multiple stages: title, game (stage 1 2 and 3), game over
* Single player mode, three stages with increasing difficulty
* Left and Right Arrows for movement
* Up Arrow for jumping
* Basic music & sound effects
* VSync enabled
* Average FPS counter

## Save File
* Make sure to extract the game in a folder where you can create files
* The game autosaves  in a binary file at the start of each stage (not checkpoints!)
* In the file is stored the starting stage, lives, coins and score
* If you want to delete the savefile, you can find it in the /data/ folder 

## Customizable Stages
* The stages are realized with a tiling system.
* In the /data/ folder you can find 3 files: stage1.map stage2.map stage3.map
* Inside these file there are the maps for the entire stages
* You can freely customize these file as you like, just follow the format and use valid tile codes

My advice, however, is to customize your levels using the spreadsheet included in the project.
It's much easier to work this way and the effect of your changes is much more direct and understandable.
Open the spreadsheet and you will find one sheet for each stage, each cell represent a tile
The color is not relevant, it is just used to give a better prospective of the layout
The only data that matters is the code inside every cell
You can now edit the file as you like. When you're done just export the file as .CSV
Open it with any text editor and replace the ";" with a blank space " "
Finally copy the rows in one of the file .map that you want to replace and you'ew good to go.

<br/>
<br/>

`Code is a little over-commented just to help anyone interested to navigate it better`  
