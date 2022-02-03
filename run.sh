#!/bin/bash
rm waveform.wav runme
clang++ main.cc audio.cc notes.cc -I. -std=c++2a -o runme
./runme