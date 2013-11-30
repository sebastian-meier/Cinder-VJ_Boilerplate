#include "VJ_Boilerplate.h"

void VJ_Boilerplate::prepareSettings( Settings *settings ){
    //Retina Screens
	//settings->enableHighDensityDisplay();
}

void VJ_Boilerplate::setup(){
    getWindow()->setUserData( new WindowData );
    //setFullScreen(true);
    WindowData *data = getWindow()->getUserData<WindowData>();
	data->type = 1;
    setWindowSize(1024, 768);
    getWindow()->setPos(10, 10);
    //getWindow()->setAlwaysOnTop();
    
    vector<DisplayRef> displays = Display::getDisplays();
    
    Window::Format WindowFormat = Window::Format();
    WindowFormat.setDisplay(displays.at(2));
    WindowFormat.setBorderless();
    WindowFormat.setPos(0, 125); //125
    WindowFormat.size( 2048, 768 ); //2048
    app::WindowRef newWindow = createWindow( WindowFormat );
    
	newWindow->setUserData( new WindowData );
    WindowData *data1 = newWindow->getUserData<WindowData>();
	data1->type = 0;
    
    //setFrameRate(10);
    
    gl::Fbo::Format format;
	format.enableMipmapping(false);
    //format.setWrap(GL_CLAMP_TO_BORDER_ARB, GL_CLAMP_TO_BORDER_ARB);
	format.setCoverageSamples(16);
	format.setSamples(4);
    scene = gl::Fbo(app_width, app_height, format);
    
    visuals.push_back(new AudioViz);
    //Add more visuals here:
    
    for(auto visual : visuals){
        visual->setup(app_width, app_height);
        visual->init();
        audio.registerListener(visual);
        midi.registerListener(visual);
    }

    shaders.push_back(new ColorOffset);
    shaders.at(0)->setup(SHADER_VERT_ColorOffset, SHADER_FRAG_ColorOffset);
    //Add more shaders here:
    for(auto shader : shaders){
        audio.registerListener(shader);
        midi.registerListener(shader);
    }
    
    midi.setup();
    audio.setup();
}

void VJ_Boilerplate::update(){
    midi.update();
    audio.update();
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
