#ifndef BUCKETLISTITEM_H
#define BUCKETLISTITEM_H

#include <QWidget>

class QLabel;

class BucketListItem : public QWidget
{
    Q_OBJECT
public:
    BucketListItem();

    void readBucket(const QString &path);

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
