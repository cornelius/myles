#include "bucketlistitem.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

BucketListItem::BucketListItem()
{
    QBoxLayout *topLayout = new QVBoxLayout(this);

    m_title = new QLabel;
    topLayout->addWidget(m_title);

    m_details = new QLabel;
    topLayout->addWidget(m_details);

    QPushButton *button = new QPushButton("Show graph");
    topLayout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(slotShowGraph()));
}

void BucketListItem::slotShowGraph()
{
    emit showGraph(m_bucketId);
}

void BucketListItem::setBucket(const Bucket &bucket)
{
    m_bucketId = bucket.id();

    m_title->setText(bucket.title());
    m_details->setText(QString("%1 items\nId: %2").arg(bucket.size()).arg(bucket.id()));
}
