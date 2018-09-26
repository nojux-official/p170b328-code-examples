#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include "MailBox.h"

using namespace std;

int main() {
    MailBox mailBox;
    vector<thread> threads;
    vector<int> received_messages;
    threads.emplace_back([&]{
        for (int i = 0; i < 30; i++){
            mailBox.put(i);
        }
        mailBox.set_finished();
    });
    threads.emplace_back([&]{
        while (!mailBox.get_finished()) {
            int received_mail = mailBox.get();
            received_messages.push_back(received_mail);
        }
    });
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    for_each(received_messages.begin(), received_messages.end(), [=](int i) {cout << i << endl;});
    return 0;
}
