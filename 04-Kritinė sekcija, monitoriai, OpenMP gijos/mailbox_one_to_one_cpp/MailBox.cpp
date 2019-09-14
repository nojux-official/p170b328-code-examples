//
// Created by ryselis on 18.9.20.
//

#include "MailBox.h"
#include <limits>

MailBox::MailBox() {
    mail = numeric_limits<int>::min();
    exists = false;
    finished = false;
}

void MailBox::put(int new_mail) {
    unique_lock<mutex> guard(lock);
    cv.wait(guard, [&]{ return !exists;});
    mail = new_mail;
    exists = true;
    cv.notify_all();
}

int MailBox::get() {
    unique_lock<mutex> guard(lock);
    cv.wait(guard, [&]{ return exists;});
    int new_letter = mail;
    exists = false;
    mail = numeric_limits<int>::min();
    cv.notify_all();
    return new_letter;
}

void MailBox::set_finished() {
    finished = true;
}

bool MailBox::get_finished() {
    return finished;
}
