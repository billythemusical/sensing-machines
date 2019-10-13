#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowShape(640, 480);
    
    //setup the grabber
    grabber.setup(640,480);
    
    //setup the contour finder and parameters
    contourFinder.setUseTargetColor(true);
    
    colorTarget.set("Color Target", ofColor(255, 0, 0));
    colorOffset.set("Color Offset", 10, 0, 255);
    minArea.set("Min Area", 0.01f, 0, 0.5f);
    maxArea.set("Max Area", 0.25f, 0, 0.5f);
    blurAmount.set("Blur Amount", 0, 0, 100);
    debugProcess.set("Debug Processs", false);
    
    //setup the gui
    guiPanel.setup("Color Tracker", "settings.json");
    guiPanel.add(colorTarget);
    guiPanel.add(colorOffset);
    guiPanel.add(minArea);
    guiPanel.add(maxArea);
    guiPanel.add(blurAmount);
    guiPanel.add(debugProcess);

}

void ofApp::update()
{
    
    grabber.update();
    if(grabber.isFrameNew())
    {
        processImg.setFromPixels(grabber.getPixels());

        
        if(blurAmount > 0)
        {
            ofxCv::blur(processImg, blurAmount);
            //ofxCv::GaussianBlur(processImg, blurAmount);
            //ofxCv::medianBlur(processImg, blurAmount);
            processImg.update();
        }
        
        //save the color under the mouse
        colorUnderMouse = processImg.getColor(ofGetMouseX(), ofGetMouseY());
        
        //update parameters
        contourFinder.setTargetColor(colorTarget, ofxCv::TRACK_COLOR_HSV);
        contourFinder.setThreshold(colorOffset);
        contourFinder.setMinAreaNorm(minArea);
        contourFinder.setMaxAreaNorm(maxArea);

        //find contours
        contourFinder.findContours(processImg);
        
    }

}

void ofApp::draw()
{
    ofSetColor(255);
    
    if(debugProcess)
    {
        processImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    else
    {
        //draw the grabber image
        grabber.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    //draw the found contours
    contourFinder.draw();
    
    // Draw the color under the mouse.
    ofPushStyle();
    ofSetColor(colorUnderMouse);
    ofDrawRectangle(ofGetMouseX() - 25, ofGetMouseY() - 25, 50, 50);
    ofNoFill();
    ofSetColor(colorUnderMouse.getInverted());
    ofDrawRectangle(ofGetMouseX() - 25, ofGetMouseY() - 25, 50, 50);
    ofPopStyle();
    
    //draw the gui
    guiPanel.draw();
    
}


void ofApp::mousePressed(int x, int y, int button)
{
    if(!guiPanel.getShape().inside(x, y))
    {
        //track the color under the mouse
        colorTarget = colorUnderMouse;
    }
}
