#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
    bool fsMode = true;
	if(fsMode){
        ofSetupOpenGL(&window, 1366, 768, OF_FULLSCREEN);			// <-------- setup the GL context
	}else{
	    ofSetupOpenGL(&window, 800, 600, OF_WINDOW);			// <-------- setup the GL context
	}

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
