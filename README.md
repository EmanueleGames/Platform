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

<img align="left" src="https://user-images.githubusercontent.com/88102377/169842473-5d66d0e1-bac5-42e5-a742-d17cc75aefee.png"><p align="left"> `01` </p> 
<img align="left" src="https://user-images.githubusercontent.com/88102377/169850543-4028d58d-93ae-4fe6-87e3-d10074f3ffc4.png"><p align="left"> `02` </p> 
<img align="left" src="https://user-images.githubusercontent.com/88102377/169850288-c57e448f-7abf-4adc-a1d2-5e7ceb4e3456.png"><p align="left"> `03` </p> 
<img align="left" src="https://user-images.githubusercontent.com/88102377/169850304-73fbe59a-a557-4389-a8d4-9db72ce8c279.png"><p align="left"> `04` </p> 
<img align="left" src="https://user-images.githubusercontent.com/88102377/169848922-f72913aa-c8e0-4301-9613-00655d39d21f.png"><p align="left"> `05` </p> 
<img align="left" src="https://user-images.githubusercontent.com/88102377/169848937-939414ca-3329-47ac-a97d-32a94c3aa7ea.png"><p align="left"> `06` </p> 
<img align="left" src="https://user-images.githubusercontent.com/88102377/169848986-cd89ec1e-5d64-4879-99e2-55fa775e8ee9.png"><p align="left"> `12` </p> 
<img align="left" src="https://user-images.githubusercontent.com/88102377/169848995-2349ae62-b0e3-4bae-bcc9-c3f7eb02c74b.png"><p align="left"> `13` </p> 
<img align="left" src="https://user-images.githubusercontent.com/88102377/169849000-1867815a-9e9b-487c-b053-b086a992e04a.png"><p align="left"> `14` </p> 
  
> You can now edit the file as you like. When you're done just export the file as `.csv`  
> Open it with any text editor and replace every `";"` with a blank space `" "`  
> Finally replace the rows in the file `.map` relative to the desired stage and you're good to go!  

<br/>
<br/>

`Code is a little over-commented just to help anyone interested to navigate it better`  
