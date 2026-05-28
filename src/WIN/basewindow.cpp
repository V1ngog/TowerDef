#include "basewindow.h"
#include "basepage.h"

BaseWindow::BaseWindow(QWidget *parent) : QWidget (parent)
{
    mainLayout = new QVBoxLayout(this);
    stackedLayout = new QStackedLayout();

    mainLayout->addLayout(stackedLayout);
    setLayout(mainLayout);
    setFixedSize(WIN_W, WIN_H);
}

void BaseWindow::registerPage(const QString &name, BasePage *page){
    if (page && !pages.contains(name)) {
        pages[name] = page;
        stackedLayout->addWidget(page);
    }
}

void BaseWindow::navigateTo(const QString &name) {
    if (pages.contains(name)) {
        BasePage* current = qobject_cast<BasePage*>(stackedLayout->currentWidget());
        if (current) {
            current->onPageExit();
        }
        
        stackedLayout->setCurrentWidget(pages[name]);
        pages[name]->onPageEnter();
    }
}

BasePage* BaseWindow::currentPage() {
    return qobject_cast<BasePage*>(stackedLayout->currentWidget());
}