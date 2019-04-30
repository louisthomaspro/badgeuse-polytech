#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>


class Exception : public QException
{

public:
    Exception(QString const& message) : _message(message) {}
    virtual ~Exception() override;
    void raise() const override { throw *this; }
    Exception *clone() const override { return new Exception(*this); }
    QString getMessage() const { return _message; }

private:
    QString _message;

};

#endif // EXCEPTION_H
