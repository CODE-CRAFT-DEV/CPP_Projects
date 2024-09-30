# Enigma_Cpp
Enigma Machine Implementation in C++

Overview

This C++ implementation simulates the Enigma machine, a complex electro-mechanical cipher machine developed in the early 20th century and famously used by the Germans during World War II. The Enigma machine is a polyalphabetic substitution cipher, meaning it uses multiple alphabets to encrypt and decrypt messages.

Components

The implementation consists of five main components:

Keyboard: Represents the keyboard input device, converting characters to numerical signals and vice versa.
Plugboard: Simulates the plugboard, a panel of patch cords and sockets that swaps letters before and after the rotor system.
Rotor: Models the rotor wheels, which perform the main encryption and decryption operations.
Reflector: Represents the reflector, a fixed wheel that reflects the signal back through the rotor system.
Enigma: The top-level class that integrates the above components to encrypt and decrypt messages.
How it Works

The Enigma machine works as follows:

The user sets the rotor order, ring settings, and plugboard connections.
The keyboard converts the input message to numerical signals.
The plugboard swaps the signals according to its connections.
The rotor system, consisting of three rotors, encrypts the signals using a complex substitution process.
The reflector reflects the signal back through the rotor system.
The rotor system decrypts the signal, and the plugboard swaps it again.
The keyboard converts the final signal back to the encrypted message.
Implementation Details

The implementation uses C++ classes to represent each component, with methods for encrypting and decrypting signals. The rotor system uses a combination of string manipulation and indexing to perform the encryption and decryption operations. The plugboard and reflector use simple string manipulation to swap and reflect the signals.

Example Usage

The provided example demonstrates how to create an Enigma machine instance, set the rotor order, ring settings, and plugboard connections, and encrypt a message using the encipher method.

Note

This implementation is a simplified version of the Enigma machine and does not include all the complexities and nuances of the original machine. It is intended for educational and illustrative purposes only.
