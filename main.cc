#include "audio.hh"
#include "notes.hh"
#include <iostream>

void tune(Wave* wave, Oscillator* oscillator, int frequency, float time)
{
    for (int i = 0; i < oscillator->get_sample_rate() * time; i++) {
        float sample = oscillator->sin_wave(frequency);
        // 4 bytes
        int int_sample = static_cast<int>(sample * wave->get_max_amplitude());
        // Remember to write to the file.
        wave->write_to_file(int_sample, 2);
    }
}

float callback(Wave* wave, Oscillator* oscillator, Notes* notes)
{
    auto notes_vec = notes->get_frequencies_vector();
    for (auto note : notes_vec) {
        tune(wave, oscillator, note.frequency, note.time);
    }
    return 1.0f;
}

int main()
{
    // frequency, amplitude, sample_rate, bit_depth
    Oscillator oscillator(440, 1, 44100, 16);

    Notes notes("twinkle.csv");

    // New wave
    Wave wave("waveform.wav", &oscillator, &notes);

    wave.write(5, callback);

    return 0;
}