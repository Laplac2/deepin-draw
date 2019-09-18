#include "cbuttonrect.h"
#include "cdrawparamsigleton.h"
#include <QPainter>


const int WIDTH = 60;
const int HEIGHT = 20;

const QColor NORMAL = Qt::darkGray;
const QColor PRESS = QColor("#49b2f6");

CButtonRect::CButtonRect(QGraphicsItem *parent, EButtonType type)
    : QGraphicsRectItem (-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, parent)
    , m_buttonType(type)
    , m_backColor(NORMAL)
{
    setCacheMode(NoCache);
    if (m_buttonType == OKButton) {
        m_text = QString("裁剪");
    } else {
        m_text = QString("取消");
    }

    this->setAcceptHoverEvents(true);
}

CButtonRect::~CButtonRect()
{

}

void CButtonRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setClipping(false);

    painter->setRenderHint(QPainter::Antialiasing);



    painter->setPen(Qt::NoPen);
    painter->setBrush(m_backColor);
//    painter->setBrush(QBrush(Qt::MaskOutColor));

    painter->drawRoundRect(boundingRect(), 30, 30);

    painter->setPen(Qt::white);
    QRectF textRect(boundingRect().x(), boundingRect().y() - 2, boundingRect().width(), boundingRect().height());
    painter->drawText(textRect, Qt::AlignHCenter, m_text);

    painter->setClipping(true);
}

CButtonRect::EButtonType CButtonRect::buttonType() const
{
    return m_buttonType;
}

void CButtonRect::move(qreal x, qreal y)
{
    setPos(x, y);
}

bool CButtonRect::hitTest(const QPointF &point)
{
    QPointF pt = mapFromScene(point);
    return this->boundingRect().contains(pt);
}

QRectF CButtonRect::boundingRect() const
{
    qreal scale = CDrawParamSigleton::GetInstance()->getScale();
    QRectF rect = QGraphicsRectItem::boundingRect();
    rect.setWidth(rect.width() / scale);
    rect.setHeight(rect.height() / scale);
    return rect;
}

void CButtonRect::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_backColor = PRESS;
    update();
    QGraphicsRectItem::hoverEnterEvent(event);
}

void CButtonRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_backColor = NORMAL;
    update();
    QGraphicsRectItem::hoverLeaveEvent(event);
}

//void CButtonRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    m_backColor = PRESS;
//    update();
//    QGraphicsRectItem::mousePressEvent(event);
//}

//void CButtonRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    m_backColor = NORMAL;
//    update();
//    QGraphicsRectItem::mouseReleaseEvent(event);
//}
