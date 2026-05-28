#include "menupage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MenuPage::MenuPage(QWidget *parent) : BasePage(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    startButton = new QPushButton("Start Game", this);
    settingsButton = new QPushButton("Settings", this);
    exitButton = new QPushButton("Exit", this);

    startButton->setFixedSize(200, 50);
    settingsButton->setFixedSize(200, 50);
    exitButton->setFixedSize(200, 50);
    
    watermark = new QLabel("V1ngog's Production");

    QHBoxLayout *helpHLayout1 = new QHBoxLayout();
    helpHLayout1->addStretch();
    helpHLayout1->addWidget(watermark);

    namePage = new QLabel("TowerDef");
    namePage->setStyleSheet("font: bold 32px;");

    QHBoxLayout *helpHLayout2 = new QHBoxLayout();
    helpHLayout2->addWidget(namePage, 0, Qt::AlignCenter);

    layout->addLayout(helpHLayout2);
    layout->addStretch();
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addWidget(settingsButton, 0, Qt::AlignCenter);
    layout->addWidget(exitButton, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addLayout(helpHLayout1);
    
    setLayout(layout);

    connect(startButton, &QPushButton::clicked, this, &MenuPage::startClicked);
    connect(settingsButton, &QPushButton::clicked, this, &MenuPage::settingsClicked);
    connect(exitButton, &QPushButton::clicked, this, &MenuPage::exitClicked);
}