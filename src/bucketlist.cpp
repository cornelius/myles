#include "bucketlist.h"

#include "bucketlistitem.h"

#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QDebug>
#include <QDir>

BucketList::BucketList(Model *model, QWidget *parent) : QWidget(parent),
    m_model(model)
{
    m_topLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Buckets");
    m_topLayout->addWidget(label);

    readBuckets();

    QFrame *dummyBucket = new QFrame();
    dummyBucket->setFrameStyle(QFrame::Box | QFrame::Raised);

    m_topLayout->addWidget(dummyBucket, 1);
}

void BucketList::readBuckets()
{
    foreach(Bucket bucket, m_model->buckets()) {
        if(bucket.isValid()) {
            BucketListItem *item = new BucketListItem;
            m_topLayout->addWidget(item);

            item->setBucket(bucket);

            connect(item, SIGNAL(showGraph(const QString &)), SIGNAL(showGraph(const QString &)));
        }
    }
}
