#ifndef _FACIALLANDMARK_H
#define _FACIALLANDMARK_H

// included dependencies
#include "../../dlib/image_processing/frontal_face_detector.h"
#include "../../dlib/image_processing/render_face_detections.h"
#include "../../dlib/image_processing.h"
#include "../../dlib/gui_widgets.h"
#include "../../dlib/image_io.h"


class featureExtractor {
	private:
		int numberOfImage;
		char ** imageList;
	public:
		featureExtractor(int numberOfImage, char **imageList);
		//std::vector<full_object_detection> faceShape();
		void faceShape();
};
#endif
