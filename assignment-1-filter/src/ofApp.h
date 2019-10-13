#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    ofVideoGrabber grabber;
//    ofImage processImg;
//    ofPixels pix;
    ofImage grabberPix;

    ofxPanel guiPanel;
    ofParameter<int> delayFrames;
    ofParameter<float> frameRate;
    ofParameter<int> step;
    ofParameter<int> ellipseSize;

    //filter stuff
    
};
