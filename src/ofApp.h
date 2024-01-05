#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void exit();

		// Additional methods for handling specific tasks
		void parsePointsFile(const string& line);
		void savePointsToFile();
		void toggleVideoPause();
		void resetPoints();
		void toggleDraw();
		void closeVideo();
		void initiateShutdown();

		// Member variables
		ofxOMXPlayer omxPlayer;		
		ofTexture tex;
private:
		ofPoint p[4];  // Array of points for drawing
		int ind = 0;   // Index variable
		int shutdownCounter;		
		bool b_Draw;   // Boolean to control drawing
};

