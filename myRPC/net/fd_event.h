#ifndef MYRPC_NET_FDEVENT_H
#define MYRPC_NET_FDEVENT_H

#include <functional>
#include <sys/epoll.h>

namespace myRPC {

class FdEvent {
public:

    enum TriggerEvent {
        IN_EVENT = EPOLLIN,
        OUT_EVENT = EPOLLOUT,
        ERROR_EVENT = EPOLLERR, // error事件默认添加到fd
    };

    FdEvent(int fd);

    FdEvent();

    ~FdEvent();

    void setNonBlock();

    std::function<void()> handler(TriggerEvent event_type);

    void listen(TriggerEvent event_type, std::function<void()> callback, std::function<void()> error_callback = nullptr);

    //  cancel listen
    void cancel(TriggerEvent event_type);

    int getFd() const {
        return m_fd;
    }

    epoll_event getEpollEvent(){
        return m_listen_events;
    }

protected:
    int m_fd {-1};

    epoll_event m_listen_events;

    std::function<void()> m_read_callback {nullptr};
    std::function<void()> m_write_callback {nullptr};
    std::function<void()> m_error_callback {nullptr};
};

}

#endif