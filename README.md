# Runout_Test_Stepper
## Problem:
### Manufacturing Engineers wanted to rotate a shaft of a product exactly three times as drawing spec to measure runout of a piston on the assembly line.

Repo contains code, PCB design and BOM.


The design used a stepper motor with a friction fit 3d printed coupling for easy removal of the shaft as it needed to continue down the assembly line. Below is a test video of the concept, final versions cannot be shown due to restrictions.



https://user-images.githubusercontent.com/49006906/172272815-928d265e-da3f-4b31-8efb-8327f7f1d115.mp4


















# V1
AccelStepper is v1 of code
Button is wired to reset
no LED indicator
must reset system to run motor again

# V2 is the final version of the code
### Folder contains PCB design, BOM and code
Button is wired to digital pin
LED blinks on standby
LED solid when running motor
can constantly run motor without resetting arduino
