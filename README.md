# STM32 SSD1351 Video & Audio Player
This is the repository for an STM32F103C8T6 (commonly found on "blue-pill" modules) music and video player on an SSD1351 OLED Module (I bough from from Buy-Display.com). The video and audio are stored unto an SD card which is connected to the STM32 microcontroller. The audio file is an 8-bit WAV file, and the video is a custom .hex file generated by the Python program in this repository. From what I tested so far, this player can output music at a 44.1Khz sample rate and 128x96 video at ~25FPS(for a 4:3 aspect ratio video). The audio is an 8-bit WAV file, and the video file is generated by my custom Python program found in this repository. 


The IDE used for the STM32 is the official STM32CubeIDE (found on ST's site)


Currently, this project is not too well-documented, but I'm working on getting the code refined/generalized and documented. Feel free to look around tough (hopefully the code makes a bit of sense). I have also put the current documentation in the [Documentation/text.md](Documentation/text.md) file. It's just a plain text file with a description of what each part of the program does.


As a fun fact: In theory, altough i've never tried it, this player could play the entire Bee movie, altough the video file size could be an issue (the video is stored as a .hex file with 2 bytes per pixel per frame of the video).
