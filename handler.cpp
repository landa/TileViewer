#include "handler.h"

void Handler::handleImageTileAssoc(const lcm::ReceiveBuffer* rbuf,
                   const std::string& chan,
                   const text_loco::tile_to_image_t* msg) {
  // we got a (tile, image_utime) pair

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
	// cout << " -----------------------" << endl;
  for (tile_it = allTileOrigins->begin(); tile_it != allTileOrigins->end(); ++tile_it) {
      vector<int64_t> images = (*mapTileOriginToImageTimestamp)[*tile_it];
			// cout << *tile_it << " --> ";
			// cout << images.size() << endl;
		}
	}

void Handler::handleImageFrame(const lcm::ReceiveBuffer* rbuf,
                 const std::string& chan,
                 const bot_core::image_t* msg) {
  image_t current = *msg;
  // lcm_instance.publish( "SEEN_TILES_TEMP", &current ); // wtf?
  Mat image(current.height,current.width,CV_8UC4);
  //QImage((unsigned char*)(current.data), current.width, current.height, current.row_stride, QImage::Format_RGB32);
  image.data = (unsigned char*) malloc(current.size);
  copy(current.data.begin(), current.data.end(), image.data);
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
  QImage qimage = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.step, QImage::Format_RGB32);
  (*mapImageTimestampToImage)[msg->utime] = qimage;
  (*mapImageTimestampToMapIndex)[msg->utime] = MAX(0, windowPointer->maps->size() - 1);
  image.release();
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
