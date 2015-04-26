#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QList>

class QWidget;

class Bucket
{
public:
    typedef QList<Bucket> List;

    Bucket() : m_size(0)
    {
    }

    bool isValid() const
    {
        return !m_id.isEmpty();
    }

    void setTitle(const QString &title)
    {
        m_title = title;
    }

    QString title() const
    {
        return m_title;
    }

    void setSize(int size)
    {
        m_size = size;
    }

    int size() const
    {
        return m_size;
    }

    void setId(const QString &id)
    {
        m_id = id;
    }

    QString id() const
    {
        return m_id;
    }

private:
    QString m_title;
    int m_size;
    QString m_id;
};

class Model
{
public:
    Model(QWidget *parent);

    void initLocalBucketsPath();

    QString localBucketsPath();

    QStringList bucketFiles();

    Bucket::List buckets();
    Bucket readBucket(const QString &path);

private:
    QWidget *m_parent;

    Bucket::List m_buckets;

    QString m_localBucketsPath;
};

#endif
