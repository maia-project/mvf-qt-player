#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent) 
{
	layout = new QVBoxLayout;
	imagelabel = new QLabel;
	infolabel = new QLabel;

	QImage dummy (776, 582, QImage::Format_RGB32);
	image = dummy;
	layout->addWidget(imagelabel);
	layout->addWidget(infolabel);

	for (int x = 0; x < 776; x ++) 
	{
		for (int y = 0; y < 582; y++) 
		{
			image.setPixel (x, y, qRgb (127, 127, 127));
		}
	}

	imagelabel->setPixmap(QPixmap::fromImage(image));

	fillLUT (1.0);

	setLayout(layout);
}

PlayerWidget::~PlayerWidget(void) 
{
	//    
}

void PlayerWidget::fillLUT (float gamma)
{
	for (int i = 0; i < 1024; i++)                
		LUT[i] = (unsigned short)floor(255*(pow(i,gamma)/pow(1023, gamma)));
}

void PlayerWidget::putImage () 
{
#ifndef USE_OPENCV
	unsigned char pixel;

	frame = new unsigned short [data->frameSize];

	data->getFrame (currentFrame, frame);

	for (int y = 0; y < 582; y++) 
	{
		for (int x = 0; x < 776; x++) 
		{
			pixel = LUT[frame[(y*776)+x]];

			image.setPixel(x, y, qRgb (pixel, pixel, pixel));
		}
	}
	
	pix = QPixmap::fromImage(image);
#else
	data->getFrame (currentFrame, frame);

	cv::Mat A (data->header.height, data->header.width, CV_16U, &frame[0]);
	cv::Mat B;

	A.convertTo(B, CV_8U, 255.0 / (pow (2, data->header.bppUsed)));

	pix = QPixmap::fromImage(QImage ((uchar*) B.data, B.cols, B.rows, B.step, QImage::Format_Indexed8));
#endif
	infolabel->setText (QString("%1").arg(currentFrame));
	
	imagelabel->setPixmap(pix);    
}

void PlayerWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)  
	{
		pos = event->pos();
		qDebug () << frame[(pos.y()*776)+pos.x()];
	}
}

void PlayerWidget::mouseMoveEvent (QMouseEvent *event)
{
	QPoint pos = event->pos();
	qDebug () << frame[(pos.y()*776)+pos.x()];
}

void PlayerWidget::setData (MVF * _data)
{
	currentFrame = 0;
	data = _data;
}

void PlayerWidget::nextFrame ()
{
	if (currentFrame < data->header.numOfFrames)
		currentFrame++;
	putImage ();
}

void PlayerWidget::prevFrame ()
{
	if (currentFrame > 1)
		currentFrame--;

	putImage ();
}
