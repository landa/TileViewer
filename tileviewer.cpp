#include "tileviewer.h"
#include "ui_tileviewer.h"

TileViewer::TileViewer(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::TileViewer)
{
  ui->setupUi(this);
  maps = new vector<QImage>;
  ui->mapView->setWindow(this);
  selectedOrigin = 0;
  QObject::connect(ui->frameChoice, SIGNAL(valueChanged(int)),
                   this, SLOT(setFrame(int)));
}

TileViewer::~TileViewer() { delete ui; }

void TileViewer::receivedImageForTile(double tileOrigin) {
  double selectedTile = (*allTileOrigins)[selectedOrigin];
  if (tileOrigin == selectedTile) updateImage(tileOrigin);
}

void TileViewer::setTile(int x, int y) {
  int width = ui->mapView->scene()->width();
  int height = ui->mapView->scene()->height();
  if (width == 0 || height == 0) return;
  double lowestDist = 9999999;
  for (size_t ii = 0; ii < allTileOrigins->size(); ++ii) {
    double dist = fabs((*allTileOrigins)[ii] - x);
    if (dist < lowestDist) {
      lowestDist = dist;
      selectedOrigin = ii;
    }
  }
  updateImage((*allTileOrigins)[selectedOrigin]);
  updateMap();
}

void TileViewer::updateImage(double tileOrigin) {
  vector<int64_t> image_utimes = (*mapTileOriginToImageTimestamp)[tileOrigin];
  int chosen_image = MAX(0, image_utimes.size() - 1);
  // update the slider
  ui->frameChoice->blockSignals(true);
  ui->frameChoice->setMinimum(0);
  ui->frameChoice->setMaximum(image_utimes.size()-1);
  // if (ui->frameChoice->value() == chosen_image) setFrame(chosen_image);
  ui->frameChoice->setValue(chosen_image);
  ui->frameChoice->blockSignals(false);

  // double selectedTile = (*allTileOrigins)[selectedOrigin]; // wtf?
  if (image_utimes.size() == 0) return;
  int64_t image_utime = image_utimes[chosen_image];
  QImage qimage = (*mapImageTimestampToImage)[image_utime];
  if (qimage.width() == 0 || qimage.height() == 0) {
    cerr << "trying to render a 0-width or 0-height image for utime " << image_utime << " and index " << chosen_image << "!" << endl;
  }

  // update the frame selection label
  stringstream labelValue;
  labelValue << "*Frame " << chosen_image << "/" << (image_utimes.size()-1);
  ui->frameLabel->setText(labelValue.str().c_str());

  // update the original frame tab
  QGraphicsScene* originalScene = new QGraphicsScene();
  QGraphicsPixmapItem* originalItem = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
  originalScene->addItem(originalItem);
  ui->frameView->setScene(originalScene);
  ui->frameView->show();
}

void TileViewer::updateMap(int mapIndex) {
  QImage mapImage;
  if (mapIndex == -1) mapImage = maps->back();
  else mapImage = (*maps)[mapIndex];
  //maps->pop_back();
  if (mapImage.width() == 0 || mapImage.height() == 0) return;
  QGraphicsScene* scene = new QGraphicsScene();
  QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(mapImage));
  scene->addItem(item);
  double origin = (*allTileOrigins)[selectedOrigin];
  int x_c = origin;
  int y_c = (*mapTileOriginToMapCoords)[origin];
  QPen qpen;
  qpen.setWidth(3);
  scene->addRect(x_c - 10, y_c - 10, 20, 20, qpen);
  ui->mapView->setScene(scene);
  ui->mapView->show();
}

void TileViewer::setFrame(int position) {
  cerr << "FIMUS!!!!!!!!!!!!" << endl;
  double selectedTile = (*allTileOrigins)[selectedOrigin];
  vector<int64_t> image_utimes = (*mapTileOriginToImageTimestamp)[selectedTile];
  if (image_utimes.size() == 0) return;
  int64_t image_utime = image_utimes[position];
  QImage qimage = (*mapImageTimestampToImage)[image_utime];
  if (qimage.width() == 0 || qimage.height() == 0) {
    cerr << "trying to render a 0-width or 0-height image for utime " << image_utime << " and index " << position << "!" << endl;
  }

  // update the frame selection label
  stringstream labelValue;
  labelValue << "Frame " << position << "/" << (image_utimes.size()-1);
  ui->frameLabel->setText(labelValue.str().c_str());

  // update the original frame tab
  QGraphicsScene* originalScene = new QGraphicsScene();
  QGraphicsPixmapItem* originalItem = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
  originalScene->addItem(originalItem);
  ui->frameView->setScene(originalScene);
  ui->frameView->show();

  int mapIndex = (*mapImageTimestampToMapIndex)[image_utime];
  //if (mapIndex < maps->size()) updateMap((*mapImageTimestampToMapIndex)[image_utime]);
}
