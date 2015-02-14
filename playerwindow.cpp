#include "playerwindow.h"

PlayerWindow::PlayerWindow(char *filename, QWidget *parent) : QWidget(parent) 
{
    QVBoxLayout *layout = new QVBoxLayout;

    widget = new PlayerWidget(this);
    file = new MVF (filename);

    std::vector<unsigned short> f(file->frameSize);
    file->getFrame (1, f);
    
    widget->setData (file);
    layout->addWidget(widget);
    
    setLayout(layout);
    
    resize (file->header.width, file->header.height);

    timer = new QTimer (this);
    connect (timer, SIGNAL (timeout()), this, SLOT (timerEvent ()));
    // connect (widget, SIGNAL (start()), this, SLOT (timerStart()));
    timer->setInterval (100);
}

void PlayerWindow::timerStart ()
{
	timer->start();
}

void PlayerWindow::timerEvent () 
{
	widget->nextFrame ();
}

void PlayerWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Space)
	{
		timer->isActive() ? timer->stop() : timer->start();
		
	}

	if (event->key() == Qt::Key_Left)
	{
		timer->stop ();
		widget->prevFrame ();
	}

	if (event->key() == Qt::Key_Right)
	{
		timer->stop ();
		widget->nextFrame ();
	}
}
