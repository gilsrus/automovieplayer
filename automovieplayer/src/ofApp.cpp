#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0,0,0);
    ofSetVerticalSync(true);
    gui.setup();
    
    image.load("tp.png");
    
    
    settings.loadFile("settings.xml");
    repeat = settings.getValue("settings:repeat", 1);
    shuffle = settings.getValue("settings:shuffle", 0);
    pjimage = settings.getValue("settings:pjimage",0);
    resMode = settings.getValue("settings:resmode",0);
    drawMode = settings.getValue("settings:drawMode",0);
    drawvMode = settings.getValue("settings:drawvMode",0);
    show_gui = settings.getValue("settings:showgui",1);
    moviePath = settings.getValue("settings:moviepath","0");
    res[0] = settings.getValue("settings:resx", 0);
    res[1] = settings.getValue("settings:resy", 0);

    if(!show_gui){
        ofHideCursor();
    }
    video.load(moviePath);
    video.play();
   
    lastTap = 1000;
    ofAddListener(doubleClickEvent, this, &ofApp::mouseDoubleClicked);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    video.update();
    currentframes = video.getCurrentFrame();
    if(currentframes < 0){
        currentframes = video.getTotalNumFrames();
    }
    
    switch(drawMode){
     
        case 0:
            posx = 0;
            break;
        case 1:
            if(resMode ==0){
                posx = (ofGetScreenWidth()/2) - video.getWidth() /2;
            }
            else{
            posx = (ofGetScreenWidth()/2) - res[0] /2;
            }
            break;
        case 2:
            if(resMode ==0){
                posx = ofGetScreenWidth() - video.getWidth();
            }
            else{
            posx = ofGetScreenWidth() - res[0];
            }
            break;
    }
    
    switch(drawvMode){
            
        case 0:
            posy = 0;
            break;
        case 1:
            if(resMode ==0){
                posy = (ofGetScreenHeight()/2) - video.getHeight() /2;
            }
            else{
            posy = (ofGetScreenHeight()/2) - (res[1] /2);
            }
            break;
        case 2:
            if(resMode ==0){
                posy= ofGetScreenHeight() - video.getHeight();
            }
            else{
            posy= ofGetScreenHeight() - res[1];
            }
            break;
    }

    
        if(repeat){
            video.setLoopState(OF_LOOP_NORMAL);
        }
        else{
             video.setLoopState(OF_LOOP_NONE);
             }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    switch(resMode){
        case 0:
            video.draw(posx,posy);
            break;
        case 1:
            video.draw(0,0,ofGetScreenWidth(),ofGetScreenHeight());
            break;
        case 2:
            video.draw(posx, posy, res[0], res[1]);
            break;
        
    }
    if(pjimage){
        if(ofGetScreenHeight() < 1080){
            image.draw((ofGetScreenWidth()/2) - 640,(ofGetScreenHeight()/2) - 360, 1280, 720);
        }
        else{
        image.draw((ofGetScreenWidth()/2) - (image.getWidth() /2),(ofGetScreenHeight()/2) - (image.getHeight() /2));
        }
        
    }
    imGui();
}

void ofApp::exit(){
    
    settings.setValue("settings:repeat", repeat);
    settings.setValue("settings:shuffle", shuffle);
    settings.setValue("settings:pjimage", pjimage);
    settings.setValue("settings:resmode", resMode);
    settings.setValue("settings:drawMode", drawMode);
    settings.setValue("settings:drawvMode", drawvMode);
    settings.setValue("settings:showgui", show_gui);
    settings.setValue("settings:moviepath", moviePath);
    settings.setValue("settings:resx", res[0]);
    settings.setValue("settings:resy", res[1]);

    settings.saveFile("settings.xml");
    
}

bool ofApp::imGui()
{
    
   auto mainSettings = ofxImGui::Settings();
    if(show_gui){
    gui.begin();
    if(ofxImGui::BeginWindow("automovieplayer for IDD exhibition ver 0.1",mainSettings, false))
    {
        
        if(ofxImGui::BeginTree("frame", mainSettings)){
        ImGui::Text("frame %.1d / %.1d ", currentframes,video.getTotalNumFrames());
           
        ImGui::DragInt("", &jumpframe, 1, 0,  video.getTotalNumFrames());
        ImGui::SameLine(); if(ImGui::Button("Frame Jump")){
            video.setSpeed(0);
            video.setFrame(jumpframe);
            video.setSpeed(1);

            
        }
            ofxImGui::EndTree(mainSettings);
        }
       
        ImGui::Spacing();
        if(ofxImGui::BeginTree("player", mainSettings)){
        if (ImGui::Button("Load Movie..."))
        {
            auto dialogResult = ofSystemLoadDialog("Load Movie", false, ofToDataPath(""));
            if (dialogResult.bSuccess)
            {
                moviePath = dialogResult.getPath();
                video.load(moviePath);
                video.play();
            }
            
        }
            ImGui::Spacing();
            if(ImGui::Button("Play")){
                if(!video.isPlaying()){
                    video.play();
                }
            }
            ImGui::SameLine();
            if(ImGui::Button("Pause")){
                video.setPaused(true);        }
            ImGui::SameLine();
            if(ImGui::Button("Stop")){
                video.stop();
                
            }
            ofxImGui::EndTree(mainSettings);
        }
      
            ImGui::Spacing();
        
        if(ofxImGui::BeginTree("setting", mainSettings)){
        //ofxImGui::AddParameter(shuffle);
        ofxImGui::AddParameter(repeat);
        ofxImGui::AddParameter(pjimage);
            ImGui::Spacing();

         static const vector<string> reslabels = { "Original", "Fullscreen", "Fixed" };
        ImGui::Text("User Resolution");
        ImGui::DragInt2("", res,1,0,ofGetScreenWidth());
            
            ImGui::Text(" Original Resolution is %.0f x %.0f",video.getWidth(),video.getHeight());
            ImGui::Text(" Original Aspect Ratio is %.0f : %.0f", (video.getWidth() / gcd(video.getWidth(),video.getHeight())),(video.getHeight() / gcd(video.getWidth(),video.getHeight()))) ;
            ImGui::Text(" User Res Aspect Ratio is %.0f : %.0f", res[0] / gcd(res[0],res[1]), res[1] / gcd(res[0],res[1])) ;
            
            if(ImGui::Button("Set Height with Original Aspect Ratio")){
                res[1] = ((video.getHeight() / gcd(video.getWidth(),video.getHeight())) * res[0]) / (video.getWidth() / gcd(video.getWidth(),video.getHeight()));
                }
            if(ImGui::Button("Set Width  with Original Aspect Ratio")){
               res[0] = ((video.getWidth() / gcd(video.getWidth(),video.getHeight())) * res[1]) / (video.getHeight() / gcd(video.getWidth(),video.getHeight()));
            }
            
            
            ImGui::Spacing();

        ofxImGui::AddRadio(resMode,reslabels,3);
        
            ImGui::Spacing();

        static const vector<string> labels = { "Left", "Center", "Right" };
        static const vector<string> vlabels = { "Up", "Center", "Down" };
       

        ofxImGui::AddRadio(drawMode, labels, 3);
        ofxImGui::AddRadio(drawvMode, vlabels, 3);
        ImGui::Spacing();

        if(ImGui::Button("Hide GUI")){
            show_gui = !show_gui;
            ofHideCursor();
        }
            ofxImGui::EndTree(mainSettings);
        }
        ImGui::Spacing();
        if (ofxImGui::BeginTree("help", mainSettings)) {
            
            ImGui::Text("press key '->' -- 30 frames forward ");
            ImGui::Text("press key '<-' -- 30 frames backward");
            ImGui::Text("press key 'f' -- FullScreen / Windowed Screen ");
            ImGui::Text("press key 'g' -- Show GUI Toggle ");
            ImGui::Text("press mouse 'left button' double click -- Show GUI");
            ofxImGui::EndTree(mainSettings);
            
        }
        
    }
    
    ofxImGui::EndWindow(mainSettings);
    gui.end();
    }
    
}

float ofApp::gcd( float m, float n)
{
    if((0 == m)||(0 == n))
		return 0;
	
	while( m != n )
	{
		if ( m > n ) m = m - n;
		else         n = n - m;
	}
	return m;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_RIGHT){
        video.setSpeed(0);
        video.setFrame(video.getCurrentFrame() + 30);
        video.setSpeed(1);
    }
    if(key == OF_KEY_LEFT){
        video.setSpeed(0);
        video.setFrame(video.getCurrentFrame() - 30);
        video.setSpeed(1);
    }
    
    if(key == 'f'){
        ofToggleFullscreen();
    }
    if(key == 'g'){
        show_gui = !show_gui;
        if(show_gui){
            ofShowCursor();
        }
        else{
            ofHideCursor();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(ofMouseEventArgs& mouse){
    static const unsigned long doubleclickTime = 400;
    unsigned long curTap = ofGetElapsedTimeMillis();
    if (lastTap != 0 && curTap - lastTap < doubleclickTime) {
        ofNotifyEvent(doubleClickEvent, mouse);
        return;
    }
    lastTap = curTap;
}

//--------------------------------------------------------------
void ofApp::mouseDoubleClicked(ofMouseEventArgs& mouse) {
    if(!show_gui){
        show_gui = true;
        ofShowCursor();
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
