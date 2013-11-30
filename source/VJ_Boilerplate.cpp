#include "VJ_Boilerplate.h"

void VJ_Boilerplate::prepareSettings( Settings *settings ){
    //Add this if you want to enable Retina Screens
    //Be aware that enabling this might drop your framerate
	//settings->enableHighDensityDisplay();
}

void VJ_Boilerplate::setup(){
    /*--- SCREEN #1 ---*/
    //this is the display we can use to display controls ect.
    getWindow()->setUserData( new WindowData );
    WindowData *data = getWindow()->getUserData<WindowData>();
	data->type = 0;
    setWindowSize(display_width1, display_height1);
    getWindow()->setPos(display_x1, display_y1);
    if(display_borderless1){    getWindow()->setBorderless();}
    if(display_alwaysontop1){    getWindow()->setAlwaysOnTop();}
    if(display_fullscreen1){    getWindow()->setFullScreen(true);}

    /*--- SCREEN #2 ---*/
    vector<DisplayRef> displays = Display::getDisplays();
    if(multiscreen && displays.size()>1){
        //If there is a second screen and multiscreen = true
        //There is a second window added where we can visualize ui elements, parameters, etc.
        Window::Format WindowFormat = Window::Format();
        WindowFormat.setDisplay(displays.at(display_id2));
        WindowFormat.setPos(display_x2, display_y2);
        WindowFormat.size( display_width2, display_height2 );

        if(display_borderless2){    WindowFormat.setBorderless();}
        if(display_alwaysontop2){   WindowFormat.setAlwaysOnTop();}
        if(display_fullscreen2){    WindowFormat.setFullScreen(true);}

        app::WindowRef newWindow = createWindow( WindowFormat );
        newWindow->setUserData( new WindowData );
        WindowData *data1 = newWindow->getUserData<WindowData>();
        data1->type = 1;
    }
    
    /*--- MAIN SCENE ---*/
    //Setting up our main scene, we will draw onto this and use it for our shaders later on
    gl::Fbo::Format format;
	format.enableMipmapping(false);
	format.setCoverageSamples(16);
	format.setSamples(4);
    scene = gl::Fbo(display_width1, display_height1, format);
    
    /*--- VISUALIZATIONS ---*/
    visuals.push_back(new AudioViz);
    //add more visuals here:
    //visuals.push_back(new VISUAL_CLASSNAME);
    
    //initialize all visuals and register them for midi- and audio-events
    for(auto visual : visuals){
        visual->setup(display_width1, display_height1);
        visual->init();
        audio.registerListener(visual);
        midi.registerListener(visual);
    }

    /*--- SHADERS ---*/
    shaders.push_back(new ColorOffset);
    shaders.at(0)->setup(SHADER_VERT_ColorOffset, SHADER_FRAG_ColorOffset);
    //add more shaders here:
    //shaders.push_back(new SHADER_CLASSNAME);
    //shaders.at(0)->setup(SHADER_RESOURCE_VERT, SHADER_RESOURCE_FRAG);
    
    //register all shaders for midi- and audio-events
    for(auto shader : shaders){
        audio.registerListener(shader);
        midi.registerListener(shader);
    }
    
    //initialize the midi and audio components
    midi.setup();
    audio.setup();
}

void VJ_Boilerplate::update(){
    //update the midi and audio component
    midi.update();
    audio.update();
    
    //update the visuals
    //only the visuals with parameter "active = true" get updated
    for(auto visual : visuals){
        visual->requestUpdate();
    }
}

void VJ_Boilerplate::draw(){
    gl::enableAlphaBlending();
    gl::clear( Color( 0, 0, 0 ) );
    WindowData *data = getWindow()->getUserData<WindowData>();
	if(data->type == 0){

        //write visualization to scene
        Area  viewport = gl::getViewport();
        scene.bindFramebuffer();
        gl::setViewport(scene.getBounds());
        gl::clear( Color( 0, 0, 0 ) );
        
        //Drawing Commands
        for(auto visual : visuals){
            visual->requestDraw();
        }
        
        //For some weird reason we need to call an gl-command after the drawing ?!
        gl::color(255,255,255);
        scene.unbindFramebuffer();
        
        for(auto shader : shaders){
            shader->requestStart();
            shader->requestSet();
        }
        
        //draw the visualization inside the shader commands
        gl::pushModelView();
        gl::translate(Vec2f(0, getWindowHeight()));
        gl::scale(Vec3f(1, -1, 1));
        gl::draw(scene.getTexture(), getWindowBounds());
        gl::popModelView();
        
        for(auto shader : shaders){
            shader->requestEnd();
        }
        
        gl::setViewport(viewport);

        visuals.at(visuals.size()-1)->requestDraw();
        
    }else{
        //If you have multiple windows you can define different type of actions for each window...
        //visuals.at(0)->draw();
    }
}

void VJ_Boilerplate::shutdown(){
    midi.shutdown();
}

CINDER_APP_NATIVE( VJ_Boilerplate, RendererGl )
