#ifndef LOSTPAGE_H
#define LOSTPAGE_H

#include "basepage.h"
#include <QLabel>
#include <QPushButton>

class LostPage : public BasePage
{
    Q_OBJECT

public:
    explicit LostPage(QWidget *parent = nullptr);

signals:
    void cancelClicked();

private:
    QLabel *textLost;
    QPushButton *cancelButton;

};  
#endif