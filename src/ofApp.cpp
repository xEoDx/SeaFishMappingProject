#include "ofApp.h"

ofApp::ofApp() : mDraggableMask("First mask")
{}

void ofApp::setup()
{
    ofBackground(0);
    video1.load("1.mp4");
    video1.play();
    video2.load("2.mp4");
    video2.play();

    ofSetFullscreen(true);
    mShowConfiguration = true;

    numMappers = 2;
    for (int i = 0; i < numMappers; i++) {
        mScreens[i].initialize(
                                video1.getWidth(),
                                video1.getHeight(),
                                i*100,
                                i*100
                                );
        char buf[256];
        sprintf(buf, "mapper%d.txt", i);
        mScreens[i].load(ofToDataPath(buf));
    }


    mDraggableMask.setup(video1.getWidth(),
                         video1.getHeight(),
                         200,
                         video1.getHeight(),
                         0,0);
    
    mMask2.setup(video1.getWidth(), video1.getHeight());
    mMask3.setup(video1.getWidth(), video1.getHeight());
    mMask4.setup(video1.getWidth(), video1.getHeight());
    
    
    mMask2.newLayer();
    mMask3.newLayer();
    mMask4.newLayer();
}

//--------------------------------------------------------------
void ofApp::update()
{
    video2.update();
    video1.update();

    for (int i = 0; i < numMappers; i++)
    {
        mScreens[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Background mapping
    mScreens[0].startMapping();
    ofSetColor(255,255);
    video2.draw(0,0);
    mScreens[0].stopMapping();
    
    // First front curtain
    mDraggableMask.drawGui(); //needs to be outside screen mapping
    mScreens[1].startMapping();
    mDraggableMask.beginLayer();
    video1.draw(0,0);
    mDraggableMask.endLayer();
    
    mDraggableMask.drawMask();
    
    // Second front curtain
//    mMask2.beginLayer();
//    ofSetColor(255,255);
//    video1.draw(0,0);
//    mMask2.endLayer();
//
//    mMask2.beginMask();
//    ofClear(0,0,0,255);
//    ofSetColor(ofColor::white);
//    ofFill();
//    ofDrawRectangle(400, 0, 200, video1.getHeight());
//
//    //mask blend
//    drawBlendRectangle(400, 420, 255, 0);
//    drawBlendRectangle(580, 600, 0, 255);
//
//    mMask2.endMask();
//    mMask2.draw();
//
//    // Third front curtain
//    mMask3.beginLayer();
//    ofSetColor(255,255);
//    video1.draw(0,0);
//    mMask3.endLayer();
//
//    mMask3.beginMask();
//    ofClear(0,0,0,255);
//    ofSetColor(ofColor::white);
//    ofFill();
//    ofDrawRectangle(800, 0, 200, video1.getHeight());
//
//    //mask blend
//    drawBlendRectangle(800, 820, 255, 0);
//    drawBlendRectangle(980, 1000, 0, 255);
//    mMask3.endMask();
//    mMask3.draw();
//
//    // Fourth front curtain
//    mMask4.beginLayer();
//    ofSetColor(255,255);
//    video1.draw(0,0);
//    mMask4.endLayer();
//
//    mMask4.beginMask();
//    ofClear(0,0,0,255);
//    ofSetColor(ofColor::white);
//    ofFill();
//    ofDrawRectangle(1200, 0, video1.getWidth(), video1.getHeight());
//
//    //mask blend
//    drawBlendRectangle(1200, 1220, 255, 0);
//
//    mMask4.endMask();
//    mMask4.draw();
    mScreens[2].stopMapping();

    if (mShowConfiguration)
    {
        for (int i = 0; i < numMappers; i++)
        {
            mScreens[i].drawBoundingBox();
        }
        //gui.draw();

        ofSetColor(125,125);
        ofFill();
        ofDrawRectangle(20,ofGetHeight()-70, 350,100);
        ofSetColor(255, 255);
        ofDrawBitmapString("COMMAND + F Fullscreen, L Load, S Save", 40, ofGetHeight()-40);
        ofDrawBitmapString("CONTROL Debug Mode", 40, ofGetHeight()-20);
    }
}

void ofApp::drawBlendRectangle(float initialPosition, float finalPosition,
                                float initialAlpha, float finalAlpha)
{
    for(float p = initialPosition; p <= finalPosition; p++)
    {
        float lerpedAlpha = ofLerp(initialAlpha, finalAlpha, (p-initialPosition)/(finalPosition-initialPosition));
        ofEnableAlphaBlending();
        ofSetColor(0, 0, 0, lerpedAlpha);
        ofDrawRectangle(p, 0, 1, video1.getHeight());
        ofDisableAlphaBlending();
    }
}

void ofApp::keyPressed(int key)
{
    cout << "keyPressed " << key << endl;
    
    switch(key){
        case OF_KEY_COMMAND:
            bCommandPressed = true;
            break;
        case 'f':
            if(bCommandPressed)
                ofToggleFullscreen();
            break;

        case 'l':
            if(bCommandPressed)
                for (int i = 0; i < numMappers; i++) {
                    char buf[256];
                    sprintf(buf, "mapper%d.txt", i);
                    mScreens[i].load(ofToDataPath(buf));
                }
            break;



        case's':
            for (int i = 0; i < numMappers; i++)
            {
                char buf[256];
                sprintf(buf, "mapper%d.txt", i);
                mScreens[i].save(ofToDataPath(buf));
            }
            break;

    }


    if (key == OF_KEY_CONTROL)
    {
        mShowConfiguration = !mShowConfiguration;
        mDraggableMask.showConfig(mShowConfiguration);
    }
}

void ofApp::keyReleased(int key)
{
}


void ofApp::mouseMoved(int x, int y )
{
}

void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < numMappers; i++)
    {
        mScreens[i].mouseDragged(x, y);
    }
}


void ofApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < numMappers; i++)
    {
        mScreens[i].mousePressed(x, y);
    }
}


void ofApp::mouseReleased(int x, int y, int button)
{
    for (int i = 0; i < numMappers; i++)
    {
        mScreens[i].mouseReleased(x, y);
    }
}

void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
