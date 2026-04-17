# RacingManager

This is my C++/Qt learning process where I'm going to learn how to code force feedback features and general SDK development with C++. The UI is built with Qt.
The idea of this project is to be my "one-for-all" tool where I can adjust my racing wheel's FFB and other settings, and also launch other applications I use when playing iRacing. Overlays also play a huge role.

## Features
I have implemented a simple UI where user can select desired Overlays and make application launch options. Purpose of this "Application Launcher" is to open all the necessary
applications which are used when driving IRacing.

I have also implemented a simple delta-overlay, and position-speed-gear-fuel-overlay.

*Overlays are movable. These overlays are going to change to be more customizable. But for this demo, I just wanted to show concept.*

![Main UI with Overlays](img_1.png)

*Checkbox for overlays which you want to show or hide.*

![Overlay Selection Panel](img_2.png)

*Application launcher, where you can add applications and launch them with one click when you open this application from desktop.*

![Application Launcher Interface](img_3.png)

*Short gif showing how overlays work. I have implemented a simple delta-overlay, and position-speed-gear-fuel-overlay. These are going to be more customizable in the future.*

<img width="426" height="240" alt="overlay_demo" src="https://github.com/user-attachments/assets/499c29f6-652b-4fe6-84ba-6e119c044d20" />

## Stack
C++20  
Qt 6

## Getting Started
1. Clone the repository.
2. Build with CMake (see CMakeLists.txt for details).
3. Run the executable from the build directory.

For more details on setup or contributions, feel free to open an issue!