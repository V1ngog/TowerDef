#include "gamebutton.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>

GameButton::GameButton(const QString& text, QGraphicsItem *parent) : QGraphicsRectItem (parent)
{
    setRect(0, 0, 120, 40);
    setPen(QPen(Qt::white));
    setBrush(QBrush(QColor(50, 50, 50)));
    setAcceptHoverEvents(true);
    
    m_text = new QGraphicsTextItem(text, this);
    m_text->setDefaultTextColor(Qt::white);
    m_text->setPos(10, 8);
}

void GameButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    emit clicked();
}

void GameButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    setBrush(QBrush(QColor(80, 80, 80)));
}

void GameButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    setBrush(QBrush(QColor(50, 50, 50)));
}