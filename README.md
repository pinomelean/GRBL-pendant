# GRBL-pendant

Hardware pendant intended for use with G-code senders for GRBL machines

### Description
This USB pendant Includes many buttons, encoder and a thumbstick that can be mapped to the most common functions and G-code commands you need to use your machine.
It uses a Teensy++ 2 because of its physical size, IO, native USB, and ease of programming with the Arduino ecosystem, *as limited as it is*.

<img src="images/Concept.png">

## Pendant layout
The Thumbstick can be used either as a mouse pointer, along with a couple of buttons for clicking, or to quickly jog the machine when pressed in.

*The Teensy can emulate a game controller thumbstick, but as not many G-code sender applications support game controllers, and those that do (I only tested UGS) may not recognize it as a game controller, the thumbstick will not be emulating a game controller and just write G-code jog commands for now. This should work with any sender.*

The buttons at the top of the pendant are dedicated to the basic machine commands: Reset, Feed hold, Cycle start/Resume, Home machine and Kill alarm lock.

There are three encoders for fine jogging of each axis. By default each detent should result in 1mm of travel, and 0.1mm if the encoder is pushed in.

The two other encoders are meant for Feed and spindle speed overrides, but could be used for jogging the A and B axises in a 5-axis machine.

*I still need to figure how to send the Feed and Spindle speed override commands characters through a sender application if it does not support hotkeys*

Next to each encoder is a button which can be used to either home that axis, or zero it.
For the Feed and Spindle encoders, the button sets it to 100%.

At the bottom of the controller are the macro buttons.
Five of them are used for probing or touching against a workpiece from every direction (except from under it).

The other 4 buttons remain free for now, until I can think of useful G-code macros to have there by default.

**Of course, all of the actions are remappable and configurable to suit the needs and workflow of the user. The defaults are just what** ***I*** **think is most useful**

## Project status
- First prototype mostly built, silicone keypad left to see how ti all looks and feels. A couple of encoder push buttons don't work.
- Thumbstick as mouse pointer - Done. Works pretty well in smaller screens, slower in bigger ones.
- Thumbstick for jogging - UGS wouldn't recognize it in game controller mode, so It just types jogging G-code commands. Works ok.
- Encoder jogging - Works well for accurate positioning. Too slow for jogging all around the machine, but there's the thumbstick for that.
- Rest of the buttons - not yet done.

<img src="images/Status1.png">

<img src="images/Status2.png">

### Notes
When I started designing this pendant I wanted to use the Takachi WH145-25-N-B enclosure, as I had seen one of them at work before and it was an excellent enclosure with rubber sides for protection and felt high quality in every way.
I decided the form-factor and layout of the pendant based on that enclosure.

Due to the difficulty and expense of getting one or two units (as an individual) for prototyping, and because I found a case similar enough on Aliexpress, I've designed the PCB around that cheaper one for now.

The Aliexpress case (AK-H-78) looks similar, but it's all made from hard ABS plastic (likely not fire-retardant) including the coloured sides which I thought would be rubber. It has no threaded inserts in the bosses and they are in slightly different positions.

If this project ever takes off and there's interest in a version with a 15-20$ more expensive case, I would definitely do a PCB version for that. Maybe even do a small production run of something like 10 units to sell to those interested and so I can get one myself with the nicer case.
