#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void mouseReleased(ofMouseEventArgs& mouse);
        void mouseDoubleClicked(ofMouseEventArgs& mouse);
        ofEvent<ofMouseEventArgs&> doubleClickEvent;
        unsigned long lastTap;
    
        float gcd(float m, float n);
    
        enum class drawMode
        {
            Left,
            Center,
            Right
        };
        enum class drawvMode
        {
            Up,
            Center,
            Down
        };
        enum class resMode
        {
        Original,
        Fullscreen,
        Fixed
        };
    
        int posx;
        int posy;
        int res[2];
    
        bool show_gui;
        int currentframes;
        int jumpframe;
    
        bool imGui();

        ofImage image;
        ofVideoPlayer video;
        ofxXmlSettings settings;
    
        ofxImGui::Gui gui;
        ofParameter<string> moviePath{ "File Path", "movie.mp4" };
        ofParameter<bool> repeat{ "Repeat", true };
        ofParameter<bool> shuffle{ "Shuffle", false };
        ofParameter<bool> pjimage{ "Projection Test Pattern Image", false };
    
        ofParameter<int> drawMode{ "Horizon Draw Mode", static_cast<int>(drawMode::Left) };
        ofParameter<int> drawvMode{ "Vertical Draw Mode", static_cast<int>(drawvMode::Up) };
        ofParameter<int> resMode{ "Movie Resolution", static_cast<int>(resMode::Original) };

        ofParameterGroup ui{ "movieplayer", moviePath,repeat,shuffle,pjimage,drawMode,drawvMode,resMode};
    

};
