Cinder-VJ_Boilerplate
=====================

A Music Visualization Boilerplate using the Cinder Library

## SETUP

Most of the files required to get going are already included. The only thing you need to do, is linking this project to your Cinder-Library. For doing so, go to your Project > Build Settings > User-Defined and then change "CINDER_PATH", so it matches your Cinder directory.

## Components

The System consists of four main components. 

## Audio

An implementation of KissFFT is creating an fft-band and a simple beat detection. The results are passed to the shaders and visualizations via an EventListener-System.

## Midi

An implementation of RtMidi is connecting all available Midi-Devices. All incoming Midi-Events are passed to the shaders and visualizations via an EventListener-System.

## Shader

The shader component is holding basic functionality to create and update shader. One of the shaders can then be applied to the running set of visualizations.

## Visuals

## License

The visuals component is the heart of the boilerplate...

The KissFFT Library included in this repository belongs to BanTheRewind
https://github.com/BanTheRewind/Cinder-KissFft/

The RTMidi Library included in this repository belongs to Gary P. Scavone
http://www.music.mcgill.ca/~gary/rtmidi/

My code is published under the MIT/GPL.

* http://en.wikipedia.org/wiki/MIT_License
* http://en.wikipedia.org/wiki/GNU_General_Public_License

If you make enhancements or code changes i would love to know so i can reshare your findings.