#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include "AbstractComChannel.hh"
#include <mutex>

class ComChannel : public AbstractComChannel {
private:
    int _socket;
    std::mutex _mutex;

public:
    ComChannel() : _socket(-1) {}

    virtual ~ComChannel() {}

    void Init(int Socket) override {
        _socket = Socket;
    }

    int GetSocket() const override {
        return _socket;
    }

    void LockAccess() override {
        _mutex.lock();
    }

    void UnlockAccess() override {
        _mutex.unlock();
    }

    std::mutex& UseGuard() override {
        return _mutex;
    }

    virtual bool Send(const std::string &message) override{
        return true;
    }

};

#endif  // COMCHANNEL_HH
