# Digital Signal Processing Plugin for Multilayered Synthesis
## Evan Sitt
## C3JI5D

-----

### Sound synthesizers have been pivotal to the development of the music industry ever since their inception. Software synthesizers offer advantages in flexibility and modularity, allowing for ease of customization by the end-user.
### Typical software music production involves digital signal processing (DSP) plugins usage. DSP plugins receive input data streams from Audio Stream Input/Output (ASIO) devices and Musical Instrument Digital Interface (MIDI) devices, which the DSP plugin then modifies and manipulates. DSP plugins are hosted by a Digital Audio Workstation (DAW). This is a digitalized version of an analog workstation featuring similar signal flow. The DAW provides the primary user interface while also handling communication with the ASIO drivers and with MIDI devices. The DAW handles final signal manipulation returning a final audio output stream.
### This project will implement a DSP plugin, using the Virtual Studio Technology 3 (VST3) interface standard. VST3 is an interface standard made to handle MIDI and ASIO while allowing the developers to create custom graphical user interfaces. The project will handle MIDI input and generate a polyphonic multilayered synthesizer waveform via the use of wavetables, combining both additive and subtractive synthesis.
### The implementation of the project will be accomplished with the use of the JUCE framework, a popular C++ development framework for audio processing plugins. The application will prioritize end-user customizability, cross-platform compatibility, and a strict low latency processing time. The application will be hosted by any VST3 compatible DAW, or used as a standalone synthesizer application.
### End-users will be able to integrate this DSP plugin into their workflow, either with multiple instances of this DSP plugin or in tandem with other DSP plugins. This DSP plugin will serve sound designers, audio engineers, and mixing engineers as an all-in-one, flexible, and easily customizable digital synthesizer.
