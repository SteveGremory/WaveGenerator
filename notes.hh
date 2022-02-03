#pragma once

#include <fstream>
#include <iostream>
#include <vector>

struct SingleNote {
    int frequency;
    float time;
};

class Notes {
public:
    /**
     * @param filename: The Path to the file containing the notes.
     */
    Notes(std::string filename);

    Notes() = default;

    /*
     * the prior being the frequency
     * and the latter being the duration of the note.
     */
    std::vector<SingleNote> get_frequencies_vector() { return _data; };

private:
    // File handle to the notes
    std::ifstream _file;
    // Vector for saving individual notes
    std::vector<SingleNote> _data;
};