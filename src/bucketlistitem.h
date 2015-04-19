#ifndef BUCKETLISTITEM_H
#define BUCKETLISTITEM_H

#include <QWidget>

class QLabel;
class QCheckBox;

class BucketListItem : public QWidget
{
    Q_OBJECT
public:
    BucketListItem();

    void readBucket(const QString &path);

private:
    QLabel *m_title;
    QLabel *m_details;
    QCheckBox *m_displayToggle;
};

#endif
