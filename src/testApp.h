#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:
        std::vector< std::vector<int> > neighborhood;
        std::vector<ofColor> colorTypes;
        int neighborhoodWidth = 4;
        int neighborhoodHeight = 4;
        int blockWidth = 10;
        int blockHeight = 10;

        int getType(int row, int col, int relativeRow, int relativeCol);
        float contentment(int row, int col, int compareRow, int compareCol);
        int clampRow(int row, int col);
        int clampCol(int row, int col);
        void switchType(int row, int col, int relativeRow, int relativeCol);
        void resetNeighborhood();
};
