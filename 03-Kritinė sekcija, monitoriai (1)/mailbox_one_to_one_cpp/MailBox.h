//
// Created by ryselis on 18.9.20.
//

#ifndef MAILBOX_ONE_TO_ONE_MAILBOX_H
#define MAILBOX_ONE_TO_ONE_MAILBOX_H

#include <mutex>
#include <condition_variable>

using namespace std;

class MailBox {
    int mail;
    bool exists;
    mutex lock;
    condition_variable cv;
    static constexpr int EMPTY_VALUE = INT32_MIN;
public:
    MailBox();
    void put(int new_mail);
    int get();
};


#endif //MAILBOX_ONE_TO_ONE_MAILBOX_H
