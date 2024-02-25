class Assembler(object):
    def __init__(self, asmpath='', mripath='', rripath='', ioipath='') -> None:
        """
        Assembler class constructor.

        Initializes 7 important properties of the Assembler class:
        -   self.__address_symbol_table (dict): stores labels (scanned in the first pass)
            as keys and their locations as values.
        -   self.__bin (dict): stores locations (or addresses) as keys and the binary 
            representations of the instructions at these locations (job of the second pass) 
            as values.
        -   self.__asmfile (str): the file name of the assembly code file. This property
            is initialized and defined in the read_code() method.
        -   self.__asm (list): list of lists, where each outer list represents one line of 
            assembly code and the inner list is a list of the symbols in that line.
            for example:
                ORG 100
                CLE
            will yiels __asm = [['org', '100'] , ['cle']]
            Notice that all symbols in self.__asm are in lower case.
        -   self.__mri_table (dict): stores memory-reference instructions as keys, and their
            binary representations as values.
        -   self.__rri_table (dict): stores register-reference instructions as keys, and their
            binary representations as values.
        -   self.__ioi_table (dict): stores input-output instructions as keys, and their
            binary representations as values.
        
        Thie constructor receives four optional arguments:
        -   asmpath (str): path to the assembly code file.
        -   mripath (str): path to text file containing the MRI instructions. The file should
            include each intruction and its binary representation separated by a space in a
            separate line. Their must be no empty lines in this file.
        -   rripath (str): path to text file containing the RRI instructions. The file should
            include each intruction and its binary representation separated by a space in a
            separate line. Their must be no empty lines in this file.
        -   ioipath (str): path to text file containing the IOI instructions. The file should
            include each intruction and its binary representation separated by a space in a
            separate line. Their must be no empty lines in this file.
        """
        super().__init__()
        # Address symbol table dict -> {symbol: location}
        self.__address_symbol_table = {}
        # Assembled machine code dict -> {location: binary representation}
        self.__bin = {}
        # Load assembly code if the asmpath argument was provided.
        if asmpath:
            self.read_code(asmpath)   
        # memory-reference instructions
        self.__mri_table = self.__load_table(mripath) if mripath else {}
        # register-reference instructions
        self.__rri_table = self.__load_table(rripath) if rripath else {}
        # input-output instructions
        self.__ioi_table = self.__load_table(ioipath) if ioipath else {}


        self.__mri_cms = []
        self.__rri_cms = []
        self.__ioi_cms = []
    

    def read_code(self, path:str):
        """
        opens .asm file found in path and stores it in self.__asmfile.
        Returns None
        """
        assert path.endswith('.asm') or path.endswith('.S'), \
                        'file provided does not end with .asm or .S'
        self.__asmfile = path.split('/')[-1] # on unix-like systems
        with open(path, 'r') as f:
            # remove '\n' from each line, convert it to lower case, and split
            # it by the whitespaces between the symbols in that line.
            self.__asm = [s.rstrip().lower().split() for s in f.readlines()]


    def assemble(self, inp='') -> dict:
        assert self.__asm or inp, 'no assembly file provided'
        if inp:
            assert inp.endswith('.asm') or inp.endswith('.S'), \
                        'file provided does not end with .asm or .S'
        # if assembly file was not loaded, load it.
        if not self.__asm:
            self.read_code(inp)
        # remove comments from loaded assembly code.
        self.__rm_comments()
        # do first pass.
        self.__first_pass()
        # do second pass.
        self.__second_pass()
        # The previous two calls should store the assembled binary
        # code inside self.__bin. So the final step is to return
        # self.__bin
        return self.__bin


    # PRIVATE METHODS
    def __load_table(self, path) -> dict:
        """
        loads any of ISA tables (MRI, RRI, IOI)
        """
        with open(path, 'r') as f:
            t = [s.rstrip().lower().split() for s in f.readlines()]
        return {opcode:binary for opcode,binary in t}


    def __islabel(self, string) -> bool:
        """
        returns True if string is a label (ends with ,) otherwise False
        """
        return string.endswith(',')


    def __rm_comments(self) -> None:
        """
        remove comments from code
        """
        for i in range(len(self.__asm)):
            for j in range(len(self.__asm[i])):
                if self.__asm[i][j].startswith('/'):
                    del self.__asm[i][j:]
                    break

    def __format2bin(self, num:str, numformat:str, format_bits:int) -> str:
        """
        converts num from numformat (hex or dec) to binary representation with
        max format_bits. If the number after conversion is less than format_bits
        long, the formatted text will be left-padded with zeros.
        Arguments:
            num (str): the number to be formatted as binary. It can be in either
                        decimal or hexadecimal format.
            numformat (str): the format of num; either 'hex' or 'dec'.
            format_bits (int): the number of bits you want num to be converted to
        """
        if numformat == 'dec':
            return '{:b}'.format(int(num)).zfill(format_bits)
        elif numformat == 'hex':
            return '{:b}'.format(int(num, 16)).zfill(format_bits)
        else:
            raise Exception('format2bin: not supported format provided.')
        
    
    def __convert_table_to_list(self, table: dict):
        final_list = []
        for key, value in table.items():
            final_list.append(key)
        
        print(table)
        print(final_list)
        return final_list

        
        
        

        


    def __first_pass(self) -> None:
        """
        Runs the first pass over the assmebly code in self.__asm.
        Should search for labels, and store the labels alongside their locations in
        self.__address_symbol_table. The location must be in binary (not hex or dec).
        Returns None
        """
        location_counter:hex = 0
        curr_item = 0
        isFinished = False
        print(self.__asm)
        while(not isFinished):
            
            if(self.__islabel(self.__asm[curr_item][0])):
                self.__address_symbol_table[self.__asm[curr_item][0].replace(",","")] = str(location_counter)
                location_counter = hex(int(location_counter, 16) + 1)
                curr_item += 1
                continue

            if(self.__asm[curr_item][0] == "org"):
                location_counter = hex(int(self.__asm[curr_item][1],16))
                
                curr_item +=1
                continue

            if(self.__asm[curr_item][0] != "end"):
                location_counter = hex(int(location_counter, 16) + 1)
                curr_item +=1
                continue

            isFinished = True
            print("\n",self.__address_symbol_table)


              



    def __second_pass(self) -> None:
        """
        Runs the second pass on the code in self.__asm.
        Should translate every instruction into its binary representation using
        the tables self.__mri_table, self.__rri_table and self.__ioi_table. It should
        also store the translated instruction's binary representation alongside its 
        location (in binary too) in self.__bin.
        """
        location_counter:hex = 0
        curr_item = 0
        
        isFinished = False
        Pseudo = ["org", "end", "hex", "dec"]

        self.__mri_cms = self.__convert_table_to_list(self.__mri_table)
        self.__ioi_cms = self.__convert_table_to_list(self.__ioi_table)
        self.__rri_cms = self.__convert_table_to_list(self.__rri_table)

        while(not isFinished):
            instructionID = 0
            curr_instruction = self.__asm[curr_item][instructionID]
            if(self.__islabel(curr_instruction)):
                instructionID += 1
                curr_instruction = self.__asm[curr_item][instructionID]
            
            if(curr_instruction in Pseudo):

                if(curr_instruction == Pseudo[0]):
                    location_counter = hex(int(self.__asm[curr_item][1],16))
                    curr_item += 1
                    continue
                    
                elif(curr_instruction == Pseudo[1]):
                    isFinished = True
                    print(self.__bin)

                elif(curr_instruction == Pseudo[2]):
                    self.__bin[self.__format2bin(location_counter,"hex",12)] = self.__format2bin(self.__asm[curr_item][instructionID + 1],"hex",16)
                
                elif(curr_instruction == Pseudo[3]):
                    self.__bin[self.__format2bin(location_counter,"hex",12)] = self.__format2bin(self.__asm[curr_item][instructionID + 1],"dec",16)

                location_counter = hex(int(location_counter, 16) + 1)
                curr_item +=1
                continue

            elif(curr_instruction in self.__mri_cms):
                curr_inst_opcode = self.__mri_table[curr_instruction]
                try:
                    address = self.__format2bin(self.__asm[curr_item][instructionID + 1],"hex",12)
                except:
                    label = self.__asm[curr_item][instructionID + 1]
                    value = self.__address_symbol_table[label]
                    address = self.__format2bin(value,"hex",12)

                

                try:
                    if(self.__asm[curr_item][instructionID + 2],"hex",1):
                        direct_bit = 1

                except:
                    direct_bit = 0
                
                final_instruction = str(direct_bit) + curr_inst_opcode + address
                self.__bin[self.__format2bin(location_counter,"hex",12)] = final_instruction


            elif(curr_instruction in (self.__ioi_cms + self.__rri_cms)):
                try:
                    final_instruction = self.__ioi_table[curr_instruction]
                except:
                    final_instruction = self.__rri_table[curr_instruction]

                self.__bin[self.__format2bin(location_counter,"hex",12)] = final_instruction

            else:
                self.__bin[self.__format2bin(location_counter,"hex",12)] = "ERROR"

            location_counter = hex(int(location_counter, 16) + 1)
            curr_item += 1





        


        