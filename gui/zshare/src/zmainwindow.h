#ifndef __ZMAINWINDOW_H__
#define __ZMAINWINDOW_H__

#include "zglobal.h"

#define ZMainWindowBase QMainWindow

class Z_EXPORT ZMainWindow : public ZMainWindowBase
{
	Q_OBJECT
public:
	ZMainWindow(QWidget *parent = NULL);
	~ZMainWindow();
};

#endif //__ZMAINWINDOW_H__
