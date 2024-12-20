#ifndef MUSICDELEGATE_H
#define MUSICDELEGATE_H

#include <QItemDelegate>
#include <QPainter>

class MusicDelegate : public QItemDelegate
{
public:
    //To fill rating coloum to represent rating out of 100
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MUSICDELEGATE_H
