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
* Five scene game: title, game (stage 1-2-3), game over
* Single player mode, three stages with increasing difficulty
* Left and Right Arrows for movement
* Up Arrow for jumping
* Basic music & sound effects
* VSync enabled
* Average FPS counter

## Save File
* Make sure to extract the game in a folder where you can create files
* The game autosaves  in a binary file at the start of each stage (not checkpoints!)
* The info stored in the file are: starting stage, lives, coins and score
* If you want to delete the savefile, you can find it in the `data` folder 

## Customizable Stages
* The stages are realized with a tiling system
* In the `data` folder you can find 3 files: `stage1.map`  `stage2.map`  `stage3.map`
* Inside these file there are the maps for the entire stages
* You can freely customize these files as you like, just follow the format and use valid tile codes

> My advice, however, is to edit your levels using the spreadsheet included in the project.  
> It's much easier to work this way and the effect of your changes is much more direct and understandable.  
> Open the spreadsheet and you will find one sheet for each stage, each cell represent a tile:  
  
![image](https://user-images.githubusercontent.com/88102377/169651515-5b4b144c-2eea-4462-8a1e-27a5d8284408.png)
  
> The color is not relevant, it is just used to give a better prospective of the layout.  
> The only data that matters is the code inside every cell:  

<p vertical-align="middle"> <img src="https://user-images.githubusercontent.com/88102377/169842473-5d66d0e1-bac5-42e5-a742-d17cc75aefee.png"> 01 </p>

empty				00						coin				06
earth				01										
grass				02						flagend				12
brick				03						flagcp				13
brick_dark	04						flagpole			14
spike				05										


> You can now edit the file as you like. When you're done just export the file as `.csv`  
> Open it with any text editor and replace every `";"` with a blank space `" "`  
> Finally replace the rows in the file `.map` relative to the desired stage and you're good to go!  

<br/>
<br/>

`Code is a little over-commented just to help anyone interested to navigate it better`  
