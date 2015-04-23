#ifndef MODEL_H
#define MODEL_H

#include <QString>

class Model
{
public:
    Model();

    void initLocalBucketsPath();

    QString localBucketsPath();

    QStringList bucketFiles();

private:
    QString m_localBucketsPath;
};

#endif
