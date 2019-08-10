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
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
private:
    ofVideoPlayer video1, video2;
    ofxFreeMapping mScreens[2];
    ofDraggableMask mFirstCurtain, mSecondCurtain, mThirdCurtain, mFourthCurtain;
    
    int mScreenMappersCount;    
    bool mShowConfiguration;
};
