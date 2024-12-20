#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include "MailBox.h"

using namespace std;

constexpr auto TERMINATE_MESSAGE = INT32_MAX;
// the program spawns two threads - a "sender" and a "receiver". The sender puts messages into the mailbox, receiver
// takes them from the mailbox. Mailbox can only store one message at a time. The threads are synchronized so that there
// is one write followed by one read -- each message must be sent and received exactly once
int main() {
    // mailbox will be used as shared memory to exchange data
    MailBox mailBox;
    vector<thread> threads;
    threads.emplace_back([&]{
        // sender thread - write 33 "messages"
        for (int i = 0; i < 33; i++){
            mailBox.put(i);
        }
        // when all messages are done writing, write the termination message - it will indicate that the writing is done
        mailBox.put(TERMINATE_MESSAGE);
    });
    threads.emplace_back([&]{
        // receiver thread - receive messages until the termination message arrives and output them all
        int received_mail;  // variable to hold a message
        // receive a message and run the body of the loop if the message is not equal to termination message
        while ((received_mail = mailBox.get()) != TERMINATE_MESSAGE) {
            // print the received message to console (there is one printing thread, so it's fine - console is not a
            // shared resource)
            cout << received_mail << endl;
        }
        // all messages are received, print them all
    });
    // wait for both threads to finish, otherwise they will be killed when main finishes
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    return 0;
}
