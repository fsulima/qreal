#pragma once

#include "item.h"
#include "ellipse.h"

class PointPort : public Item
{
public:
	PointPort(qreal x, qreal y, Item *parent = 0);
	virtual QRectF boundingRect() const;
	virtual void drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual void drawExtractionForItem(QPainter* painter);
	virtual void drawFieldForResizeItem(QPainter* painter);
	virtual void changeDragState(qreal x, qreal y);
	virtual void resizeItem(QGraphicsSceneMouseEvent *event);

	virtual QPair<QDomElement, Item::DomElementTypes> generateItem(QDomDocument &document, QPointF const &topLeftPicture);

private:
	qreal mRadius;
};
