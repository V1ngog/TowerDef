#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class GameButton : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    
public:
    explicit GameButton(const QString& text, QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

signals:
    void clicked();

private:
    QGraphicsTextItem* m_text;
};
#endif