# automovieplayer
Simple automatic movie player for exhibition.
All setting is saved with ofxXmlSettings.

You can all of contol this player with just mouse(or trackpad).

This version is only for one movie file.
(for IDD exhibition Ver)

## Requirements
- openFrameworks 0.9.8+
- ofxImGui
- ofxXmlSettings

## How to use
![SC](https://github.com/gilsrus/automovieplayer/raw/master/screenshot.png)

#### 1. frame
- Current frames / Total Frames
- Jump frame
(Select some frames and push 'Frame Jump')

### 2. player
- Load Movie...
Support movie files by quicktime (ofvideoplayer)
- Play,Pause,Stop

### 3. setting
- Repeat
- Projection Test Pettern Image
You can change Imagefile.(/bin/data/tp.png)
Default image is 1920 x 1080.
(http://www.desktopwallpaperhd.net/testcard-video-testcardk-39648.html)
(Your Resolution lower than 1080P)It will display 720p size(1280 x 720).

- User Resolution
You can set Witdh and Height with Original Aspect ratio.

- Movie resolution Mode
Fullscreen is not allow Original Aspect Ratio.

- Hide GUI
Press key 'g'  --  toggle Show GUI
double click mouse 'left button' -- Show GUI (Only work unvisible GUI)


### 4. help
- Press key 'Right Arrow'  --  Skip 30 frames foward.
- Press key 'Left Arrow'  --  Skip 30 frames backward.
- Press key 'f'  --  openframeworks Fullscreen Toggle.
- Press key 'g'  --  toggle Show GUI

## Copyright
Copyright 2017 gilsrus.
