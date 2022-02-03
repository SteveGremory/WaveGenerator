#pragma once

#include <cmath>

class Oscillator {

public:
    /**
     * @brief Constructor: Takes in frequency, amplitude, sample rate and bit depth.
     **/
    Oscillator(float frequency, float amplitude, int sample_rate, int bit_depth)
        : _frequency(frequency)
        , _amplitude(amplitude)
        , _sample_rate(sample_rate)
        , _bit_depth(bit_depth)
    {
        /*
            A * sin(2 * pi * f * x / Sampling Rate)
            A = Amplitude
            f = Frequency
        */
        _offset = 2 * M_PI * _frequency / _sample_rate;
    }
    /**
     * @brief Operator: Generates a sine wave
     **/
    float sin_wave()
    {
        float sample = _amplitude * sin(_angle);
        _angle += _offset;

        return sample;
    }

    /**
     * @brief Operator: Generates a sine wave
     * @param frequency: The frequency of the sine wave to be generated
     **/
    float sin_wave(float frequency)
    {
        float sample = _amplitude * sin(_angle);
        _angle += 2 * M_PI * frequency / _sample_rate;

        return sample;
    }

    /**
     * @brief Getter: Returns the sample rate
     **/
    int get_sample_rate()
    {
        return _sample_rate;
    }

    /**
     * @brief Getter: Returns the bit depth
     **/
    int get_bit_depth()
    {
        return _bit_depth;
    }

    /**
     * @brief Getter: Returns the frequency
     **/
    float get_frequency()
    {
        return _frequency;
    }

    /**
     * @brief Getter: Returns the amplitude
     **/
    float get_amplitude()
    {
        return _amplitude;
    }

private:
    // Variables
    float
        _frequency,
        _amplitude,
        _offset,
        _angle = 0.0f;
    int
        _sample_rate,
        _bit_depth;
};