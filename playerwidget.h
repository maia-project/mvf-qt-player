
#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include <math.h>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QImage>
#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include <opencv2/core/core.hpp>
#include "mvfio.h"

class PlayerWidget : public QWidget 
{
	Q_OBJECT
	
	private:
		QLabel *imagelabel, *infolabel;
		QVBoxLayout *layout;

		QImage image;
		QPixmap pix;
		QPainter painter;
		QPoint pos;

		MVF *data;

#ifdef USE_OPENCV
		std::vector<unsigned short> frame;
		cv::Mat A;
#else
		unsigned short *frame;
#endif
		unsigned int currentFrame;
		
		void putImage ();
		void fillLUT (float gamma);
		void mousePressEvent (QMouseEvent *event);
		void mouseMoveEvent (QMouseEvent *event);
		void zoomSubframe ();
		unsigned short LUT[1024];
	public:
		PlayerWidget(QWidget *parent = 0);
		~PlayerWidget (void);
		void setData (MVF *data);
		void nextFrame ();
		void prevFrame ();
	signals:
}; 

#endif
