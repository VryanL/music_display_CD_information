#include "musicdelegate.h"

void MusicDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 3) {
        int rating = index.data().toInt();
        QRect rect = option.rect;
        painter->fillRect(rect, Qt::lightGray);
        rect.setWidth(rect.width() * rating / 100);
        painter->fillRect(rect, Qt::blue);
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}
