#include "notes.hh"

Notes::Notes(std::string filename)
{
    // Set the exceptions
    _file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Try opining the file
    try {
        // Open the file
        _file.open(filename);

        // Read the data
        while (!_file.eof()) {
            // Temporary values
            std::string value_string, key_string;

            // Get the line and separate it
            if (!std::getline(_file, key_string, ','))
                break;
            std::getline(_file, value_string, '\n');

            // Convert the string(s) to int(s)
            float value_float = std::stof(value_string);
            int key_int = std::stoi(key_string);

            // Push the notes with the times to the vector.
            _data.push_back(SingleNote { key_int, value_float });
        }

    } catch (std::ifstream::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
}
