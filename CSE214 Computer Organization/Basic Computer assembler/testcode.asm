        ORG 100 /starting location
        CLE     / clear E
        CLA
        STA CTR
        LDA WRD
        SZA
        BUN ROT 
        BUN STP
ROT,    CIL     /start rotating AC
        SZE
        BUN AGN
        BUN ROT
AGN,    CLE
        ISZ CTR
        SZA
        BUN ROT
STP,    HLT
        ORG 120
CTR,    HEX 0
WRD,    HEX 62C1
        END
