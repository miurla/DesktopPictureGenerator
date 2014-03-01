#include "testApp.h"

#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define MENUBAR_HEIGHT  22
#define REFRESH_FRAME 30
// #define RETINA_DISPLAY

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    
    #ifdef RETINA_DISPLAY
        scale = 2;
        lineWidth = 2;
        lineLength = 6;
    #else
        scale = 1;
        lineWidth = 1;
        lineLength = 5;
    #endif
    
    screenWidth = ofGetScreenWidth();
    screenHeight = ofGetScreenHeight();
    
    fbo.allocate(screenWidth*scale, screenHeight*scale, GL_RGBA);
    
    drawImage();
    saveImage();
}

//--------------------------------------------------------------
void testApp::update(){
    if(ofGetFrameNum() == REFRESH_FRAME) {
        refreshDock();
        ofExit();
    }
}

void testApp::drawImage(){
    fbo.begin();
    ofBackground(0);
    ofColor keyColor;
    keyColor.set(ofRandom(50,255),ofRandom(50,255),ofRandom(50,255));
    ofPushMatrix();
    ofTranslate(0, MENUBAR_HEIGHT*scale);
    ofScale(scale, scale);
    ofSetLineWidth(lineWidth);
    for(int i=0; i< floor(screenWidth/GRID_WIDTH)+1 ; i++) {
        for(int j=0; j< floor(screenHeight/GRID_HEIGHT)+1 ; j++) {
            if(i%5 == 0 || j%5 == 0) {
                ofSetColor(keyColor);
            } else {
                ofSetColor(255);
            }
            ofPushMatrix();
            ofTranslate(-3, 0);
            ofLine(i*GRID_WIDTH, j*GRID_HEIGHT, i*GRID_WIDTH+lineLength, j*GRID_HEIGHT);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate(0, -3);
            ofLine(i*GRID_WIDTH, j*GRID_HEIGHT, i*GRID_WIDTH, j*GRID_HEIGHT+lineLength);
            ofPopMatrix();
        }
    }
    ofPopMatrix();
    fbo.end();
}

void testApp::saveImage() {
    ofPixels pix;
    fbo.readToPixels(pix);
    ofSaveImage(pix, "picture.png");
}

// [reference] using shell script to launch external apps from OF by julapy
// http://forum.openframeworks.cc/t/using-shell-script-to-launch-external-apps-from-of/3853
void testApp :: refreshDock ()
{
	string shPath;
	shPath = ofToDataPath( "refresh.sh", true );
	
	char *shPathChar;
	shPathChar = new char[ shPath.length() + 1 ];
	
	strcpy( shPathChar, shPath.c_str() );
	
	//--
	int pid = fork();
	cout << "pid :: " << pid << endl;
	switch ( pid )
	{
		case -1 :
			cout << "Uh-Oh! fork() failed.\n" << endl;
		case  0 :
			execl( shPathChar, shPathChar, NULL );
		default :
			return;
	}
}