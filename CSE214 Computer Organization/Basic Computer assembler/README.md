# Project 2 : Basic Computer Assembler

Welcome to Project 2 of CSE311 Computer Organization!

In this project, you will be building a very simple assembler for the Basic Computer Instruction Set Architecture as per M.Mano's book "Computer System Architecture" [1].

The Basic Computer has a 16-bit instruction divided into 12-bit address, 3-bit opcode and 1-bit for addressing mode.

The Basic Computer's ISA supports 25 instructions categorized as following:
* Memory-Reference Instructions (MRI) : 7 instructions
* Register-Reference Instructions (RRI) : 12 instructions
* Input-Output Instructions (IOI) : 6 instructions

The detailed instructions and their corresponding binary representations are saved in three files `mri.txt` for memory-reference instructions, `rri.txt` for register-reference instructions and finally `ioi.txt` for input-output instructions. Each file contains the instructions each in a separate line, and each line has the instruction and its representation separated by a space. No empty lines are allowed in this file (however, this case is not programmed to raise any errors in the implemented code, yet). The Instruction Set supported by this assembler can be changed by modifying the three mentioned files.

However, there are only 4 pseudo-instructions supported by this assembler: `ORG`, `END`, `HEX` and `DEC`. These instructions do not have a direct binary mapping, but are instructions to the assembler to behave in a certain way during the first and second passes. **Your implementation of the first and second pass of this project should consider only these four pseudo-instructions**.

## Assembly Language Rules

The assembly code supported by this simple assembler must stick to some basic rules otherwise it will yield unpredictable results.

* Each line consists of four parts:
    1. **Label's column** (optional): 3 characters followed by a comma followed by the instruction in the same line. Any label that is not following this convention must yield an error.
        For example, the following code is invalid:
        ```
        ROT,
        CIL
        BUN ROT
        ```
        Instead, you should write the previous code in the following format:
        ```
        ROT, CIL
        BUN ROT
        ```
    2. **Instruction's column** (required): This column can have any of the supported instructions.
    3. **Operand's column** (optional): the operand must correspond to a label included in this assembly code. Reference to labels that do not exist in the same assembly file must cause an error.
    4. **Addressing mode flag** (optional): add `I` if the instruction is indirect.
    5. **Comments' column** (optional): starts with `/` followed by any text. This whole text will be discarded by the assembler and serves the purpose of documentation only.
* There is at least one space between every column.
* Addresses placed after `ORG` are in hexadecimal and are written directly without preceding it with any special characters i.e. `100` is actually (32)<sub>10.
* Similar to the last point, labels created using the `HEX` pseudo instruction should also be without any special characters and should directly write the hexadecimal digits i.e. `AC41`.


You should see an example at `testcode.asm` and `testcode.mc` for the assembly code and the assembled binary machine code, respectively. In the output file, the first column corresponds to the memory location (12 bits), and the second column corresponds to the translated binary representation of the instructions (16 bits).

## assembler.py

The class `Assembler` has 6 methods already implemented for you. It has 7 data structures to save the input assembly code, address symbol table, the instruction set tables and other important information necessary for the assembly. Please read the code carefully before attempting to make any modifications, understand the purpose of every property and method first.

After the second pass, the private property `__bin` (of type dict) should have the binary representation of every assembly instructions as values and their location in memory as keys. The public method `assemble()` returns that object after completing the second pass so that it can be used to store the binary output in a file or send it to the standard output.



## Your task

Your task in this project is to write the code of the `__first_pass(self)` and `__second_pass(self)` methods of the `Assembler` class. The flowchart of the first pass and second pass can be found in Mano's book[1]. You should use the implemented methods when needed or write your own methods to complete this task. You must stick to the language rules and to explained output format (dictionary `__bin`).

Please make sure that you translate all instructions and locations into binary format, and that all binary locations (or addresses) are 12-bit and all binary instructions are 16-bit. If a binary number's length is less than 12 or 16, it must be left-padded with zeros. Moreover, notice that the keys and values at `__bin` are binary numbers of type string i.e. `'00111010011'` not actual integers.

Once your implement the two functions correctly, run `testscript.py` and you should see the following:
```
Assembling...
TEST PASSED
```
If your implementation has an issue, you should see `TEST FAILED` instead.

## Appendix

The following is the detailed ISA:

### Memory-Reference Instructions (MRI) : (7)
| Instruction | Binary Representation |
|-------------| -------|
|AND          |I000xxxxxxxxxxxx|
|ADD          |I001xxxxxxxxxxxx|
|LDA          |I010xxxxxxxxxxxx|
|STA          |I011xxxxxxxxxxxx|
|BUN          |I100xxxxxxxxxxxx|
|BSA          |I101xxxxxxxxxxxx|
|ISZ          |I110xxxxxxxxxxxx|

These instructions have one operand, which is an address in memory. Each instruction starts with the addressing mode bit (I). If I = 0, the addressing is direct, which means that the address (the 12-bit x's) holds the value of the operand. However, if I=1, the addressing is indirect which means the address holds the value of the address of the actual operand.

### Register-Reference Instructions (RRI) (12)
| Instruction | Binary Representation |
|-------------| -------|
|CLA          |0111100000000000|
|CLE          |0111010000000000|
|CMA          |0111001000000000|
|CME          |0111000100000000|
|CIR          |0111000010000000| 
|CIL          |0111000001000000|
|INC          |0111000000100000|
|SPA          |0111000000010000|
|SNA          |0111000000001000|
|SZA          |0111000000000100| 
|SZE          |0111000000000010|
|HLT          |0111000000000001|

These instructions don't have any operands and are translated directly into machine code.

### Input-Output Instructions (IOI) (6)
| Instruction | Binary Representation |
|-------------| -------|
|INP          |1111100000000000|
|OUT          |1111010000000000|
|SKI          |1111001000000000|
|SKO          |1111000100000000|
|ION          |1111000010000000|
|IOF          |1111000001000000|

Similar to RRI, these instructions don't have any operands and are translated directly into machine code.

### Pseudo Instructions

There are four more instructions that can appear in the assembly code which does not directly map into a binary representation: `ORG`, `END`, `HEX`, and `DEC`. These instructions tell the assembler that their location has a special meaning.

## References
[1] M. Mano, “Computer System Architecture,” Pearson Publisher, 3rd Edition, 1992.

## Credits

This project was created by Mostafa Soliman and Osama Adel, 12 Decemeber 2020.