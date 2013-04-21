#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //ofSetFrameRate(5);
    colorTypes.push_back(ofColor::red);
    colorTypes.push_back(ofColor::yellow);
    colorTypes.push_back(ofColor::blue);
    //colorTypes.push_back(ofColor::green);
    //colorTypes.push_back(ofColor::white);
    //colorTypes.push_back(ofColor::black);
    resetNeighborhood();
}

//--------------------------------------------------------------
void testApp::update(){
int loop = 0;
    while (loop < 1000){
        int randomRow = rand() % neighborhood.size();
        int randomCol = rand() % neighborhood[randomRow].size();
        //cout << "Row: " << randomRow << endl;
        //cout << "Col: " << randomCol << endl;
        int bestSwitchRow = 0;
        int bestSwitchCol = 0;
        for(int i=-1; i<=1; i++){
            for(int j=-1; j<=1; j++){
                //cout << "i: " << i << " j: " << j << endl;
                if(utility(randomRow, randomCol, bestSwitchRow, bestSwitchCol) < utility(randomRow, randomCol, i, j)){
                    //cout << "In if statement" << endl;
                    bestSwitchRow = i;
                    bestSwitchCol = j;
                }
                //cout << "Through if statement" << endl;
            }
        }
        if(bestSwitchRow == 0 && bestSwitchCol == 0){
            int randomRowDirection = (rand() % 3)-1;
            int randomColDirection = (rand() % 3)-1;
            switchType(randomRow, randomCol, randomRowDirection, randomColDirection);
        }else{
            switchType(randomRow, randomCol, bestSwitchRow, bestSwitchCol);
        }
        //cout << "Switched!" << endl;
        loop++;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    for(int i=0; i<neighborhood.size(); i++){
        for(int j=0; j<neighborhood[i].size(); j++){
            ofSetColor(colorTypes[neighborhood[i][j]]);
            ofRect(j*blockWidth,i*blockHeight,blockWidth,blockHeight);
        }
    }
}

void testApp::resetNeighborhood(){
    neighborhoodHeight = max(4,(ofGetWindowHeight()/blockHeight));
    neighborhoodWidth = max(4,(ofGetWindowWidth()/blockWidth));

    neighborhood.resize(neighborhoodHeight, vector<int>(neighborhoodWidth, 0));
    for(int i=0; i<neighborhood.size(); i++){
        for(int j=0; j<neighborhood[i].size(); j++){
            neighborhood[i][j] = (rand() % colorTypes.size());
        }
    }
}

int testApp::getType(int row, int col, int relativeRow, int relativeCol){
    return neighborhood[clampRow(row+relativeRow,col+relativeCol)][clampCol(row+relativeRow,col+relativeCol)];
}

int testApp::clampRow(int row, int col){
    int finalRow = row;
    while(finalRow<0){
        finalRow += neighborhood.size();
    }
    while(finalRow>(neighborhood.size()-1)){
        finalRow -= neighborhood.size();
    }
    return finalRow;
}

int testApp::clampCol(int row, int col){
    int finalCol = col;
    while(finalCol<0){
        finalCol += neighborhood[clampRow(row, col)].size();
    }
    while(finalCol>(neighborhood[clampRow(row, col)].size()-1)){
        finalCol -= neighborhood[clampRow(row, col)].size();
    }
    return finalCol;
}

float testApp::contentment(int row, int col, int compareRow, int compareCol){
    int myType = getType(row, col, 0, 0);
    //cout << "Running contentment on " << row << ", " << col << ", " << compareRow << ", " << compareCol << endl;
    float contentment = 0;
    int searchDistance = 2;
    int switchRow = clampRow(row+compareRow, col+compareCol);
    int switchCol = clampCol(row+compareRow, col+compareCol);
    //cout << "Starting for loop" << endl;
    for(int i=-searchDistance; i<=searchDistance; i++){
        for(int j=-searchDistance; j<=searchDistance; j++){
            if(i != 0 && j != 0){
                if(myType == getType(switchRow, switchCol, i, j)){
                    //float distance = abs(i) + abs(j);
                    float distance = sqrt(pow(i, 2) + pow(j, 2));
                    float weight = pow(distance, -0.5);
                    //cout << "Weight " << weight << endl;
                    contentment += weight;
                    //cout << contentment << endl;
                }
            }
        }
    }
    //cout << "Contentment of " << row << ", " << col << ", " << compareRow << ", " << compareCol << " is " << contentment << endl;
    return contentment;
}

float testApp::utility(int row, int col, int compareRow, int compareCol){
    float goThere = contentment(row, col, compareRow, compareCol) - contentment(row, col, 0, 0);
    float comeHere = contentment(clampRow(row+compareRow, col+compareCol), clampCol(row+compareRow, col+compareCol), -compareRow, -compareCol) - contentment(clampRow(row+compareRow, col+compareCol), clampCol(row+compareRow, col+compareCol), 0, 0);
    //cout << "goThere: " << goThere << " comeHere: " << comeHere << endl;
    float utility = goThere + comeHere;
    return utility;
}

void testApp::switchType(int row, int col, int switchRow, int switchCol){
    int originalType = getType(row, col, 0, 0);
    neighborhood[row][col] = neighborhood[clampRow(row+switchRow, col+switchCol)][clampCol(row+switchRow, col+switchCol)];
    neighborhood[clampRow(row+switchRow, col+switchCol)][clampCol(row+switchRow, col+switchCol)] = originalType;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == ' '){
        resetNeighborhood();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
