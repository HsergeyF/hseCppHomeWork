# General compilation info:
    - Apple clang version 14.0.3 (clang-1403.0.22.14.1)

Compilation string:

`
g++ -std=c++17 -g {input.cpp} -o {output}
`

# Stego solution explanation:

- [Paper source](https://www.ijarcce.com/upload/november/13-A%20New%20Approach%20in%20Steganography.pdf)

- We use Least Significant Bit Method Technique, which doesn't change image quality drammatically (+-1 point of each pixel), but message may be easily destroyed by intruder.


# TODO:

- Makefiles, separate to different pathes
- Extra checks for execution file etc.