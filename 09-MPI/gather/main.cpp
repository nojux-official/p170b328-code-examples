#include <iostream>
#include <mpi.h>
#include <algorithm>

using namespace std;
using namespace MPI;

const auto MAX_MESSAGE_SIZE = 5;
const auto MAX_PROCESS_COUNT = 4;

int main() {
    string word;
    char words[MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT];
    fill(words, &words[MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT], '-');
    Init();
    auto rank = COMM_WORLD.Get_rank();
    switch (rank) {
        case 0: {
            word = "zero";
            break;
        }
        case 1: {
            word = "one";
            break;
        }
        case 2: {
            word = "two";
            break;
        }
        case 3: {
            word = "three";
            break;
        }
        default: {
            word = "";
            cerr << "Unexpected amount of processes" << endl;
        }
    }
    char word_buffer[MAX_MESSAGE_SIZE];
    fill(word_buffer, &word_buffer[MAX_MESSAGE_SIZE], '-');
    word.copy(word_buffer, word.size());
    COMM_WORLD.Gather(&word_buffer, MAX_MESSAGE_SIZE, CHAR, words, MAX_MESSAGE_SIZE, CHAR, 0);
    Finalize();
    cout << "Process " << rank << " sent word " << string(word_buffer, MAX_MESSAGE_SIZE) << endl;
    cout << "Process " << rank << " has words " << string(words, MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT) << endl;
    return 0;
}