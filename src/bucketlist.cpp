#include "bucketlist.h"

#include "model.h"
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
    foreach(QString bucketFile, m_model->bucketFiles()) {
        BucketListItem *item = new BucketListItem;
        m_topLayout->addWidget(item);

        item->readBucket(bucketFile);

        connect(item, SIGNAL(showGraph(const QString &)), SIGNAL(showGraph(const QString &)));
    }
}
