#ifndef BUCKETLISTITEM_H
#define BUCKETLISTITEM_H

#include "model.h"

#include <QWidget>

class QLabel;

class BucketListItem : public QWidget
{
    Q_OBJECT
public:
    BucketListItem();

    void setBucket(const Bucket &bucket);

signals:
    void showGraph(const QString &bucketId);

protected slots:
    void slotShowGraph();

private:
    QString m_bucketId;

    QLabel *m_title;
    QLabel *m_details;
};

#endif
