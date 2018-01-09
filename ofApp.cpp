#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(255);
	ofSetWindowTitle("Insta");

	//ofNoFill();
	ofSetColor(0);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 300, true, true);
	this->word = "ƒ";
	this->word_paths = this->font.getStringAsPoints(this->word);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	for (int w_index = 0; w_index < this->word.size(); w_index += 2) { // “ú–{Œê‚È‚Ì‚Å2ByteHH
		vector<ofPolyline> outline = word_paths[w_index].getOutline();
		ofVec3f center = outline[0].getCentroid2D();

		for (int o_index = 0; o_index < outline.size(); o_index++) {
			outline[o_index] = outline[o_index].getResampledBySpacing(3);
			vector<ofPoint> vertices = outline[o_index].getVertices();

			for (int v_index = 0; v_index < vertices.size() - 1; v_index++) {
				ofVec3f point_1 = vertices[v_index] - center;
				ofVec3f point_2 = vertices[v_index + 1] - center;
				
				float noise_value_1 = ofNoise(v_index * 0.01 + ofGetFrameNum() * 0.01);
				float noise_value_2 = ofNoise((v_index + 1) * 0.01 + ofGetFrameNum() * 0.01);

				if (noise_value_1 < 0.5) {
					noise_value_1 = 0.5;
				}
				if (noise_value_2 < 0.5) {
					noise_value_2 = 0.5;
				}

				noise_value_1 -= 0.5;
				noise_value_2 -= 0.5;

				ofBeginShape();
				ofVertex(point_1);
				ofVertex(point_2);
				ofVertex(point_2 + ofVec3f(0, 0, -300 * noise_value_2 + 1));
				ofVertex(point_1 + ofVec3f(0, 0, -300 * noise_value_1 + 1));
				ofEndShape(true);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
