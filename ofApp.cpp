#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();
	ofSetLineWidth(2);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	int start_index = this->face.getNumVertices();
	for (float x = 128; x < 255; x += 1) {

		float next_x = x + 1;
		int index = this->face.getNumVertices();

		float angle_x = ofMap(ofNoise(noise_seed.x, x * 0.0035 + ofGetFrameNum() * 0.01), 0, 1, PI * -2, PI * 2);
		auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));

		float angle_y = ofMap(ofNoise(noise_seed.y, x * 0.0035 + ofGetFrameNum() * 0.01), 0, 1, PI * -2, PI * 2);
		auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

		float next_angle_x = ofMap(ofNoise(noise_seed.x, next_x * 0.0035 + ofGetFrameNum() * 0.01), 0, 1, PI * -2, PI * 2);
		auto next_rotation_x = glm::rotate(glm::mat4(), next_angle_x, glm::vec3(1, 0, 0));

		float next_angle_y = ofMap(ofNoise(noise_seed.y, next_x * 0.0035 + ofGetFrameNum() * 0.01), 0, 1, PI * -2, PI * 2);
		auto next_rotation_y = glm::rotate(glm::mat4(), next_angle_y, glm::vec3(0, 1, 0));

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec4(x, 10, 0, 0) * rotation_y * rotation_x);
		vertices.push_back(glm::vec4(next_x, 10, 0, 0)* next_rotation_y* next_rotation_x);
		vertices.push_back(glm::vec4(next_x, -10, 0, 0) * next_rotation_y * next_rotation_x);
		vertices.push_back(glm::vec4(x, -10, 0, 0) * rotation_y * rotation_x);

		this->face.addVertices(vertices);
		this->line.addVertices(vertices);

		auto color = ofColor();
		auto next_color = ofColor();

		color.setHsb(ofMap((int)(x + ofGetFrameNum() * 1) % 128, 1, 128, 0, 255), 180, 255);
		next_color.setHsb(ofMap((int)(next_x + ofGetFrameNum() * 1) % 128, 1, 128, 0, 255), 180, 255);

		this->face.addColor(color);
		this->face.addColor(next_color);
		this->face.addColor(next_color);
		this->face.addColor(color);

		this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
		this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

		this->line.addIndex(index + 0); this->line.addIndex(index + 1);
		this->line.addIndex(index + 2); this->line.addIndex(index + 3);
	}

	this->line.addIndex(start_index + 0); this->line.addIndex(start_index + 3);
	this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(270);

	for (int i = 0; i < 8; i++) {

		ofRotateX(45);

		this->line.drawWireframe();
		this->face.draw();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}