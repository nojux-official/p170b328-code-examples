cmake_minimum_required(VERSION 3.12)
project(mailbox_one_to_one)

set(CMAKE_CXX_STANDARD 20)

add_executable(mailbox_one_to_one main.cpp MailBox.cpp MailBox.h)
TARGET_LINK_LIBRARIES(mailbox_one_to_one pthread)