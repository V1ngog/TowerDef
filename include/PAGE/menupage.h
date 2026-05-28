#ifndef MENUPAGE_H
#define MENUPAGE_H

#include "basepage.h"
#include <QLabel>
#include <QPushButton>

class MenuPage : public BasePage
{
    Q_OBJECT

public:
    explicit MenuPage(QWidget *parent = nullptr);

signals:
    void startClicked();
    void settingsClicked();
    void exitClicked();

private:
    QPushButton *startButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    QLabel *watermark;
    QLabel *namePage;
};
#endif