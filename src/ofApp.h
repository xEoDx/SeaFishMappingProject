#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFreeMask.h"
#include "ofDraggableMask.h"

class ofApp : public ofBaseApp
{
public:
    ofApp();
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    void drawBlendRectangle(float initialPosition, float finalPosition,
                            float initialAlpha, float finalAlpha);
    
private:
    ofVideoPlayer video1, video2;
    
    ofDraggableMask mDraggableMask;
    ofxPanel gui;
    
    int numMappers;
    ofxFreeMapping mScreens[2];
    bool mShowConfiguration;
    bool bCommandPressed;
    
    ofxFreeMask mMask1, mMask2, mMask3, mMask4;
};
