#include "ofApp.h"


string pointsFilePath;

//--------------------------------------------------------------
// Setup method: Initializes the application
void ofApp::setup()
{	
	ofHideCursor(); // Hide the cursor on the screen

    shutdownCounter = 0;
    b_Draw = true;

    // Reading video name from a file and constructing its path
    string videoFile = ofToDataPath("video", true);
    string videoName;
    ifstream vidfile(videoFile);
    if (vidfile.is_open()) {
        getline(vidfile, videoName);        
        vidfile.close();
    }
    string videoPath = ofToDataPath(videoName, true);
    
    // Setting up the video player settings
    ofxOMXPlayerSettings settings;
    settings.videoPath = videoPath;
    settings.useHDMIForAudio = true;
    settings.enableTexture = true;
    settings.enableLooping = true;
    settings.enableAudio = true;

    // Setting up the video player with the configured settings
    omxPlayer.setup(settings);

    // Initializing corner points for drawing
    p[0].x = 0; p[0].y = 0;
    p[1].x = ofGetWidth(); p[1].y = 0;
    p[2].x = ofGetWidth(); p[2].y = ofGetHeight();
    p[3].x = 0; p[3].y = ofGetHeight();
    
    ofBackground(0); // Setting the background color

    // Reading and parsing the points file
    pointsFilePath = ofToDataPath("points", true);
    ifstream myfile(pointsFilePath);
    if (myfile.is_open()) {
        string line;
        getline(myfile, line);
        parsePointsFile(line);
        myfile.close();
    }
}


//--------------------------------------------------------------
// Update method: Called before drawing each frame
void ofApp::update()
{
}

//--------------------------------------------------------------
// Draw method: Renders each frame
void ofApp::draw(){
 	if (b_Draw) {
        if (!omxPlayer.isTextureEnabled()) {
            return;
        }
        // Drawing the texture with the specified points
        tex = omxPlayer.getTextureReference();
        tex.draw(p[0], p[1], p[2], p[3]);
    }
}

//--------------------------------------------------------------
// Handles key press events
void ofApp::keyPressed(int key){
	switch(key) {
        case '1': ind = 0; break;
        case '2': ind = 1; break;
        case '3': ind = 2; break;
        case '4': ind = 3; break;
        case OF_KEY_LEFT: p[ind].x -= 2; break;
        case OF_KEY_RIGHT: p[ind].x += 2; break;
        case OF_KEY_UP: p[ind].y -= 2; break;
        case OF_KEY_DOWN: p[ind].y += 2; break;
        case 's': savePointsToFile(); break;
        case 'p': toggleVideoPause(); break;
        case 'r': resetPoints(); break;
        case 'd': toggleDraw(); break;
        case 'q': initiateShutdown(); break;
    }
}

//--------------------------------------------------------------
// Handles key release events
void ofApp::keyReleased(int key) {
    if (key == 'q') {
        shutdownCounter = 0;
    }
}

//--------------------------------------------------------------
// Exit event: called when the application close
void ofApp::exit() {
    closeVideo();
}

//--------------------------------------------------------------
// Parses the points file and updates the points array
void ofApp::parsePointsFile(const string& line) {
    size_t pos = 0;
    size_t idx = 0;
    string token;
    string delimiter = ",";
    string s = line;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        p[idx].x = stoi(token); 
        s.erase(0, pos + delimiter.length());
        
        pos = s.find(delimiter);
        token = s.substr(0, pos);
        p[idx].y = stoi(token);
        s.erase(0, pos + delimiter.length());
        idx++;
    }
}

//--------------------------------------------------------------
// Saves the current points to the file
void ofApp::savePointsToFile() {
    ofstream myfile;
    myfile.open(pointsFilePath);
    myfile << ofToString(p[0].x) + "," + ofToString(p[0].y) + "," + 
              ofToString(p[1].x) + "," + ofToString(p[1].y) + "," +
              ofToString(p[2].x) + "," + ofToString(p[2].y) + "," +
              ofToString(p[3].x) + "," + ofToString(p[3].y);
    myfile.close();
}

//--------------------------------------------------------------
// Toggles video pause
void ofApp::toggleVideoPause() {
    omxPlayer.setPaused(!omxPlayer.isPaused());
}

//--------------------------------------------------------------
// Close video playback if it's open
void ofApp::closeVideo() {
    if (omxPlayer.getIsOpen()) {
        omxPlayer.close();
    }
}
//--------------------------------------------------------------
// Resets the points to their default positions
void ofApp::resetPoints() {
    p[0].x = 0; p[0].y = 0;
    p[1].x = ofGetWidth(); p[1].y = 0;
    p[2].x = ofGetWidth(); p[2].y = ofGetHeight();
    p[3].x = 0; p[3].y = ofGetHeight();
    savePointsToFile(); // Save the reset points
}

//--------------------------------------------------------------
// Toggles the draw state
void ofApp::toggleDraw() {
    b_Draw = !b_Draw;
}

//--------------------------------------------------------------
// Initiates system shutdown
void ofApp::initiateShutdown() {
    shutdownCounter++;
    if (shutdownCounter == 60) {
        // Close video
	    closeVideo();

        // Optional: Add a delay if needed to ensure all resources are released
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Execute system shutdown command
        string cmd = "shutdown now";
        ofSystem(cmd.c_str());
    }
}