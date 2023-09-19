# Ponchisao - WiFi Password Brute Force Program

This is a program written in C++ that retrieves values from a dictionary (dictionary.txt) and attempts to establish connections with the selected Wi-Fi network. If none of the passwords from that dictionary are correct, it will begin making connection attempts with random phrases, mixing numbers, symbols, uppercase, and lowercase characters.

## Requirements

- Ubuntu or a similar Linux kernel.
- The following libraries:
  - `g++`
  - `libstdc++6`
  - `libstdc++-10-dev`

You can install the required libraries using the following commands:

```bash
sudo apt-get update
sudo apt-get install g++
sudo apt-get install libstdc++6
sudo apt-get install libstdc++-10-dev
```

# Download the Dictionary File

Before running the program, you need to download the dictionary file that will be used for brute force attacks. You can obtain it from the following link:

[Download dictionary file](https://ponchisao326.cf/downloads/dictionary.zip)

# Compilation

To compile the program, use the following command in the terminal:

```bash
g++ main.cpp -o bruteforce
```
You can change the name of the file by changing "bruteforce" to something diferent.

## Usage

Run the program as follows:

./bruteforce

The program will prompt you to select a WiFi network from the list of available networks. Then, you can enter the number of passwords you want to try or select 0 to run it infinitely (not recommended).

The program will attempt to find the correct password using the downloaded dictionary file and, if necessary, by generating random passwords. If successful, it will display the password and a successful WiFi connection.

Please note that this program is for educational and legal purposes only and should be used with permission on WiFi networks for which you have authorization to conduct security testing.

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

```markdown
<!-- © 2023 Victor Gomez. All Rights Reserved. -->

This project is licensed under the MIT License - see the LICENSE.md file for details.

Unauthorized copying and reproduction of this project, via any medium, is strictly prohibited, unless explicitly permitted by Victor Gomez.
