#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QWidget>

class BasePage : public QWidget
{
    Q_OBJECT

public:
    explicit BasePage(QWidget *parent = nullptr) : QWidget (parent) {}
    virtual ~BasePage() {}

    virtual void onPageEnter() {}
    virtual void onPageExit() {}
    virtual void updateData() {}
};

#endif