#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QMap>
#include <QPushButton>
#include "basepage.h"

class BaseWindow : public QWidget 
{
    Q_OBJECT
    

protected:
    const int WIN_W = 800;
    const int WIN_H = 600;
    
    QVBoxLayout *mainLayout;
    QStackedLayout *stackedLayout;
    QMap<QString, BasePage*> pages;

public:
    explicit BaseWindow(QWidget *parent = nullptr);
    virtual ~BaseWindow() {}
    
    void registerPage(const QString &name, BasePage *page);
    void navigateTo(const QString &name);
    BasePage* currentPage();

};
#endif