#include <iostream>
#include <string>
#include <vector>

// Keyboard class
class Keyboard {
public:
    int forward(char letter) {
        return letter - 'A';
    }

    char backward(int signal) {
        return signal + 'A';
    }
};

// Plugboard class
class Plugboard {
private:
    std::string left;
    std::string right;

public:
    Plugboard(std::vector<std::string> pairs) : left("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), right("ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
        for (const auto& pair : pairs) {
            char A = pair[0];
            char B = pair[1];
            int pos_A = left.find(A);
            int pos_B = left.find(B);
            left[pos_A] = B;
            left[pos_B] = A;
        }
    }

    int forward(int signal) {
        char letter = right[signal];
        return left.find(letter);
    }

    int backward(int signal) {
        char letter = left[signal];
        return right.find(letter);
    }
};

// Rotor class
class Rotor {
private:
    std::string left;
    std::string right;
    char notch;

public:
    Rotor(std::string wiring, char notch) : left("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), right(wiring), notch(notch) {}

    int forward(int signal) {
        char letter = right[signal];
        return left.find(letter);
    }

    int backward(int signal) {
        char letter = left[signal];
        return right.find(letter);
    }

    void rotate(int n = 1, bool forward = true) {
        for (int i = 0; i < n; ++i) {
            if (forward) {
                left = left.substr(1) + left[0];
                right = right.substr(1) + right[0];
            }
            else {
                left = left[left.size() - 1] + left.substr(0, left.size() - 1);
                right = right[right.size() - 1] + right.substr(0, right.size() - 1);
            }
        }
    }

    void rotate_to_letter(char letter) {
        int n = left.find(letter);
        rotate(n);
    }

    void set_ring(int n) {
        rotate(n - 1, false);
        int n_notch = left.find(notch);
        notch = left[(n_notch - n + 26) % 26];
    }

    char get_notch() const {
        return notch;
    }

    std::string get_left() const {
        return left;
    }
};

// Reflector class
class Reflector {
private:
    std::string left;
    std::string right;

public:
    Reflector(std::string wiring) : left("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), right(wiring) {}

    int reflect(int signal) {
        char letter = right[signal];
        return left.find(letter);
    }
};

// Enigma class
class Enigma {
private:
    Reflector re;
    Rotor r1;
    Rotor r2;
    Rotor r3;
    Plugboard pb;
    Keyboard kb;

public:
    Enigma(Reflector re, Rotor r1, Rotor r2, Rotor r3, Plugboard pb, Keyboard kb)
        : re(re), r1(r1), r2(r2), r3(r3), pb(pb), kb(kb) {}

    void set_rings(std::vector<int> rings) {
        r1.set_ring(rings[0]);
        r2.set_ring(rings[1]);
        r3.set_ring(rings[2]);
    }

    void set_key(std::string key) {
        r1.rotate_to_letter(key[0]);
        r2.rotate_to_letter(key[1]);
        r3.rotate_to_letter(key[2]);
    }

    char encipher(char letter) {
        if (r2.get_notch() == r2.get_left()[0] && r3.get_notch() == r3.get_left()[0]) {
            r1.rotate();
            r2.rotate();
            r3.rotate();
        }
        else if (r2.get_notch() == r2.get_left()[0]) {
            r1.rotate();
            r2.rotate();
            r3.rotate();
        }
        else if (r3.get_notch() == r3.get_left()[0]) {
            r2.rotate();
            r3.rotate();
        }
        else {
            r3.rotate();
        }

        int signal = kb.forward(letter);
        signal = pb.forward(signal);
        signal = r3.forward(signal);
        signal = r2.forward(signal);
        signal = r1.forward(signal);
        signal = re.reflect(signal);
        signal = r1.backward(signal);
        signal = r2.backward(signal);
        signal = r3.backward(signal);
        signal = pb.backward(signal);
        return kb.backward(signal);
    }
};

int main() {
    Keyboard kb;
    Plugboard pb({ "AB", "CD", "EF" });

    Rotor I("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q');
    Rotor II("AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E');
    Rotor III("BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V');
    Rotor IV("ESOVPZJAYQUIRHXLNFTGKDCMWB", 'J');
    Rotor V("VZBRGITYUPSDNHLXAWMJQOFECK", 'Z');
    Reflector A("EJMZALYXVBWFCRQUONTSPIKHGD");
    Reflector B("YRUHQSLDPXNGOKMIEBFZCWVJAT");
    Reflector C("FVPJIAOYEDRZXWGCTKUQSBNMHL");

    Enigma enigma(B, IV, II, I, pb, kb);
    enigma.set_rings({ 5, 26, 2 });
    enigma.set_key("CAT");

    std::string message = "HELLO";
    std::cout << "Enter word: ";
    std::cin >> message;

    std::string cypher_text = "";

    for (char letter : message) {
        cypher_text += enigma.encipher(letter);
    }

    std::cout << cypher_text << std::endl;

    return 0;
}
