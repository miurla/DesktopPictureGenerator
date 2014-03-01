#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
    
        void drawImage();
        void saveImage();
        void refreshDock();
    
        int screenWidth;
        int screenHeight;
        int lineWidth;
        int lineLength;
        int scale;
    
        ofFbo fbo;
};
