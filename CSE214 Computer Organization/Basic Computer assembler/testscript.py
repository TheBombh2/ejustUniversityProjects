from assembler import Assembler

INPUT_FILE = 'testcode.asm'
OUT_FILE = 'testcode.mc'
MRI_FILE = 'mri.txt'
RRI_FILE = 'rri.txt'
IOI_FILE = 'ioi.txt'

if __name__ == "__main__":
    bin_text = ''
    asm = Assembler(asmpath=INPUT_FILE, \
                    mripath=MRI_FILE, \
                    rripath=RRI_FILE, \
                    ioipath=IOI_FILE)
    print('Assembling...')
    binaries = asm.assemble()
    for lc in binaries:
        bin_text += lc + '\t' + binaries[lc] + '\n'
    with open(OUT_FILE, 'r') as f:
        print('TEST PASSED' if f.read() == bin_text else 'TEST FAILED')
        print(f.read())