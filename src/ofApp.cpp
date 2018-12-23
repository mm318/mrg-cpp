#include "ofApp.h"

static constexpr int NUM_DATA_POINTS = 801;
static constexpr int MID_DATA_POINT = NUM_DATA_POINTS / 2;

static constexpr MRG_REAL VREST_DEVIATION = 30;


ofApp::ofApp(MRG & neuron_model)
  : ofBaseApp(),
    m_neuron_model(neuron_model),
    m_data(neuron_model.get_num_nodes())
{
  int i = 0;

  for (; i <= MID_DATA_POINT; ++i) {
    for (auto iter = m_data.begin(); iter != m_data.end(); ++iter) {
      iter->push_back(get_vrest());
    }
  }

  for (; i < NUM_DATA_POINTS; ++i) {
    RingBuffer<MRG_MATRIX_REAL>::pointer data = m_neuron_model.get_next_data();

    int j = 0;
    for (auto iter = m_data.begin(); iter != m_data.end(); ++iter, ++j) {
      iter->push_back(data->at(j, 0));
    }
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
  // Compute and get the latest data
  RingBuffer<MRG_MATRIX_REAL>::pointer data = m_neuron_model.try_get_next_data();
  if (data == nullptr) {
    return;
  }

  // insert the latest data at the head of the array.
  int i = 0;
  for (auto iter = m_data.begin(); iter != m_data.end(); ++iter, ++i) {
    iter->push_back(data->at(i, 0));
    iter->pop_front();
  }

  // debug
  // printf("v_rest: %f, m_data[%lu]: %f\n", get_vrest(), m_data.size() / 2, m_data[m_data.size() / 2].back());
}

//--------------------------------------------------------------
void ofApp::draw()
{
  int width = ofGetWindowWidth();
  int height = ofGetWindowHeight();

  ofBackgroundGradient(ofColor(40), ofColor(0), OF_GRADIENT_CIRCULAR);
  ofEnableAlphaBlending();
  ofEnableSmoothing();
  ofFill();

  // draw a "baseline"
  // ofSetColor(255, 255, 255, 64);
  // ofDrawLine(width, 0, 0, height);

  ofSetLineWidth(2.0f);
  ofPolyline wigglyPolyLine;

  const float section_height = static_cast<float>(height) / static_cast<float>(m_data.size());
  float y = section_height / 2.0f;
  for (auto node_iter = m_data.begin(); node_iter != m_data.end(); ++node_iter) {
    ofPushMatrix();
    ofTranslate(0, y, 0);

    // set the wiggly line
    int i = 0;
    auto points_iter = node_iter->begin();

    for (; i < MID_DATA_POINT; ++i, ++points_iter) {
      // From the 'i' iterator, use ofMap to compute the x location of data point
      float px = ofMap(i, 0, NUM_DATA_POINTS - 1, 0, width);
      float py = -ofMap(*points_iter, get_vrest() - VREST_DEVIATION, get_vrest() + VREST_DEVIATION,
                        -section_height / 2.0f, section_height / 2.0f);
      wigglyPolyLine.addVertex(px, py, 0.0f);
    }
    ofSetColor(255, 0, 0, 100);
    wigglyPolyLine.draw();  // draw the line
    wigglyPolyLine.clear();

    float point_x = ofMap(i, 0, NUM_DATA_POINTS - 1, 0, width);
    float point_y = -ofMap(*points_iter, get_vrest() - VREST_DEVIATION, get_vrest() + VREST_DEVIATION,
                           -section_height / 2.0f, section_height / 2.0f);
    ++i, ++points_iter;

    for (; i < NUM_DATA_POINTS; ++i, ++points_iter) {
      // From the 'i' iterator, use ofMap to compute the x location of data point
      float px = ofMap(i, 0, NUM_DATA_POINTS - 1, 0, width);
      float py = -ofMap(*points_iter, get_vrest() - VREST_DEVIATION, get_vrest() + VREST_DEVIATION,
                        -section_height / 2.0f, section_height / 2.0f);
      wigglyPolyLine.addVertex(px, py, 0.0f);
    }
    ofSetColor(64, 64, 64, 100);
    wigglyPolyLine.draw();  // draw the line
    wigglyPolyLine.clear();

    ofSetColor(215, 215, 215);
    // ofDrawCircle(point_x, point_y, 3.0f);
    ofDrawRectangle(point_x - 2.0f, point_y - 2.0f, 4.0f, 4.0f);

    ofPopMatrix();
    y += section_height;
  }
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
