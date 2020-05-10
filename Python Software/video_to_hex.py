#! python3
#
# This program takes in a 128x72 image and converts it so that the output buffer
# can be used in an SSD1351 module without extra math or computation
# This program generates the bytes to be sent to the display with a 2-byte per pixel 
# configuration (65k color depth) 
#
# Author : Jamal Bouajjaj
#
#
####################################################################################################

from PIL import Image
import sys
import math

def mapRange(i, in_min, in_max, out_min, out_max):
    return (((i - in_min) * (out_max - out_min)) // (in_max - in_min)) + out_min

def main():
    # Get variables from user
    imagename = input("Type image file name\n")
    batch_numbers = input("Type number of images from 0 to x\n")
    batch_numbers = int(batch_numbers)
    
    numb_file_increment = 0
    
    f = open("BatchOutput/vid0.hex", "wb")
    
    for num_img in range(0, batch_numbers+1, 1):
        finalhex = []
        # Open image and determin width and height
        try:
            im = Image.open("BatchImages/%s_%06d.png" % (imagename, num_img))
            #im = im.convert('RGB')
        except IOError:
            print("Please give a proper image file")
            sys.exit(2)
        w = im.width
        h = im.height
        print("Width is :", w)
        print("Height is :", h)
        print("Current Image %s"%num_img)

        if w != 128:
            print("Width is not 128px, exiting...")
            sys.exit() 
        #if h != 72:
        #    print("Height is not 722px, exiting...")
        #    sys.exit() 

        for y in range(h):
            for x in range(w):
                pixel = im.getpixel((x, y))      # Get the selected pixel's color data
                r = mapRange(pixel[0], 0, 255, 0, 0b11111)
                g = mapRange(pixel[1], 0, 255, 0, 0b111111)
                b = mapRange(pixel[2], 0, 255, 0, 0b11111)
                finalhex.append((r<<(5+6)) | (g<<5) | (b))

        
        for i in range(len(finalhex)):
            f.write(finalhex[i].to_bytes(2, byteorder='big'))
        
        numb_file_increment += 1
        
    f.close()
    
    # End of program, wait for button press to exit
    input("Press Enter to continue...")

if __name__ == "__main__":
    main()
