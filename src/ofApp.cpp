#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
  ofSetWindowTitle("Noise 1D Example");
  ofBackground(215, 215, 215);
  ofSetVerticalSync(true);
  ofSetCircleResolution(256);

  setupSignedNoiseDemo();
}

//--------------------------------------------------------------
void ofApp::setupSignedNoiseDemo()
{
  // Setup and allocate resources used in the signed noise demo.

  nSignedNoiseData = 400; // we'll store a history of 400 numbers
  signedNoiseData = new float[nSignedNoiseData];
  for (int i = 0; i < nSignedNoiseData; i++) {
    signedNoiseData[i] = 0;
  }

  // Some coordinates...
  radialNoiseDemoY = 200;
  radialNoiseDemoR = 100;
  radialNoiseDemoX = ofGetWidth() / 2 - radialNoiseDemoR;

  radialNoiseCursor = 0.0;
}

//--------------------------------------------------------------
void ofApp::update()
{
  // Shift all of the old data forward through the array
  for (int i = (nSignedNoiseData - 1); i > 0; i--) {
    signedNoiseData[i] = signedNoiseData[i - 1];
  }

  // Compute the latest data, and insert it at the head of the array.
  // Here is where ofSignedNoise is requested.
  float noiseStep    = 1.0f;
  float noiseAmount  = 1.0f;

  signedNoiseData[0] = noiseAmount * ofSignedNoise( radialNoiseCursor );
  radialNoiseCursor += noiseStep;
}

//--------------------------------------------------------------
void ofApp::draw()
{
  ofBackgroundGradient(ofColor(255), ofColor(180), OF_GRADIENT_CIRCULAR);

  // Draw the stored noise history as a straightforward timeline.
  ofPushMatrix();

  float drawWiggleWidth = radialNoiseDemoR * TWO_PI;
  ofTranslate (radialNoiseDemoX + radialNoiseDemoR - drawWiggleWidth, radialNoiseDemoY - radialNoiseDemoR, 0);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofNoFill();

  // draw a "baseline"
  ofSetColor(0, 0, 0, 64);
  ofDrawLine(0, 0, drawWiggleWidth, 0);

  // draw a wiggly line
  ofSetColor(255, 0, 0, 192);
  ofPolyline wigglyPolyLine;
  for (int i = 0; i < nSignedNoiseData; i++) {

    // From the 'i' iterator, use ofMap to compute both
    // an angle (around a circle) and an alpha value.
    float px = ofMap(i, 0, nSignedNoiseData - 1, drawWiggleWidth, 0);
    float py = 0 - radialNoiseDemoR * signedNoiseData[i];
    wigglyPolyLine.addVertex({px, py, 0}  );
  }

  // draw the line
  wigglyPolyLine.draw();
  ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
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
