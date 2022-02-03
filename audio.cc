#include "audio.hh"

/**
 * @brief Write the the "size" number of bytes of a value to a file
 */
void Wave::write_to_file(int value, int size)
{
    _file.write(reinterpret_cast<const char*>(&value), size);
}

/**
 * @param time: How long is the audio going to be?
 * @param function: Function being used to generate the audio.
 */
bool Wave::write(int time, std::function<float(Wave*, Oscillator*, Notes*)> function)
{
    /* Add WAVE metadata */

    // Header chunk
    _file << "RIFF";
    _file << "----";
    _file << "WAVE";

    // Format Chunk
    _file << "fmt "; // The extra space here is important as it *must* be 4 bytes.
    write_to_file(16, 4); // as stated, 4 bytes long ONLY.
    write_to_file(1, 2); // Tell the player that it's PCM encoded
    write_to_file(1, 2); // Single channel
    write_to_file(_sample_rate, 4); // Sample rate

    auto byte_rate = _sample_rate * _bit_depth / 8;
    write_to_file(byte_rate, 4); // Rate at which the *bytes* are read

    write_to_file(_bit_depth / 8, 2); // Block align
    write_to_file(_bit_depth, 2); // Bit depth

    // Data chunk
    _file << "data";
    _file << "----";

    // To calculate the size of the data
    _pre_audio_position = _file.tellp();

    // Wave generation function

    function(this, _oscillator, _notes);

    _post_audio_position = _file.tellp();

    // Seek to the position and write the size of the data
    _file.seekp(_pre_audio_position - 4);
    write_to_file(_post_audio_position - _pre_audio_position, 4);

    // Same thing, but for the RIFF chunk
    _file.seekp(4, std::ios::beg);
    write_to_file(_post_audio_position - 8, 4);

    return true;
}
