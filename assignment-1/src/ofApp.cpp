#include "ofApp.h"


void ofApp::setup()
{
    ofSetWindowShape(640, 480);

    // Setup the grabber.
    grabber.setup(640, 480);

    frameRate.set("Frame Rate: ", ofGetFrameRate());
    delayFrames.set("Delay in Frames", 0, 0, 3000);
    step.set("Step: ", 2, 1, 50);
    ellipseSize.set("Ellipse Size: ", 10, 0, 50);

    // Setup the gui.
    guiPanel.setup("Video Filter", "settings.json");
//    guiPanel.add(frameRate);
//    guiPanel.add(delayFrames);
    guiPanel.add(step);
    guiPanel.add(ellipseSize);

}

void ofApp::update()
{
    grabber.update();
    if (grabber.isFrameNew())
    {
          grabberPix = grabber.getPixels();

    }
}

void ofApp::draw()
{
    ofBackground(0);

//    for(int y = 0; y < grabber.getHeight(); y+=step*2)
    for(int y = 0; y < grabber.getHeight(); y+=step)
    {
//        for(int x = 0; x < grabber.getWidth(); x+=step*2)
        for(int x = 0; x < grabber.getWidth(); x+=step)
        {
            float r = grabberPix.getColor(x + roundf(sqrt(x*y)), y).r;
            float g = grabberPix.getColor(x, y*2).g;
            float b = grabberPix.getColor(x, y).b;
            ofFill();
            ofSetColor(r, g, b);
//            ofDrawEllipse(x - sin(y)*step, y + sin(x)*step, ellipseSize, ellipseSize);
            ofDrawEllipse(x, y, ellipseSize, ellipseSize);
        }
    }

    // Draw the gui.
    guiPanel.draw();
}
