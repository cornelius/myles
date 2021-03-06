#ifndef BUCKETLIST_H
#define BUCKETLIST_H

#include "model.h"

#include <QWidget>

class Model;

class QBoxLayout;

class BucketList : public QWidget
{
    Q_OBJECT
public:
    explicit BucketList(Model *model, QWidget *parent = 0);

    void readBuckets();

    QString localBucketsPath();

signals:
    void showGraph(const QString &bucketId);

public slots:

private:
    Model *m_model;

    QBoxLayout *m_topLayout;
};

#endif
