#ifndef MYCAMERAWINDOW_H_
#define MYCAMERAWINDOW_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include "playerwidget.h"
#include "mvfio.h"

class PlayerWindow : public QWidget
{
    Q_OBJECT
    private:
        PlayerWidget *widget;
        MVF *file;
	// unsigned short * frame;
	// int nFrame;
	// int numFrames;
	QTimer *timer;
	void keyPressEvent (QKeyEvent *event);

    public:
        PlayerWindow (char *filename, QWidget *parent=0);
         
    private slots:
        void timerEvent ();
    	void timerStart ();
};


#endif /*MYCAMERAWINDOW_H_*/
