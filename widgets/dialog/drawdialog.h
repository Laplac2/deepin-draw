#ifndef DRAWDIALOG_H
#define DRAWDIALOG_H

#include "dialog.h"

class DrawDialog : public Dialog
{
    Q_OBJECT
public:
    explicit DrawDialog(QWidget *parent = 0);

signals:
    void saveDrawImage();

protected:
    void keyPressEvent(QKeyEvent *e) override;

};

#endif // DRAWDIALOG_H
