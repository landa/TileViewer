#include "handler.h"

void Handler::handleImageTileAssoc(const lcm::ReceiveBuffer* rbuf,
                   const std::string& chan,
                   const text_loco::tile_to_image_t* msg) {
	// represent the tile by its origin
	double origin = msg->x;
	origin = floor(origin+0.5);

	// if we haven't seen this tile, add it to our vector
  if (find(allTileOrigins->begin(), allTileOrigins->end(), origin) == allTileOrigins->end()) {
      allTileOrigins->push_back(origin);
      (*mapTileOriginToMapCoords)[origin] = msg->y;
		}

	// if we don't have this image for our tile, add it
  vector<int64_t> images_for_tile = (*mapTileOriginToImageTimestamp)[origin];
	if (find(images_for_tile.begin(), images_for_tile.end(), msg->image_utime)
			== images_for_tile.end()) {
      (*mapTileOriginToImageTimestamp)[origin].push_back(msg->image_utime);
			try {
				emit receivedImageForTile(origin);
			} catch (int e) {
				cerr << "error!" << endl;
			}
		}

	// go through all tiles and print them out
	vector<double>::iterator tile_it;
  for (tile_it = allTileOrigins->begin(); tile_it != allTileOrigins->end(); ++tile_it) {
      vector<int64_t> images = (*mapTileOriginToImageTimestamp)[*tile_it];
		}
	}

void Handler::handleImageFrame(const lcm::ReceiveBuffer* rbuf,
                 const std::string& chan,
                 const bot_core::image_t* msg) {

  // Extract the image_t data into an OpenCV Mat
  image_t current = *msg;
  Mat* image_ptr = new Mat(current.height,current.width,CV_8UC4);
  Mat image = *image_ptr;
  image.data = (unsigned char*) malloc(current.size);
  copy(current.data.begin(), current.data.end(), image.data);

  // Crop the image so that we only have the left channel
  image = image(Rect(0, 0, MIN(image.cols, 1024), MIN(image.rows, 768)));

  // Draw a checkerboard pattern on the image
  int checkerXOffset = 10;
  int checkerYOffset = image.rows - 70;
  // row 1
  rectangle(image, Point(0+checkerXOffset, 0+checkerYOffset), Point(20+checkerXOffset, 20+checkerYOffset), Scalar(0, 0, 0), -1);
  rectangle(image, Point(20+checkerXOffset, 0+checkerYOffset), Point(40+checkerXOffset, 20+checkerYOffset), Scalar(255, 255, 255), -1);
  rectangle(image, Point(40+checkerXOffset, 0+checkerYOffset), Point(60+checkerXOffset, 20+checkerYOffset), Scalar(0, 0, 0), -1);
  // row 2
  rectangle(image, Point(0+checkerXOffset, 20+checkerYOffset), Point(20+checkerXOffset, 40+checkerYOffset), Scalar(255, 255, 255), -1);
  rectangle(image, Point(20+checkerXOffset, 20+checkerYOffset), Point(40+checkerXOffset, 40+checkerYOffset), Scalar(0, 0, 0), -1);
  rectangle(image, Point(40+checkerXOffset, 20+checkerYOffset), Point(60+checkerXOffset, 40+checkerYOffset), Scalar(255, 255, 255), -1);
  // row 3
  rectangle(image, Point(0+checkerXOffset, 40+checkerYOffset), Point(20+checkerXOffset, 60+checkerYOffset), Scalar(0, 0, 0), -1);
  rectangle(image, Point(20+checkerXOffset, 40+checkerYOffset), Point(40+checkerXOffset, 60+checkerYOffset), Scalar(255, 255, 255), -1);
  rectangle(image, Point(40+checkerXOffset, 40+checkerYOffset), Point(60+checkerXOffset, 60+checkerYOffset), Scalar(0, 0, 0), -1);

  // Turn the Mat into a QImage
  // QImage qimage = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.step, QImage::Format_RGB32);
  // (*mapImageTimestampToImage)[msg->utime] = qimage;
  // (*mapImageTimestampToMapIndex)[msg->utime] = MAX(0, windowPointer->maps->size() - 1);
  // image.release();

  // Save the Mat into our vector
  (*mapImageTimestampToImage)[msg->utime] = &image;
}

void Handler::handleMapImage(const lcm::ReceiveBuffer* rbuf,
                 const std::string& chan,
                 const bot_core::image_t* msg) {
  image_t current = *msg;
  Mat image(current.height,current.width,CV_8UC4);
  image.data = (unsigned char*) malloc(current.size);
  copy(current.data.begin(), current.data.end(), image.data);
  QImage qimage = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.step, QImage::Format_RGB32);
  if (qimage.width() == 0 || qimage.height() == 0) {
    std::cerr << "received a 0-width or 0-height image" << std::endl;
  } else {
    windowPointer->maps->push_back(qimage);
    emit receivedMap();
  }
  image.release();
}
