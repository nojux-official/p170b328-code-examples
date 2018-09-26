//
// Created by ryselis on 18.9.20.
//

#ifndef MAILBOX_ONE_TO_ONE_MAILBOX_H
#define MAILBOX_ONE_TO_ONE_MAILBOX_H

#include <mutex>
#include <condition_variable>

using namespace std;

class MailBox {
private:
    int mail;
    bool exists;
    mutex lock;
    condition_variable cv;
    bool finished;
public:
    MailBox();
    void put(int new_mail);
    int get();
    void set_finished();
    bool get_finished();
};


#endif //MAILBOX_ONE_TO_ONE_MAILBOX_H
