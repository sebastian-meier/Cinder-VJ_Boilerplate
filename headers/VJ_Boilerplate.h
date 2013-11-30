//
//  VJ_Boilerplate.h
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 30.09.13.
//
//

#include "Resources.h"

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <iostream>
#include <vector>

#include "WindowData.h"

//Input
#include "Midi.h"
#include "AudioAnalyzer.h"

//Visual
#include "AudioViz.h"
//Add more Visuals here:

//FBO
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"

//Shader
#include "Shader.h"
#include "ColorOffset.h"
//Add more shaders here:

using namespace ci;
using namespace ci::app;
using namespace std;

class VJ_Boilerplate : public AppNative {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void update();
    void shutdown();
	void draw();
    
    //Basic Settings
    //Screen-Size
    int app_width = 2048; //2048;
    int app_height = 768;
    //Visualization-Size
    int display_width = 2024; //2024
    int display_height = 400;
    
    //Grid Settings
    float grid_width = 20.0;
    float grid_height = 20.0;
    
    //Trips
    vector<Visual*> visuals;
    
    bool wireframe = false;
    bool showBorder = false;
    
    //FBO > Texture Stuff for the shaders
    gl::Fbo::Format format;
	gl::Fbo scene;
    
    //Shader
    vector<Shader*> shaders;
    float sinOffset = 0.0;
    
    //Midi System
    Midi midi;
    //AudioAnalyzer
    AudioAnalyzer audio;
};
