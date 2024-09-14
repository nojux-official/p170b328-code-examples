//
// Created by ryselis on 18.9.20.
//

#include "MailBox.h"

MailBox::MailBox() {
    // initialize mail to some non-meaningful value
    mail = EMPTY_VALUE;
    // message does not exist yet when the mailbox is created
    exists = false;
}

/**
 * Puts the message into the mailbox in a thread-safe way. If previous message has not yet been removed, waits for the
 * removal before writing it
 * @param new_mail - a new message to be added to the mailbox
 */
void MailBox::put(const int new_mail) {
    // use unique lock to lock the whole method. We modify mail and exists, so they both need to be inside critical
    // section
    unique_lock<mutex> guard(lock);
    // if exists flag is true, wait for it to become false
    cv.wait(guard, [&]{ return !exists;});
    // do the actual write of the message
    mail = new_mail;
    exists = true;
    // receiver thread waits for exists to be true, so notify it that it changed
    cv.notify_one();
}

int MailBox::get() {
    // use unique lock to lock the whole method. We modify mail and exists, so they both need to be inside critical
    // section
    unique_lock<mutex> guard(lock);
    // if exists flag is false, wait for it to become true
    cv.wait(guard, [&]{ return exists;});
    // save the message to a temporary variable and clear the mailbox
    const auto new_letter = mail;
    exists = false;
    mail = EMPTY_VALUE;
    // sender thread may be waiting for exists flag to become false, notify it here
    cv.notify_one();
    return new_letter;
}
