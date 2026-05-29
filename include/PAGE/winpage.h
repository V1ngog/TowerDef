#ifndef WINPAGE_H
#define WINPAGE_H

#include "basepage.h"
#include <QLabel>
#include <QPushButton>

class WinPage : public BasePage
{
    Q_OBJECT

public:
    explicit WinPage(QWidget *parent = nullptr);

signals:
    void cancelClicked();

private:
    QLabel *textVictory;
    QPushButton *cancelButton;

};  
#endif