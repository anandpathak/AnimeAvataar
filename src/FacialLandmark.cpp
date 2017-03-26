#include "header/FacialLandmark.h"

using namespace std;
using namespace dlib;

featureExtractor::featureExtractor(int numberOfImage, char **imageList){
	this->numberOfImage=numberOfImage;
	this->imageList=imageList;
}
void featureExtractor::faceShape(){

	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor sp;

  deserialize(this->imageList[1]) >> sp;

    image_window win, win_faces;
    array2d<rgb_pixel> img2;

//    std::vector<full_object_detection> shapes[numberOfImage-2];
    for (int i = 2; i < this->numberOfImage; ++i){
        cout << "processing image " << this->imageList[i] << endl;
        array2d<rgb_pixel> img;
        load_image(img, this->imageList[i]);
        // Make the image larger so we can detect small faces.
        pyramid_up(img);
        std::vector<rectangle> dets = detector(img);
        cout << "Number of faces detected: " << dets.size() << endl;

  		  std::vector<full_object_detection> shapes;
         for (unsigned long j = 0; j < dets.size(); ++j){
            full_object_detection shape = sp(img, dets[j]);
            shapes.push_back(shape);
        }
        win.clear_overlay();
    		win.set_image(img);
    		win.add_overlay(render_face_detections(shapes));
				cout << "Hit enter to process the next image..." << endl;
				cin.get();
    }

}
