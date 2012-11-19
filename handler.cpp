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
  Mat image = Mat(current.height,current.width,CV_8UC4);
  image.data = (unsigned char*) malloc(current.size);
  copy(current.data.begin(), current.data.end(), image.data);

  // Crop the image so that we only have the left channel
  image = image(Rect(0, 0, MIN(image.cols, 1024), MIN(image.rows, 768)));

  // Save the Mat into our vector
  (*mapImageTimestampToImage)[msg->utime] = new Mat(image);
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
    fprintf(stderr, "emitting receivedMap signal!\n");
    emit receivedMap();
  }
  image.release();
}
