#pragma once

#include "notes.hh"
#include "oscillator.hh"

#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>

class Wave {
private:
    // Variables
    int
        _sample_rate,
        _bit_depth,
        _pre_audio_position,
        _post_audio_position;

    float _max_amplitude;
    Oscillator* _oscillator;
    Notes* _notes;
    std::string _filename;
    std::ofstream _file;

public:
    /**
     * @param filename: the path + name of the file being written
     * @param oscillator: the oscillator being used to generate the wave that is to be written to the file
     */
    Wave(std::string filename, Oscillator* oscillator, Notes* notes)
        : _filename(filename)
        , _sample_rate(oscillator->get_sample_rate())
        , _bit_depth(oscillator->get_bit_depth())
        , _oscillator(oscillator)
        , _notes(notes)
    {
        _file.open(_filename, std::ios::binary);
        _max_amplitude = std::pow(2, _bit_depth - 1) - 1;
    }

    ~Wave()
    {
        _file.close();
    }

    /**
     * @param time: length of the audio file
     * @param callback: the function to generate the wave that is to be written to the file.
     */
    bool write(int time, std::function<float(Wave*, Oscillator*, Notes*)> function);
    const char* read();

    /**
     * @brief Getter Returns maximum amplitude
     **/
    float get_max_amplitude() { return _max_amplitude; }

    /**
     * @param value: the value to write
     * @param size: the number of bytes of that value to write
     */
    void write_to_file(int value, int size);
};