<div class="row">
<div class="col-12 col-md-3 order-md-12 doc-sidebar">
<nav id="toc" class="sidebar-toc sticky-top">

<ul class="nav flex-column nav-pills">
  <li><a class="nav-link" href="#final-project"><strong>Final Project</strong></a></li>
  <li><a class="nav-link" href="#project-description"><strong>Project Description</strong></a></li>
  <li><a class="nav-link" href="#how-to-run-our-code">How to Run Our Code?</a></li>
  <li><a class="nav-link" href="#future-features">Future Features</a></li>
  <li><a class="nav-link" href="#engaged">Engaged</a></li>
  <li><a class="nav-link" href="#not-engaged">Not Engaged</a></li>
  </ul>

</nav>
</div>

<div class="col-12 col-md-9 doc-main">

<div class="row">
<div class="col">

# Final Project

## Project Description
Our project is an RPG adventure game including character, monster, and several rooms. To win this game, the player has to find the key of the exit door and find the room which connects the exit door. In the game, there would be some monsters in some rooms. When the player gets into the room which has monster inside, the player is engaged. When fighting with a monster, the rule is all about strength. If the character’s strength is larger than the monster’s, then the character wins and good to do other actions and move to the next room; however, if the monster’s strength is greater than the character’s, then you are dead and lose the game.

## How to Run Our Code?
We choose C++ to achieve modularity. There are three `.hpp` files and four `.cpp` files. When compiling, you need a C++ environment and execute `adventure.sln` in Visual Studio to run the program. When running the program, the character will start at the initial room and start adventuring.
When get to a room, there might be a treasure in it, which might include weapons or a key to the exit door. For now, we have three options, one is that you have two third chances to get the key. Second is that you can fight with the monster to get the key. Last one is the exit door. If you have the key, you can escape the room and win the game. 


## Future Features
In the future, we have some commands for a player to do in two circumstances:

## Engaged

#### Hit
When engaged, the player can choose to fight with the monster. When the character’s strength is greater than the monster’s, then you win. If your strength is smaller than the monster’s, then you lose the game. 

#### Esc
When engaged, the player can choose to escape the room and move back to the previous room.

## Not Engaged

#### Move
The player can choose to move to the room they want.

#### Grab
When getting to the room, if the room has some objects, the player can grab it. If there is nothing to grab, the program will show the error message and continue the game.

#### Des
The player can destroy their objects from them and the object will no longer exist. If they don’t have items, the program will show the error message and continue the game.
