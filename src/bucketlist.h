#ifndef BUCKETLIST_H
#define BUCKETLIST_H

#include <QWidget>

class QBoxLayout;

class BucketList : public QWidget
{
    Q_OBJECT
public:
    explicit BucketList(QWidget *parent = 0);

    void readBuckets();

    QString localBucketsPath();

signals:

public slots:

private:
    QBoxLayout *m_topLayout;
};

#endif
