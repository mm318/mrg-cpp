#include "ofApp.h"

static constexpr int NUM_DATA_POINTS = 801;
static constexpr int MID_DATA_POINT = NUM_DATA_POINTS / 2;


ofApp::ofApp(MRG & neuron_model) : ofBaseApp(), m_neuron_model(neuron_model)
{
  for (int i = 0; i < NUM_DATA_POINTS; ++i) {
    RingBuffer<MRG_MATRIX_REAL>::pointer data = m_neuron_model.get_next_data();
    m_data.push_back(data->at(0, 0));
  }
}

//--------------------------------------------------------------
void ofApp::setup()
{
  ofSetWindowTitle("Axon Node Voltages");
  ofBackground(40, 40, 40);
  ofSetVerticalSync(true);
  ofSetCircleResolution(256);
}

//--------------------------------------------------------------
void ofApp::update()
{
  RingBuffer<MRG_MATRIX_REAL>::pointer data = m_neuron_model.try_get_next_data();
  if (data == nullptr) {
    return;
  }

  // Compute the latest data, and insert it at the head of the array.
  m_data.push_back(data->at(0, 0));
  m_data.pop_front();

  // debug
  // printf("m_data[0]: %f\n", m_data.back());
}

//--------------------------------------------------------------
void ofApp::draw()
{
  int width = ofGetWindowWidth();
  int height = ofGetWindowHeight();

  ofBackgroundGradient(ofColor(40), ofColor(0), OF_GRADIENT_CIRCULAR);

  // Draw the stored noise history as a straightforward timeline.
  ofPushMatrix();

  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofFill();

  // draw a "baseline"
  // ofSetColor(255, 255, 255, 64);
  // ofDrawLine(width, 0, 0, height);

  ofSetLineWidth(2.0f);
  ofTranslate(0, height / 2, 0);
  ofPolyline wigglyPolyLine;

  // set the wiggly line
  int i = 0;
  auto iter = m_data.begin();

  for (; i < MID_DATA_POINT; ++i, ++iter) {
    // From the 'i' iterator, use ofMap to compute the x location of data point
    float px = ofMap(i, 0, NUM_DATA_POINTS - 1, 0, width);
    float py = -(*iter);
    wigglyPolyLine.addVertex(px, py, 0.0f);
  }
  ofSetColor(255, 0, 0, 100);
  wigglyPolyLine.draw();  // draw the line

  float point_x = ofMap(i, 0, NUM_DATA_POINTS - 1, 0, width);
  float point_y = -(*iter);
  ++i, ++iter;

  wigglyPolyLine.clear();
  for (; i < NUM_DATA_POINTS; ++i, ++iter) {
    // From the 'i' iterator, use ofMap to compute the x location of data point
    float px = ofMap(i, 0, NUM_DATA_POINTS - 1, 0, width);
    float py = -(*iter);
    wigglyPolyLine.addVertex(px, py, 0.0f);
  }
  ofSetColor(64, 64, 64, 100);
  wigglyPolyLine.draw();  // draw the line

  ofSetColor(215, 215, 215);
  // ofDrawCircle(point_x, point_y, 3.0f);
  ofDrawRectangle(point_x - 3.0f, point_y - 3.0f, 6.0f, 6.0f);

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
