#include "clickableqtextedit.h"

ClickableQTextEdit::ClickableQTextEdit(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant ClickableQTextEdit::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex ClickableQTextEdit::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex ClickableQTextEdit::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int ClickableQTextEdit::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int ClickableQTextEdit::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant ClickableQTextEdit::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
