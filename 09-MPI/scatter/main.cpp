#include <iostream>
#include <mpi.h>
#include <algorithm>

using namespace std;
using namespace MPI;

const int MAIN_PROCESS = 0;

const auto MAX_MESSAGE_SIZE = 5;
const auto MAX_PROCESS_COUNT = 4;

int main() {
    Init();
    char chunk[MAX_MESSAGE_SIZE];
    char words[MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT];
    generate(words, words + MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT, [] { return '-';});
    auto rank = COMM_WORLD.Get_rank();
    if (rank == MAIN_PROCESS) {
        string words_to_scatter[] = {"zero", "one", "two", "three"};
        for (int i = 0; i < MAX_PROCESS_COUNT; i++) {
            string word = words_to_scatter[i];
            word.copy(words + MAX_MESSAGE_SIZE * i, word.size(), 0);
        }
    }
    COMM_WORLD.Scatter(words, MAX_MESSAGE_SIZE, CHAR, chunk, MAX_MESSAGE_SIZE, CHAR, MAIN_PROCESS);
    Finalize();
    string word(chunk, chunk + MAX_MESSAGE_SIZE);
    cout << "Process " << rank << " received " << word << endl;
    cout << "Process " << rank << " had words " << string(words, words + MAX_MESSAGE_SIZE * MAX_PROCESS_COUNT) << endl;
    return 0;
}