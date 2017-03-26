#include <iostream>
#include "header/FacialLandmark.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2){
		cout << "please provide shape_predictor_68_face_landmarks and image as command line input \n" << endl;
		cout << " e.g. program shape_predictor_68_face_landmarks.dat faces/*.jpg \n" << endl;
		return 0;
	}
	featureExtractor landmark(argc, argv);
	landmark.faceShape();
	return 0;
}
