# GRBL-pendant

Hardware pendant intended for use with G-code senders for GRBL machines

### Description
The aim of this project is to produce a physical controller which functions similarly to a machine pendant, but is not limited to only that. The device would allow the user to interact with both the computer and the CNC machine without needing to reach for the mouse and keyboard for the most machining tasks.
The hardware is not limited to a single purpose, though, as the firmware can be easily changed so the controller can suit the needs of the user, and be adapted for their particular workflow.

<img src="/Pictures/Concept.png" alt="Initial concept drawing" width="300"/>   <img src="/Pictures/Build10.png" width="500"/>

This USB pendant Includes many buttons, encoders and a thumbstick that can be configured with the most common functions and G-code commands you need to use your machine.
It uses a Teensy++ 2 because of its physical size, IO, native USB, and ease of programming with the Arduino ecosystem, *as limited as it is*.

### Free and open source

I publish all the files necessary for anyone to "DIY" it, all files can be opened and edited with FOSS software.
Anyone with a CNC mill/router should be able to make their own if they're so inclined.

The code is written as simple as I can manage (even if I suck at it), so anyone with basic knowledge and/or an Arduino tutorial open in another tab can modify it to suit their needs.

The PCBs are designed in KiCad and made to be simple enough to be milled at home, as I've done with the first prototype.

<img src="/Pictures/KiCad.png" alt="KiCad" width="800"/>

To mill the PCBs I used, and would recommend, [Juan Pablo Caram](https://github.com/jpcaram)'s [FlatCAM](http://www.flatcam.org/) and [Martin Pittermann](https://github.com/martin2250)'s [OpenCNCPilot](https://github.com/martin2250/OpenCNCPilot)

FreeCAD was used to design the silicone keypad and the mould to cast it.
The mould and the case were milled using toolpaths generated in the path workbench.

<img src="/Pictures/FreeCAD.png" alt="FreeCAD" width="800"/>

## Pendant layout

The layout I had in mind designing this pendant, and will come by default will be the following:

The Thumbstick is used either as a mouse pointer, along with a couple of buttons for clicking, or to quickly jog the machine when pressed in.

*The Teensy can emulate a game controller thumbstick, but as not many G-code sender applications support game controllers, and those that do (I only tested UGS) may not recognize the one emulated by the teensy, the thumbstick will not be emulating a game controller for nw, and just write G-code jog commands instead. This should work with any sender.*

The buttons at the top of the pendant are dedicated to the basic machine commands: Reset, Feed hold, Cycle start/Resume at the top, and Home machine and Kill alarm lock right of the thumbstick.

There are three encoders for fine jogging of each axis. By default each detent should result in 1mm of travel, and 0.1mm if the encoder is pushed in while turning.
Pushing an encoder without turning it will zero that axis.

The two other encoders are meant for Feed and spindle speed overrides, but could be used for jogging two extra axises in a 5-axis machine if anyone's running one of those.

*I still need to figure how to send the Feed and Spindle speed override command characters through a sender application if it does not have hotkeys for that*

Next to each encoder is a button which is used to individually home that axis.
For the Feed and Spindle encoders, the button resets it to 100%.

At the bottom of the controller are the macro buttons.
The five ones in the middle are used for probing or touching against a workpiece from every direction (except from under it).

The other 4 buttons are left for any extra macros the user could need, such as turning on/off mist/flood coolant, starting/stopping the spindle, touching a bit on the tool setter...

**Of course, all of the actions are remappable and configurable to suit the needs and workflow of the user. The defaults are just what** ***I*** **think is most useful**

## Project status

- Second version built. Looks much nicer in black and white. Probably final version if no issues arise.
	- The keypad also feels nice and works very well, but the Shore A20 durometer silicone might be too soft for this application, but will do for mow.

<img src="/Pictures/Build10.png" width="500"/>

<img src="/Pictures/Build11.png" width="500"/>

- Keypad mould machined. Couldn't get the 3D surfacing operation to work with a ball end mill en FreeCAD, so I had to resort to Fusion360 for that operation.
	- A sprue and vent have to be drilled manually into the side to inject the silicone with a syringe and push out the air.

<img src="/Pictures/Build4.png" width="500"/>

<img src="/Pictures/Build5.png" width="500"/>
	
- First prototype mostly built, silicone keypad left to see how it all looks and feels. A couple of encoder push buttons don't work, but will do for testing.
	- Several adjustments made for a second version. Will not make a mold and keypad for the first.

<img src="/Pictures/Build1.png" width="500"/>

- Thumbstick as mouse pointer - Done. Works pretty well in the smaller screens I use, slower in bigger ones, but it's adjustable.
- Thumbstick for jogging - UGS wouldn't recognize it in game controller mode, so It just types jogging G-code commands. Works ok.
- Encoder jogging - Works well for accurate positioning. Too slow for jogging around a bigger machine, but there's the thumbstick for that.
- Rest of the buttons - not yet programmed.

## Notes

