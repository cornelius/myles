#include "bucketlist.h"

#include <QBoxLayout>
#include <QFrame>
#include <QLabel>

BucketList::BucketList(QWidget *parent) : QWidget(parent)
{
    QBoxLayout *topLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Buckets");
    topLayout->addWidget(label);

    QFrame *dummyBucket = new QFrame();
    dummyBucket->setFrameStyle(QFrame::Box | QFrame::Raised);

    topLayout->addWidget(dummyBucket, 1);
}
