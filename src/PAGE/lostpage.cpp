#include "lostpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

LostPage::LostPage(QWidget *parent) : BasePage (parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QLabel *title = new QLabel("Lost", this);
    title->setStyleSheet("font: bold 48px; color: red; background-color: rgba(0, 0 ,0, 0);");
    
    QPushButton *cancelButton = new QPushButton("Back to Menu", this);
    cancelButton->setFixedSize(200, 50);
    
    layout->addStretch();
    layout->addWidget(title, 0, Qt::AlignCenter);
    layout->addSpacing(50);
    layout->addWidget(cancelButton, 0, Qt::AlignCenter);
    layout->addStretch();
    
    connect(cancelButton, &QPushButton::clicked, this, &LostPage::cancelClicked);
}