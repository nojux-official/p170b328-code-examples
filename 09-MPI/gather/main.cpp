#include <iostream>
#include <mpi.h>
#include <algorithm>

using namespace std;
using namespace MPI;

const auto MAX_MESSAGE_SIZE = 5;
const auto MAX_PROCESS_COUNT = 4;

string get_word(int rank);

int main() {
    char words[MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT];
    fill(words, &words[MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT], '-');
    Init();
    auto rank = COMM_WORLD.Get_rank();
    auto word = get_word(rank);
    char word_buffer[MAX_MESSAGE_SIZE];
    fill(word_buffer, &word_buffer[MAX_MESSAGE_SIZE], '-');
    word.copy(word_buffer, word.size());
    COMM_WORLD.Gather(&word_buffer, MAX_MESSAGE_SIZE, CHAR, words, MAX_MESSAGE_SIZE, CHAR, 0);
    Finalize();
    cout << "Process " << rank << " sent word " << string(word_buffer, MAX_MESSAGE_SIZE) << endl;
    cout << "Process " << rank << " has words " << string(words, MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT) << endl;
    return 0;
}

string get_word(int rank) {
    switch (rank) {
        case 0: {
            return "zero";
        }
        case 1: {
            return "one";
        }
        case 2: {
            return "two";
        }
        case 3: {
            return "three";
        }
        default: {
            cerr << "Unexpected amount of processes" << endl;
        }
    }
    return "";
}
