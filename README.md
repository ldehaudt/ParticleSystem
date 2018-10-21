# ParticleSystem

This project has for a goal to render millions of particles that all interact with a gravity center at a reasonable framerate.
Using openCl for calculationg particle positions and openGl to render them, this was done by allocating the particles only on the vRam.

The primary challenge of this project was getting openGl and openCL to work together nicely. I used c++ with a class for each to make it simpler to
work with/ understand.

I recomend trying this one out. Enjoy ^-^

## Compiling and running

Run `make`. An executable will compile. Currently only tested on OS X.

Run `./particleSystem`.

You can run `./particleSystem [num particles]` with any number between 100 and 30000000 to set teh number of particles.

## input

`q` to release particles

`space` to stop gravity from following the mouse

`scroll in/out` to zoom in/out

`esc` to quit


![](2.gif)

![](1.gif)

![](3.gif)
