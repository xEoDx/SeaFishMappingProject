#include "ofApp.h"

//--------------------------------------------------------------
ofApp::ofApp() :
    mFirstCurtain("First mask"),
    mSecondCurtain("Second mask"),
    mThirdCurtain("Third curtain"),
    mFourthCurtain("Fourth curtain")
{}

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
    video1.load("1.mp4");
    video1.play();
    video2.load("2.mp4");
    video2.play();

    ofSetFullscreen(true);
    mShowConfiguration = true;

    mScreenMappersCount = 2;
    for (int i = 0; i < mScreenMappersCount; i++) {
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


    mFirstCurtain.setup(video1.getWidth(),
                         video1.getHeight(),
                         200,
                         video1.getHeight(),
                         0,0);
    
    mSecondCurtain.setup(video1.getWidth(),
                         video1.getHeight(),
                         200,
                         video1.getHeight(),
                         400,0);
    
    mThirdCurtain.setup(video1.getWidth(),
                        video1.getHeight(),
                        200,
                        video1.getHeight(),
                        800,0);
    
    mFourthCurtain.setup(video1.getWidth(),
                         video1.getHeight(),
                         200,
                         video1.getHeight(),
                         1200,0);
}

//--------------------------------------------------------------
void ofApp::update()
{
    video2.update();
    video1.update();

    for (int i = 0; i < mScreenMappersCount; i++)
    {
        mScreens[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Background mapping
    mScreens[0].startMapping();
    ofSetColor(255, 255);
    video2.draw(0, 0);
    mScreens[0].stopMapping();
    
    // Curtains Gui needs to be drawn
    // before Mapping screens
    mFirstCurtain.drawGui();
    mSecondCurtain.drawGui();
    mThirdCurtain.drawGui();
    mFourthCurtain.drawGui();
    
    mScreens[1].startMapping();
    
    // First front curtain
    mFirstCurtain.beginLayer();
    video1.draw(0, 0);
    mFirstCurtain.endLayer();
    mFirstCurtain.drawMask();
    
    // Second curtain
    mSecondCurtain.beginLayer();
    video1.draw(0, 0);
    mSecondCurtain.endLayer();    
    mSecondCurtain.drawMask();
  
    // Third curtain
    mThirdCurtain.beginLayer();
    video1.draw(0, 0);
    mThirdCurtain.endLayer();
    mThirdCurtain.drawMask();
    
    // Fourth curtain
    mFourthCurtain.beginLayer();
    video1.draw(0, 0);
    mFourthCurtain.endLayer();
    mFourthCurtain.drawMask();
    
    mScreens[2].stopMapping();

    if (mShowConfiguration)
    {
        for (int i = 0; i < mScreenMappersCount; i++)
        {
            mScreens[i].drawBoundingBox();
        }

        ofSetColor(125,125);
        ofFill();
        ofDrawRectangle(20,ofGetHeight()-70, 350,100);
        ofSetColor(255, 255);
        ofDrawBitmapString("COMMAND + F Fullscreen, L Load, S Save", 40, ofGetHeight()-40);
        ofDrawBitmapString("CONTROL Debug Mode", 40, ofGetHeight()-20);
    }
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    cout << "keyPressed " << key << endl;
    
    switch(key)
    {
        case OF_KEY_COMMAND:
            mIsCommandPressed = true;
            break;
        case 'f':
            if (mIsCommandPressed)
                ofToggleFullscreen();
            break;

        case 'l':
            if (mIsCommandPressed)
                for (int i = 0; i < mScreenMappersCount; i++)
                {
                    char buf[256];
                    sprintf(buf, "mapper%d.txt", i);
                    mScreens[i].load(ofToDataPath(buf));
                }
            break;

        case's':
            for (int i = 0; i < mScreenMappersCount; i++)
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
        mFirstCurtain.showConfig(mShowConfiguration);
        mSecondCurtain.showConfig(mShowConfiguration);
        mThirdCurtain.showConfig(mShowConfiguration);
        mFourthCurtain.showConfig(mShowConfiguration);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < mScreenMappersCount; i++)
    {
        mScreens[i].mouseDragged(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < mScreenMappersCount; i++)
    {
        mScreens[i].mousePressed(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    for (int i = 0; i < mScreenMappersCount; i++)
    {
        mScreens[i].mouseReleased(x, y);
    }
}

//--------------------------------------------------------------
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
