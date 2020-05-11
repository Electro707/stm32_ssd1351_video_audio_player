# Python program that takes a .mp4 file and converts it to a custom .hex file and a .wav file to be used with the STM32
# video and music player
import ffmpeg
import cv2
import numpy as np
import sys
from fractions import Fraction
import wx

# TODO: Add a .hex and .wav to the end of the given file name
# TODO: Add option for coping video (so a 16:9 video can be cropped into a 4:3 video)
# TODO: Try to make it faster ???
# TODO: Try with formats other than .mp4


# Function to open a file dialog and get the path
# https://stackoverflow.com/questions/9319317/quick-and-easy-file-dialog-in-python
def wx_get_path(wildcard):
    style = wx.FD_OPEN | wx.FD_FILE_MUST_EXIST
    dialog = wx.FileDialog(None, 'Open', wildcard=wildcard, style=style)
    if dialog.ShowModal() == wx.ID_OK:
        path = dialog.GetPath()
    else:
        path = None
    dialog.Destroy()
    return path


# Function to create a wx dialog to get a string
def wx_string_dialog(message):
    dialog = wx.TextEntryDialog(None, message)
    if dialog.ShowModal() == wx.ID_OK:
        val = dialog.GetValue()
        if val == '':
            val = None
    else:
        val = None
    dialog.Destroy()
    return val


# Function to map a value from range_a to range_b (similar to Arduino's map() function)
def map_range(inp, in_min, in_max, out_min, out_max):
    return (((inp - in_min) * (out_max - out_min)) // (in_max - in_min)) + out_min


# Convert the video's audio into a 8-bit PCM WAV file
def convert_audio(vid_name, out_name):
    audio_steam = ffmpeg.input(vid_name)
    out_audio = ffmpeg.output(audio_steam.audio, out_name, **{'ar': '44.1k', 'ac': 1,
                                                              'acodec': 'pcm_u8', 'bitexact': None, 'y': None})
    # print(ffmpeg.get_args(out_audio))
    ffmpeg.run(out_audio)


# Function to get some properties about the video
def get_video_properties(cv2_handler):
    frames_count = int(cv2_handler.get(cv2.CAP_PROP_FRAME_COUNT))
    w = int(cv2_handler.get(cv2.CAP_PROP_FRAME_WIDTH))
    h = int(cv2_handler.get(cv2.CAP_PROP_FRAME_HEIGHT))
    return frames_count, w, h


# Function to add a 'frame' to the video buffer
def add_to_hex_file(frame_buff, file_handler):
    for y in frame_buff:
        for pixel in y:
            pixel = [int(k) for k in pixel]
            r = map_range(pixel[0], 0, 255, 0, 0b11111)
            g = map_range(pixel[1], 0, 255, 0, 0b111111)
            b = map_range(pixel[2], 0, 255, 0, 0b11111)
            pixel_byte = (r << (5 + 6)) | (g << 5) | b
            file_handler.write(pixel_byte.to_bytes(2, byteorder='big'))


########################################################################################################################
# Start of Application
print("Start of Program")
# Create a wx app for the file and string dialog
wx_app = wx.App(None)
# Get the video file name
input_file_name = wx_get_path('*.mp4')
if input_file_name is None:
    print("No filename was given")
    sys.exit(1)
# Get the output hex file's desired name
out_vid_name = wx_string_dialog("Enter video name (leave blank for vid.hex)")
if out_vid_name is None:
    out_vid_name = 'vid.hex'
# Get the output wav file's desired name
out_audio_name = wx_string_dialog("Enter audio name (leave blank for music.wav)")
if out_audio_name is None:
    out_audio_name = 'music.wav'

# Create an opencv video capture object for the selected video and get some properties on it
vid_opencv = cv2.VideoCapture(input_file_name)
frame_count, vid_width, vid_height = get_video_properties(vid_opencv)
fraction_aspect_ratio = Fraction(vid_width/vid_height).limit_denominator(1000)

print("Video is %sx%s with an aspect ratio of %s" % (vid_width, vid_height, fraction_aspect_ratio))

# Check the aspect ratio of the input video
if (vid_width / vid_height) == (4/3):
    video_aspect = '4:3'
    video_resize_to = (128, 96)
    video_resize_to_dic = {'width': 128, 'height': 96}
elif (vid_width / vid_height) == (16 / 9):
    video_aspect = '16:9'
    video_resize_to = (128, 72)
    video_resize_to_dic = {'width': 128, 'height': 72}
else:
    print("Video is not in a 16:9 or 4:3 aspect ratio")
    sys.exit(1)

print("Reading video file and compressing it and converting video to custom .hex file")
# Create a buffer to store each video's pixel in
hex_file_handler = open(out_vid_name, "wb")
for i in range(frame_count):
    # Open the video's current frame
    ret, temp_buff = vid_opencv.read()
    if ret is False:
        break
    # Resize the video to either 128x72 or 128x96 and make the array RGB instead of the default BGR
    temp_buff = cv2.resize(temp_buff, video_resize_to, interpolation=cv2.INTER_LINEAR)
    temp_buff = cv2.cvtColor(temp_buff, cv2.COLOR_BGR2RGB)
    add_to_hex_file(temp_buff, hex_file_handler)
vid_opencv.release()    # "Close" the video
hex_file_handler.close()
# Convert the audio portion of the video into an 8-bit PCM WAV file
print("Converting video's audio data into 8-bit PCM WAV file")
convert_audio(input_file_name, out_audio_name)
# End if program
print("End of Program")
