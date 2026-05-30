#include "winpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

WinPage::WinPage(QWidget *parent) : BasePage (parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QLabel *title = new QLabel("VICTORY!", this);
    title->setStyleSheet("font: bold 48px; color: green; background-color: rgba(0,0,0);");
    
    QPushButton *menuButton = new QPushButton("Back to Menu", this);
    menuButton->setFixedSize(200, 50);
    
    layout->addStretch();
    layout->addWidget(title, 0, Qt::AlignCenter);
    layout->addSpacing(50);
    layout->addWidget(menuButton, 0, Qt::AlignCenter);
    layout->addStretch();
    
    connect(menuButton, &QPushButton::clicked, this, &WinPage::cancelClicked);
}