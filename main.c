#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xtensa/config/core.h>
#include "ecc.h"
#include "sm2.h"
#include "cedar.h"
#include "secureboot.h"
#include "sv100_uart.h"
cedarPkaMode_t pkaMode = pka256bForEcc ;
cedarPkaOp_t pkaOpera = pkaAdd;

sb_para_t secbt = {
 .rootKey     =       NULL,
 .publicKeyHash   =   NULL,
 .userConfig  =       NULL,
.bootImgVer  =        32,
.bootImgSrc  =         0,
.bootSym     =         1,
.bootAsym    =         1,
.bootHashSel =         1,
};


#ifdef __DEBUG__ECC__

ceError_t test_ecc_simple(void)
{
    uint32 sucess_num = 0,BitNum;
    uint8 Hex_inputP[512] = {0};
    char  *rsa_inputMsg[] =  {

    };
    char  *rsa_inputP[] =    {
    };
    char *rsa_res[] = {

   };
    uint8  *IdealResult= "abc";
    //uint8  Hex_inputMsg[512] = {0};
    //uint8  Hex_IdealResult[512] = {0};
    //uint8  outputEnc1[512]={0};

    uint32 ByteNum =0;
    uint32 pka_sts = 0;
    uint32  i = 0,j = 0,k = 0;    
    uint32 hashConfig = HASH_CFG_256_MODE|HASH_FINAL_PART(1)|HASH_SHA2_MODE;

    pkaOpera = 12;
    uint32 test_case = 0;
    uint8  ModeCount = 7;
    uint32 monitor = 0;
    uint32 point_sts = 0;
    #if 0
    uint8  *Hex_IdealResult=(uint8*)malloc(512);
    uint8  *Hex_inputMsg=(uint8*)malloc(1024);
    uint8  *outputEnc1=(uint8*)malloc(512);
    char  *inputMsg = (char*)malloc(1024);
    //for(k = 0;k < 200;k++)
    for(test_case = 0;test_case < 15;test_case++)
    //for(pkaOpera = 1;pkaOpera <= 15;pkaOpera++)
    {
        // if(k == 0)  
        // {pkaOpera = 1;}
        // else if(k == 1)
        // {pkaOpera = 2;}
        // else if(k == 2)
        // {
        //     // if(ce_sha2(input123,output123,0, hashConfig))
        //     // 	return 1;
        //     pkaOpera = 1;
        // }       
        memset(outputEnc1,0,512);
        switch (ModeCount)
        {
        case 0: //448(224+224)
            pkaMode  = pka224bForEcc;
            inputMsg   =   "8E3C994747702DE3EAB6AE65C9A140182A8B2D3A9944491528E9FA9E"
                           "9D9F5E346E3C994747702DE3EAB6AE65C9A140182A8B2D3A99444915";
            IdealResult =  "2BDBF77BB5ACC72B3226DC49B457EE7DF42C6D52C3CF764FC22E43B3";
            break;
        case 1:  //512(256+256)
            pkaMode  = pka256bForEcc;
            ByteNum = 32;
            BitNum = 32;
            switch(pkaOpera)
            {
                case pkaAdd: case pkaSub: case pkaMul: case pkaMod:case pkaModAdd: case pkaModSub: case pkaModMul:
                    inputMsg =  "CE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                                "D093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256";                                                        
                    break;
                case pkaDiv:
                    inputMsg =  "CE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9D093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"
                                "8093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256";
                    break;            
                case pkaModInv:
                    inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9";
                    //inputMsg =  "56D05E3ED493390FAC462D087867634EDD508B090FC5D5BB0625D597921B29B1";
                    //inputMsg =  "A756FBE87979B22AEC10BDC3D2E96792D7E0671D4CA089FA28E939EA7D3C791D";
                    //inputMsg =  "6DB4490BC4DB0D24B80169CEC70D1EFD49FD2AA0985E8BF512A18C0F104B436F";
                    break;
                case pkaPointAdd:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch (test_case)
                    {
                    case 0:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"      //x1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316"      //y2
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"      //x2 
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"   ;  //y1
                        break;
                    case 1:
                        inputMsg =  "0000000000000000000000000000000000000000000000000000000000000000"      //x1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316"      //y2
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"      //x2 
                                    "0000000000000000000000000000000000000000000000000000000000000000"   ;  //y1                 
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 2:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"      //x1
                                    "0000000000000000000000000000000000000000000000000000000000000000"      //y2
                                    "0000000000000000000000000000000000000000000000000000000000000000"      //x2 
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"   ;  //y1                  
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 3:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"      //x1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316"      //y2
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"      //x2
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"   ;  //y1
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0|CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 4:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"      //x1
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"      //y2
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"      //x2
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"   ;  //y1
                        break;                          
                    default:
                        break;
                    }
                    break;

                case pkaPointDbl:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch (test_case)
                    {
                    case 0:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256";
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 1:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                                    "0000000000000000000000000000000000000000000000000000000000000000";
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;    
                    default:
                        break;
                    }
                break;

                case pkaPointMul:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch(test_case)
                    {
                        case 0:
                        // inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                        //             "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"
                        //             "C51E4753AFDEC1E6B6C6A5B992F43F8DD0C7A8933072708B6522468B2FFB06FD";
                        // inputMsg =  "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"
                        //             "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5"
                        //             "3CED51EC692DC48C9F31DB9BCE03198048E281A539CFB15F169CB0E3F63BCEA3";
                        //  inputMsg = "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"
                        //             "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5"
                        //             "56D05E3ED493390FAC462D087867634EDD508B090FC5D5BB0625D597921B29B1";
                        inputMsg =  "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"
                                    "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5"
                                    "6DB4490BC4DB0D24B80169CEC70D1EFD49FD2AA0985E8BF512A18C0F104B436F";
                        break;
                        case 1:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"
                                    "0000000000000000000000000000000000000000000000000000000000000000";  //k=0
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 2:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"
                                    "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551";//k=n
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 3:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"
                                    "ffffffff11111111ffffffffffffffffbce6faada7179e84f3b9cac2fc632551";//k>n
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        default:
                        break;
                    }
                    break;
                case pkamPointMul: //k2 x1 x2 k1 y1 y2   
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch(test_case)
                    {
                        case 0:
                        inputMsg =  "D37F628ECE72A462F0145CBEFE3F0B355EE8332D37ACDD83A358016AEA029DB7"  //k2
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "C51E4753AFDEC1E6B6C6A5B992F43F8DD0C7A8933072708B6522468B2FFB06FD"  //k1
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2

                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        // inputMsg =  "6988041BAF9405FE527889F4BF2B87EA898686B2DE66A2A474A4640289DD01DD"  //k2 
                        //             "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"  //x1 
                        //             "4AEDEECB75171A00AAEED60058046F46E1B7D2A2A0DBF44D5C1BF16E62A2DCFC"  //x2
                        //             "0E051D30269F2733705D4ABCD87DC91D8879908304FE431986E8F118463DC043"  //k1 
                        //             "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5"  //y1
                        //             "D167750F85D38CB69C9A16EA40DC9047979A8A1CC4195FC8B7036034A0CF586F" ;//y2
                        break;
                        case 1:
                        inputMsg =  "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k2 = n
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "0000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 2:
                        inputMsg =  "0000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k1 = n
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 3:
                        inputMsg =  "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k2 = n
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k1 = n
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 4:
                        inputMsg =  "0000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "0000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 5:
                        inputMsg =  "ffffffff11111111ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k2 >n
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "0000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 6:
                        inputMsg =  "ffffffff11111111ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k2 > n
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k1 = n
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 7:
                        inputMsg =  "0000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "ffffffff11111111ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k1 > n
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 8:
                        inputMsg =  "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k2 = n
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "ffffffff11111111ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k1 > n
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 9:
                        inputMsg =  "ffffffff11111111ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k2 > n
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B"  //x2
                                    "ffffffff11111111ffffffffffffffffbce6faada7179e84f3b9cac2fc632551"  //k1 > n
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 10: 
                        inputMsg =  "44222FA1D8F589F00F1BC33A666E7C0D7E1A9BF6A0F3A053DCF49DBA97DCD950"  //k2 
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x2
                                    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01"  //k1 
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256" ;//y2  (k1+k2=n) G1=G2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;  
                        case 11: 
                        inputMsg =  "44222FA1D8F589F00F1BC33A666E7C0D7E1A9BF6A0F3A053DCF49DBA97DCD950"  //k2 
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x2
                                    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01"  //k1 
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256" ;//y2  (x1,y1)  is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0;            
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 12:
                        inputMsg =  "44222FA1D8F589F00F1BC33A666E7C0D7E1A9BF6A0F3A053DCF49DBA97DCD950"  //k2 
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x2
                                    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01"  //k1 
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256" ;//y2  (x2,y2)  is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 13:  
                        inputMsg =  "44222FA1D8F589F00F1BC33A666E7C0D7E1A9BF6A0F3A053DCF49DBA97DCD950"  //k2 
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x1
                                    "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"  //x2
                                    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01"  //k1 
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"  //y1
                                    "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256" ;//y2  (x1,y1) (x2,y2) is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0|CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;                                                                                
                        default:
                            break;
                    }                
                    break;
                default:
                    break;
            }
            StringToHex(inputMsg,Hex_inputMsg,&ByteNum);    
            ce_pka_opa(Hex_inputMsg,(outputEnc1),pkaOpera,pkaMode,NULL);
            break;
        case 2:  //768(384+384)
            pkaMode  = pka384bForEcc;
            ByteNum = 48;
            BitNum = 48;
            switch(pkaOpera)
            {
                case pkaAdd: case pkaSub: case pkaMul: case pkaMod:case pkaModAdd: case pkaModSub: case pkaModMul:
                    inputMsg =  "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"
                                "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E";                                                        
                    break;
                case pkaDiv:
                    inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092"
                                "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051";
                    break;            
                case pkaModInv:
                    inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E";
                    break;
                case pkaPointAdd:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch (test_case)
                    {
                    case 0:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"      //x1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092"      //y2
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"      //x2 
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"   ;  //y1
                        break;
                    case 1:
                        inputMsg =  "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"      //x1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092"      //y2
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"      //x2 
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092"   ;  //y1                 
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 2:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"      //x1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092"      //y2
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"      //x2 
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"   ;  //y1                  
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 3:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"      //x1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092"      //y2
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"      //x2
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"   ;  //y1
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0|CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 4:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"      //x1
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"      //y2
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"      //x2
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"   ;  //y1
                        break;                          
                    default:
                        break;
                    }
                    break;

                case pkaPointDbl:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch (test_case)
                    {
                    case 0:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45";
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 1:
                        inputMsg =  "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"
                                    "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;    
                    default:
                        break;
                    }
                break;

                case pkaPointMul:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch(test_case)
                    {
                        case 0:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"
                                    "A4EBCAE5A665983493AB3E626085A24C104311A761B5A8FDAC052ED1F111A5C44F76F45659D2D111A61B5FDD97583480";
                        break;
                        case 1:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"
                                    "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";  //k=0
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 2:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973";//k=n
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 3:
                        inputMsg =  "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973";//k>n
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        default:
                        break;
                    }
                    break;
                case pkamPointMul: //k2 x1 x2 k1 y1 y2   
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch(test_case)
                    {
                        case 0:
                        inputMsg =  "AFCF88119A3A76C87ACBD6008E1349B29F4BA9AA0E12CE89BCFCAE2180B38D81AB8CF15095301A182AFBC6893E75385D"  //k2
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "A4EBCAE5A665983493AB3E626085A24C104311A761B5A8FDAC052ED1F111A5C44F76F45659D2D111A61B5FDD97583480"  //k1
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2

                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 1:
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 = n
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 2:
                        inputMsg =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 = n
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 3:
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 = n
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 = n
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 4:
                        inputMsg =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 5:
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 >n
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 6:
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 > n
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 = n
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 7:
                        inputMsg =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 > n
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 8:
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 = n
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 > n
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 9:
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 > n
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 > n
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 10: 
                        inputMsg =  "44222FA2D8F589EF0F1BC33A666E7C0DC133A148F9DC01CEB09E20798FB0E1DE52DC3E6877D8C5D12D1323E0CD23507E"  //k2 
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x2
                                    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01053DCF49D0D7E1A9BFD8F589FFA1D8F5"  //k1 
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45" ;//y2  (k1+k2=n) G1=G2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;  
                        case 11: 
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2  (x1,y1)  is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0;            
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 12:
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2  (x2,y2)  is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 13:  
                        inputMsg =  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k2 
                                    "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E"  //x1
                                    "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D81051"  //x2
                                    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"  //k1 
                                    "5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45"  //y1
                                    "84009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092" ;//y2  (x1,y1) (x2,y2) is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0|CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;                                                                                
                        default:
                            break;
                    }                
                    break;
                default:
                    break;
            }
            StringToHex(inputMsg,Hex_inputMsg,&ByteNum);    
            ce_pka_opa(Hex_inputMsg,(outputEnc1),pkaOpera,pkaMode,NULL);

            break;
        case 3:  //1042(521+521)
            pkaMode  = pka521bForEcc;
            inputMsg =   "18E3C994747702DE3EAB6AE65C9A140182A8B2D3A9944491528E9FA9E9D9F5E346E3C994747702DE3EAB6AE65C9A140182A8B2D3A9944491528E9FA9E9D9F5E3412"
                        "1AE48941231ACBC36980AEF15EA008956ADE5654182A8B2D3A994449152AFF12A528E9FA9E9D9F5E346E3C994747702DE3EA3A9944491528E9FABC36980AE1256AF";
            IdealResult ="33C852D59791CEA1A82C19D7BB3A1C96ED870927C1BECFBE8D27E3F2FF04F4F5EC0CB38F1314A23C7319A77FA3E1842F6692ED6CEDDD59BA3C895BE081E4D708AC1";
            break;

        case 4:   //4096(2048+2048)
            pkaMode = pka2048bForRsa;
            pkaOpera =pkaModExp;
            StringToHex(rsa_inputMsg[k],Hex_inputMsg,&ByteNum);
            StringToHex(rsa_inputP[k],Hex_inputP,&ByteNum);
            ce_pka_opa(Hex_inputMsg,outputEnc1,pkaOpera,pkaMode,Hex_inputP);
            break;
        case 5:   //6144(3072+3072)
            pkaMode = pka3072bForRsa;
            pkaOpera =pkaModExp;
            StringToHex(rsa_inputMsg[k],Hex_inputMsg,&ByteNum);
            StringToHex(rsa_inputP[k],Hex_inputP,&ByteNum);
            ce_pka_opa(Hex_inputMsg,outputEnc1,pkaOpera,pkaMode,Hex_inputP);
            break;
        case 6:   //8192(4096+4096)
            pkaMode = pka4096bForRsa;
            pkaOpera =pkaModExp;
            StringToHex(rsa_inputMsg[k],Hex_inputMsg,&ByteNum);
            StringToHex(rsa_inputP[k],Hex_inputP,&ByteNum);
            ce_pka_opa(Hex_inputMsg,outputEnc1,pkaOpera,pkaMode,Hex_inputP);
            break;

        case 7:   //SM2
            pkaMode  = pka256bForEcc;
            ByteNum = 32;
            BitNum = 32;
            switch(pkaOpera)
            {
                case pkaAdd: case pkaSub: case pkaMul: case pkaMod:case pkaModAdd: case pkaModSub: case pkaModMul:
                    inputMsg =  "CE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                                "D093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256";                                                        
                    break;
                case pkaDiv:
                    inputMsg =  "CE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9D093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"
                                "8093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256";
                    break;            
                case pkaModInv:
                    inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9";
                    break;
                case pkaPointAdd:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch (test_case)
                    {
                    case 0:
                        inputMsg =  "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"      //x1
                                    "78E1167231CE7D6AFC3B5C443EA037A9D5812D4214AC5DC50B7B5E8652613D6A"      //y2
                                    "FBA2B4D6B288B1B8EE3971A9058EC4FB35F2F9304D46185B5560003606200C10"      //x2 
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802"   ;  //y1
                        break;
                    case 1:
                        inputMsg =  "0000000000000000000000000000000000000000000000000000000000000000"      //x1
                                    "78E1167231CE7D6AFC3B5C443EA037A9D5812D4214AC5DC50B7B5E8652613D6A"      //y2
                                    "FBA2B4D6B288B1B8EE3971A9058EC4FB35F2F9304D46185B5560003606200C10"      //x2 
                                    "0000000000000000000000000000000000000000000000000000000000000000"   ;  //y1                 
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 2:
                        inputMsg =  "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"      //x1
                                    "0000000000000000000000000000000000000000000000000000000000000000"      //y2
                                    "0000000000000000000000000000000000000000000000000000000000000000"      //x2 
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802"   ;  //y1                  
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 3:
                        inputMsg =  "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"      //x1
                                    "78E1167231CE7D6AFC3B5C443EA037A9D5812D4214AC5DC50B7B5E8652613D6A"      //y2
                                    "FBA2B4D6B288B1B8EE3971A9058EC4FB35F2F9304D46185B5560003606200C10"      //x2 
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802"   ;  //y1
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0|CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 4:
                        inputMsg =  "FBA2B4D6B288B1B8EE3971A9058EC4FB35F2F9304D46185B5560003606200C10"      //x1
                                    "78E1167231CE7D6AFC3B5C443EA037A9D5812D4214AC5DC50B7B5E8652613D6A"      //y2
                                    "FBA2B4D6B288B1B8EE3971A9058EC4FB35F2F9304D46185B5560003606200C10"      //x2 
                                    "78E1167231CE7D6AFC3B5C443EA037A9D5812D4214AC5DC50B7B5E8652613D6A"   ;  //y1
                        break;                          
                    default:
                        break;
                    }
                    break;

                case pkaPointDbl:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch (test_case)
                    {
                    case 0:
                        inputMsg =  "FBA2B4D6B288B1B8EE3971A9058EC4FB35F2F9304D46185B5560003606200C10"
                                    "78E1167231CE7D6AFC3B5C443EA037A9D5812D4214AC5DC50B7B5E8652613D6A";
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                    case 1:
                        inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                                    "0000000000000000000000000000000000000000000000000000000000000000";
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;    
                    default:
                        break;
                    }
                break;

                case pkaPointMul:
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch(test_case)
                    {
                        case 0:
                        // inputMsg =  "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9"
                        //             "C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256"
                        //             "C51E4753AFDEC1E6B6C6A5B992F43F8DD0C7A8933072708B6522468B2FFB06FD";
                        // inputMsg =  "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"
                        //             "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5"
                        //             "3CED51EC692DC48C9F31DB9BCE03198048E281A539CFB15F169CB0E3F63BCEA3";
                        //  inputMsg = "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"
                        //             "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5"
                        //             "56D05E3ED493390FAC462D087867634EDD508B090FC5D5BB0625D597921B29B1";
                        inputMsg =  "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"
                                    "6DB4490BC4DB0D24B80169CEC70D1EFD49FD2AA0985E8BF512A18C0F104B436F";
                        break;
                        case 1:
                        inputMsg =  "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"
                                    "0000000000000000000000000000000000000000000000000000000000000000";  //k=0
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 2:
                        inputMsg =  "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"
                                    "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123";//k=n
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 3:
                        inputMsg =  "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"
                                    "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFDF6B21C6052B53BBF40939D54123";//k>n
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        default:
                        break;
                    }
                    break;
                case pkamPointMul: //k2 x1 x2 k1 y1 y2   
                    CEDAR_CEDAR_PKA_POINT_STATUE = 0;
                    CEDAR_CEDAR_PKA_OP_RPT = 0;
                    monitor = 0;
                    switch(test_case)
                    {
                        case 0:
                        inputMsg =  "D37F628ECE72A462F0145CBEFE3F0B355EE8332D37ACDD83A358016AEA029DB7"  //k2
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "C51E4753AFDEC1E6B6C6A5B992F43F8DD0C7A8933072708B6522468B2FFB06FD"  //k1
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2

                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        // inputMsg =  "6988041BAF9405FE527889F4BF2B87EA898686B2DE66A2A474A4640289DD01DD"  //k2 
                        //             "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"  //x1 
                        //             "4AEDEECB75171A00AAEED60058046F46E1B7D2A2A0DBF44D5C1BF16E62A2DCFC"  //x2
                        //             "0E051D30269F2733705D4ABCD87DC91D8879908304FE431986E8F118463DC043"  //k1 
                        //             "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5"  //y1
                        //             "D167750F85D38CB69C9A16EA40DC9047979A8A1CC4195FC8B7036034A0CF586F" ;//y2
                        break;
                        case 1:
                        inputMsg =  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"  //k2 = n
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "0000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 2:
                        inputMsg =  "0000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"  //k1 = n
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 3:
                        inputMsg =  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"  //k2 = n
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"  //k1 = n
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 4:
                        inputMsg =  "0000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "0000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 5:
                        inputMsg =  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFDF6B21C6052B53BBF40939D54123"  //k2 >n
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "0000000000000000000000000000000000000000000000000000000000000000"  //k1 = 0
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 6:
                        inputMsg =  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFDF6B21C6052B53BBF40939D54123"  //k2 > n
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"  //k1 = n
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 7:
                        inputMsg =  "0000000000000000000000000000000000000000000000000000000000000000"  //k2 = 0
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFDF6B21C6052B53BBF40939D54123"  //k1 > n
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;
                        case 8:
                        inputMsg =  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"  //k2 = n
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFDF6B21C6052B53BBF40939D54123"  //k1 > n
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 9:
                        inputMsg =  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFDF6B21C6052B53BBF40939D54123"  //k2 > n
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFDF6B21C6052B53BBF40939D54123"  //k1 > n
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 10: 
                        inputMsg =  "44222FA1D8F589F00F1BC33A666E7C0D7E1A9BF6A0F3A053DCF49DBA97DCD950"  //k2 
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x2
                                    "BBDDD05D270A760FF0E43CC5999183F1F3E9437480D264D776C7564EA1F867D3"  //k1 
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0" ;//y2  (k1+k2=n) G1=G2
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;  
                        case 11: 
                        inputMsg =  "44222FA1D8F589F00F1BC33A666E7C0D7E1A9BF6A0F3A053DCF49DBA97DCD950"  //k2 
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01"  //k1 
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2  (x1,y1)  is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0;            
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 12:
                        inputMsg =  "44222FA1D8F589F00F1BC33A666E7C0D7E1A9BF6A0F3A053DCF49DBA97DCD950"  //k2 
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01"  //k1 
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2  (x2,y2)  is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;   
                        case 13:  
                        inputMsg =  "44222FA1D8F589F00F1BC33A666E7C0D7E1A9BF6A0F3A053DCF49DBA97DCD950"  //k2 
                                    "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"  //x1
                                    "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F8359"  //x2
                                    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01"  //k1 
                                    "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"  //y1
                                    "8E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802" ;//y2  (x1,y1) (x2,y2) is infinite point
                        CEDAR_CEDAR_PKA_POINT_STATUE = CEDAR_CEDAR_PKA_POINT_STATUE_POINT0|CEDAR_CEDAR_PKA_POINT_STATUE_POINT1;
                        monitor = CEDAR_CEDAR_PKA_POINT_STATUE;
                        break;                                                                                
                        default:
                            break;
                    }                
                    break;
                default:
                    break;
            }
            StringToHex(inputMsg,Hex_inputMsg,&ByteNum);    
            ce_pka_opa(Hex_inputMsg,(outputEnc1),pkaOpera,pkaMode,NULL);
            break;


        default:
            break;
        }

        uint32 cedar_carry = 0;
        //compare result
        switch(ModeCount)
        {
            case 1:
            point_sts = 0;
                switch(pkaOpera)
                {
                case pkaAdd:
                    IdealResult ="9EB7F33EAFFB8A677EEF7828E10D7B61D1A301C275E955176DB1B65DBA1D3A1F";
                    cedar_carry = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_ADDER_OVER_STS;
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaAdd fail\n");
                    else
                    {
                        printf("pkaAdd sucess\n");
                        pka_sts = 0x01<<pkaAdd;
                    }
                    break;
                case pkaSub:
                    IdealResult ="026F69C136E11C9A7913D32CC2BF51510EB8CE5C31B435D5FEB85FEAA6680A8D";
                    cedar_carry = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_SUB_OVER_STS;
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaSub fail\n");
                        
                    else
                    {
                        printf("pkaSub sucess\n");
                        pka_sts = 0x01<<pkaSub;
                    }
                        
                    break;
                case pkaMul:
                    IdealResult ="A7F463322176048D8C65A0704C3F37F8F1F60742B27F4805DFD489A95937C65AFE4BB8E35738C26E16A32FD58F528DE2BBB98A0E01C2C52D90CA70A5754E2F86";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        printf("pkaMul fail\n");
                    else
                    {
                        printf("pkaMul sucess\n");
                        pka_sts = 0x01<<pkaMul;
                    }
                        
                    break;
                case pkaDiv:
                    IdealResult ="9A6EFE7C0E00BC91CC15D0FD9A85388B012D3B8834FBAA9A4B175C720C2A1CE5  ";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaDiv fail\n");   
                    else
                    {
                        printf("pkaDiv sucess\n");
                        pka_sts = 0x01<<pkaDiv;
                    }
                    break;
                case pkaMod:
                    IdealResult ="AF3683AF06F5112BC58C53DED9063171C4D8903FC9BF20A67305E2D2C182AD3B";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaMod fail\n");                   
                    else
                    {
                        printf("pkaMod sucess\n");
                        pka_sts = 0x01<<pkaMod;
                    }
                    break;
                case pkaModAdd:
                    IdealResult ="9EB7F33FAFFB8A667EEF7828E10D7B61D1A301C175E955176DB1B65DBA1D3A20";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,(outputEnc1),BitNum))
                        printf("pkaModAdd fail\n");                    
                    else
                    {
                        printf("pkaModAdd sucess\n");
                        pka_sts = 0x01<<pkaModAdd;
                    }
                    break;
                case pkaModSub:
                    IdealResult ="FD90963DC91EE36686EC2CD33D40AEAEF14731A4CE4BCA2A0147A0155997F572";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaModSub fail\n");
                    else
                    {
                        printf("pkaModSub sucess\n");
                        pka_sts = 0x01<<pkaModSub;
                    }
                    break;
                case pkaModMul:
                    IdealResult ="D24681255EDCE6E675D98DBACFBE7192E388F5BD50680C45810F022BC2499B52";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaModMul fail\n");
                    else
                    {
                        printf("pkaModMul sucess\n");
                        pka_sts = 0x01<<pkaModMul;
                    }
                    break;
                case pkaModInv:
                    IdealResult ="BA3139C658EE097DD5E1E30772CF5258F4666A512EB0449CD1A8BD9C004EC6A0";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaModInv fail\n");   
                    else
                    {
                        printf("pkaModInv sucess\n");
                        pka_sts = 0x01<<pkaModInv;
                    }					
                    break;
                case pkaPointAdd:
                    switch (test_case)
                        {
                        case 0:
                            IdealResult = "72B13DD4354B6B81745195E98CC5BA6970349191AC476BD4553CF35A545A067E8D585CBB2E1327D75241A8A122D7620DC33B13315AA5C9D46D013011744AC264";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            //IdealResult ="0A760D408284F286F64E01D39D6B559B1281BE7CE6D1B82A28F9881C993D4B56A406C2B3103A2D1523A457A9462B8F781FDD55C1BCEEC4BD9B954CB5FC5AA3C2";
                            break;
                        case 1:
                            IdealResult = "55A8B00F8DA1D44E62F6B3B25316212E39540DC861C89575BB8CF92E35E0986B5421C3209C2D6C704835D82AC4C3DD90F61A8A52598B9E7AB656E9D8C8B24316";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 2:
                            IdealResult = "DE2444BEBC8D36E682EDD27E0F271508617519B3221A8FA0B77CAB3989DA97C9C093AE7FF36E5380FC01A5AAD1E66659702DE80F53CEC576B6350B243042A256";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 3:
                            IdealResult = "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";                 
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;                        
                        default:
                            break;
                        }

                    if(!point_sts)
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                    }
                    else
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                    }

                    break;

                case pkaPointDbl:
                    switch (test_case)
                        {
                        case 0:
                            IdealResult = "7669E6901606EE3BA1A8EEF1E0024C33DF6C22F3B17481B82A860FFCDB6127B0FA878162187A54F6C39F6EE0072F33DE389EF3EECD03023DE10CA2C1DB61D0C7";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 1:
                            IdealResult = "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;                      
                        default:
                            break;
                        }

                    if(!point_sts)
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                    }
                    else
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                    }
                        
                    break;
                case pkaPointMul:
                    switch(test_case)
                    {
                        case 0:
                            IdealResult ="51D08D5F2D4278882946D88D83C97D11E62BECC3CFC18BEDACC89BA34EECA03F75EE68EB8BF626AA5B673AB51F6E744E06F8FCF8A6C0CF3035BECA956A7B41D5";
                            //IdealResult ="D65FEB0B4EEBB9C9F9E6337EF5D7F0432191DA394529C5346A4AC36FA794FB489BF72DB40F6A5A8245872961CE11BD6504AECA83F6BA82DB6AF16DC06AFD3AB6";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                        case 1:
                            IdealResult ="00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                        case 2:
                            IdealResult ="00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                        case 3:
                            IdealResult = "845832FC50DE4FDCCDC1284D44ECDEA8E976E117756A39EECFE6C1C9B41805DD7794F8E1166D8F40C9D44300F7580EBBCDC10305A7BBDC821A3DCB3E752FBB0A";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                        default:
                        break;
                        
                    }
                    if(!point_sts)
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                            printf("pkaPointMul fail\n");                    
                        else
                        {
                            pka_sts = 0x01<<pkaPointMul;
                            printf("pkaPointMul sucess\n");
                        }
                    }
                    else
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                        
                    }
                    
                    break;
                case pkamPointMul:
                    switch(test_case)
                        {
                            case 0:
                            IdealResult = "D867B4679221009234939221B8046245EFCF58413DAACBEFF857B8588341F6B8F2504055C03CEDE12D22720DAD69C745106B6607EC7E50DD35D54BD80F615275";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 1:
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 2:
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000"; 
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 3:
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 4:
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 5:
                            IdealResult =  "5D24F80ED6504E2A9DC43F8BB770D84231E8A58817D138E3D988ED2A8709615503F7EF3C6D829A640FBC6F0D8617511BA720B5290FD56805B8BB71AB9570E136"; 
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 6:
                            IdealResult =  "5D24F80ED6504E2A9DC43F8BB770D84231E8A58817D138E3D988ED2A8709615503F7EF3C6D829A640FBC6F0D8617511BA720B5290FD56805B8BB71AB9570E136";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 7:
                            IdealResult =  "845832FC50DE4FDCCDC1284D44ECDEA8E976E117756A39EECFE6C1C9B41805DD7794F8E1166D8F40C9D44300F7580EBBCDC10305A7BBDC821A3DCB3E752FBB0A";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 8:
                            IdealResult =  "845832FC50DE4FDCCDC1284D44ECDEA8E976E117756A39EECFE6C1C9B41805DD7794F8E1166D8F40C9D44300F7580EBBCDC10305A7BBDC821A3DCB3E752FBB0A";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;   
                            case 9:  
                            IdealResult =  "2032F093E34EFF18B0FD6D572D795DA36F1746161C202673E330F67A6F72D5E49E3528B4D631D4CCC8FEAEE6615B562D40425A7BC83121BE559DE7E0854CC794";      
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;      
                                break;   
                            case 10: 
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";  
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break; 
                            case 11: 
                            IdealResult =  "01C709A2EC6A33C9AB320D4A1E2A639A8ED9BC2F4123A849E7FD51BF3ED93F963848238319DE1C1BAE24765EA8AB40ECB942A46A8735EF03D0E09BBA80054531";  
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break; 
                            case 12: 
                            IdealResult =  "01C709A2EC6A33C9AB320D4A1E2A639A8ED9BC2F4123A849E7FD51BF3ED93F96C7B7DC7BE621E3E551DB89A15754BF1346BD5B9678CA10FC2F1F64457FFABACE";  
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break; 
                            case 13: 
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";  
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;                                                                                   
                            default:
                                break;
                        }              
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkamPointMul fail\n");
                    else
                    {
                        pka_sts = 0x01<<pkamPointMul;
                        printf("pkamPointMul sucess\n");
                    }
                    break;
                default:
                    break;
            }   
            break;

            case 2:  //384
            point_sts = 0;
            switch(pkaOpera)
            {
			case pkaAdd:
                IdealResult ="5BA0DF6719A8C9F69B50D5238FEF68A8096FB9FAC5E02C9A5BA43C75A853C9B501D688F02407318BBC600911D39C2953";
                cedar_carry = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_ADDER_OVER_STS;
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
					printf("pkaAdd fail\n");
				else
                {
					printf("pkaAdd sucess\n");
                    pka_sts = 0x01<<pkaAdd;
                }
				break;
			case pkaSub:
                IdealResult ="9BA328091DD17DEECC2C5915F483C71B532B59D2738DC5ACB01713D929077E76D57FF9DE6734219109025D48694B6CC9";
                cedar_carry = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_SUB_OVER_STS;
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
					printf("pkaSub fail\n");
                    
				else
                {
                    printf("pkaSub sucess\n");
                    pka_sts = 0x01<<pkaSub;
                }
					
				break;
			case pkaMul:
                IdealResult ="5E5BA2109DDA7B73A62AE0ECD24F29FB2F487BADD21B47AD979DF95AE3EE355163846B63F2EBB0ACE673891D8066203652264D2DF82FDC439D96667FE60204EA42D7F2E3835CDF259A0345589F863148445217BD34B0D223E8B97B7859F4DEC6";
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
					printf("pkaMul fail\n");
				else
                {
                    printf("pkaMul sucess\n");
                    pka_sts = 0x01<<pkaMul;
                }
					
				break;
			case pkaDiv:
                IdealResult ="7929502EAC2301B4E0F36D3F6DA9C81688F32CE50C01BB67973CEB19694E9CB67D5E8D90E647487D13F720911DA6F2E4";
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
					printf("pkaDiv fail\n");   
				else
                {
					printf("pkaDiv sucess\n");
                    pka_sts = 0x01<<pkaDiv;
                }
				break;
			case pkaMod:
                IdealResult ="868D3A3DB661EF7ACC8ACC224A39F2819616CF5BA297C534977EDA757BC7F1D02FF2EC5342C4F94F976C5BB828E55C72";
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
					printf("pkaMod fail\n");                   
				else
                {
					printf("pkaMod sucess\n");
                    pka_sts = 0x01<<pkaMod;
                }
				break;
			case pkaModAdd:
                IdealResult ="5BA0DF6719A8C9F69B50D5238FEF68A8096FB9FAC5E02C9A5BA43C75A853C9B601D688F12407318BBC600910D39C2954";
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,(outputEnc1),BitNum))
					printf("pkaModAdd fail\n");                    
				else
                {
					printf("pkaModAdd sucess\n");
                    pka_sts = 0x01<<pkaModAdd;
                }
				break;
			case pkaModSub:
                IdealResult ="645CD7F6E22E821133D3A6EA0B7C38E4ACD4A62D8C723A534FE8EC26D6F881882A80062098CBDE6EF6FDA2B896B49336";
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
					printf("pkaModSub fail\n");
				else
                {
					printf("pkaModSub sucess\n");
                    pka_sts = 0x01<<pkaModSub;
                }
				break;
			case pkaModMul:
                IdealResult ="143F1973F1433A25DB2B5E7A0494E1E445D369AA6EDC091E674DBD108691C7B0B194E00EF959BAD778ADD7E7F47967D4";
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
					printf("pkaModMul fail\n");
				else
                {
					printf("pkaModMul sucess\n");
                    pka_sts = 0x01<<pkaModMul;
                }
				break;
			case pkaModInv:
                IdealResult ="D7DE0E6A6069F54309569E3B2EABCD5E9778FBF4C20373D08416BE84A769DC4FBA25BA7D56BC90FC200B5B1DEA7360EE";
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
					printf("pkaModInv fail\n");   
				else
                {
                    printf("pkaModInv sucess\n");
                    pka_sts = 0x01<<pkaModInv;
                }					
				break;
			case pkaPointAdd:
                switch (test_case)
                    {
                    case 0:
                        IdealResult = "12DC5CE7ACDFC5844D939F40B4DF012E68F865B89C3213BA97090A247A2FC009075CF471CD2E85C489979B65EE0B5EED167312E58FE0C0AFA248F2854E3CDDCB557F983B3189B67F21EEE01341E7E9FE67F6EE81B36988EFA406945C8804A4B0";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                    case 1:
                        IdealResult = "AACC05202E7FDA6FC73D82F0A66220527DA8117EE8F8330EAD7D20EE6F255F582D8BD38C5A7F2B40BCDB68BA13D8105184009A263FEFBA7C2C57CFFA5DB3634D286131AFC0FCA8D25AFA22A7B5DCE0D9470DA89233CEE178592F49B6FECB5092";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                    case 2:
                        IdealResult = "FBA203B81BBD23F2B3BE971CC23997E1AE4D89E69CB6F92385DDA82768ADA415EBAB4167459DA98E62B1332D1E73CB0E5FFEDBAEFDEBA603E7923E06CDB5D0C65B22301429293376D5C6944E3FA6259F162B4788DE6987FD59AED5E4B5285E45";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                    case 3:
                        IdealResult = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";                 
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;                        
                    default:
                        break;
                    }

                if(!point_sts)
                {
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                    {
                        printf("pkaPointAdd fail\n");
                    }
                    else
                    {
                        printf("pkaPointAdd sucess\n");
                        pka_sts = 0x01<<pkaPointAdd;
                    }
                }
                else
                {
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                    {
                        printf("pkaPointAdd fail\n");
                    }
                    else
                    {
                        printf("pkaPointAdd sucess\n");
                        pka_sts = 0x01<<pkaPointAdd;
                    }
                }

				break;

			case pkaPointDbl:
                switch (test_case)
                    {
                    case 0:
                        IdealResult = "2A2111B1E0AA8B2FC5A1975516BC4D58017FF96B25E1BDFF3C229D5FAC3BACC319DCBEC29F9478F42DEE597B4641504CFA2E3D9DC84DB8954CE8085EF28D7184FDDFD1344B4D4797343AF9B5F9D837520B450F726443E4114BD4E5BDB2F65DDD";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                    case 1:
                        IdealResult = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;                      
                    default:
                        break;
                    }

                if(!point_sts)
                {
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                    {
                        printf("pkaPointAdd fail\n");
                    }
                    else
                    {
                        printf("pkaPointAdd sucess\n");
                        pka_sts = 0x01<<pkaPointAdd;
                    }
                }
                else
                {
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                    {
                        printf("pkaPointAdd fail\n");
                    }
                    else
                    {
                        printf("pkaPointAdd sucess\n");
                        pka_sts = 0x01<<pkaPointAdd;
                    }
                }
					
				break;
			case pkaPointMul:
                switch(test_case)
                {
                    case 0:
                        IdealResult ="E4F77E7FFEB7F0958910E3A680D677A477191DF166160FF7EF6BB5261F791AA7B45E3E653D151B95DAD3D93CA0290EF2AC7DEE41D8C5F4A7D5836960A773CFC1376289D3373F8CF7417B0C6207AC32E913856612FC9FF2E357EB2EE05CF9667F";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                    break;
                    case 1:
                        IdealResult ="000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                    break;
                    case 2:
                        IdealResult ="000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                    break;
                    case 3:
                        IdealResult = "EEA240A63ADB4F65E1A9510B5C174FB937B0C88F05D166F876DB17BF718DC78F4B8371A8F4D45D43D0542BC91EB8E0F54B84F1C002FB7D14247553A4A56CC9403D9F296DFFD4738EE5F8B708BA6D0CB1D24E04777C7D591702A063765E5583AD";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                    break;
                    default:
                    break;
                    
                }
                if(!point_sts)
                {
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        printf("pkaPointMul fail\n");                    
                    else
                    {
                        pka_sts = 0x01<<pkaPointMul;
                        printf("pkaPointMul sucess\n");
                    }
                }
                else
                {
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                    {
                        printf("pkaPointAdd fail\n");
                    }
                    else
                    {
                        printf("pkaPointAdd sucess\n");
                        pka_sts = 0x01<<pkaPointAdd;
                    }
                    
                }
                
				break;
			case pkamPointMul:
                switch(test_case)
                    {
                        case 0:
                        IdealResult = "917EA28BCD641741AE5D18C2F1BD917BA68D34F0F0577387DC81260462AEA60E2417B8BDC5D954FC729D211DB23A02DC1A29F7CE6D074654D77B40888C73E92546C8F16A5FF6BCBD307F758D4AEE684BEFF26F6742F597E2585C86DA908F7186";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 1:
                        IdealResult =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 2:
                        IdealResult =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"; 
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 3:
                        IdealResult =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 4:
                        IdealResult =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 5:
                        IdealResult =  "2A36B166787F96A5764B429A827B016A1B3F54383479F3621D4C8D900FA2604D202787693F59EB51162325A0AB08A53F02D8DD7CC2076961470FB575D51B0481FDC6E6FF8EFFBC5D29E3138831DFE793B6CE4ABE1AC5D23F7132CB0BA41C04AD"; 
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 6:
                        IdealResult =  "2A36B166787F96A5764B429A827B016A1B3F54383479F3621D4C8D900FA2604D202787693F59EB51162325A0AB08A53F02D8DD7CC2076961470FB575D51B0481FDC6E6FF8EFFBC5D29E3138831DFE793B6CE4ABE1AC5D23F7132CB0BA41C04AD";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 7:
                        IdealResult =  "EEA240A63ADB4F65E1A9510B5C174FB937B0C88F05D166F876DB17BF718DC78F4B8371A8F4D45D43D0542BC91EB8E0F54B84F1C002FB7D14247553A4A56CC9403D9F296DFFD4738EE5F8B708BA6D0CB1D24E04777C7D591702A063765E5583AD";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 8:
                        IdealResult =  "EEA240A63ADB4F65E1A9510B5C174FB937B0C88F05D166F876DB17BF718DC78F4B8371A8F4D45D43D0542BC91EB8E0F54B84F1C002FB7D14247553A4A56CC9403D9F296DFFD4738EE5F8B708BA6D0CB1D24E04777C7D591702A063765E5583AD";
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;   
                        case 9:  
                        IdealResult =  "903BCA4E1BDFB3A45D63FC50335DFD27AE582888F1411F341821C32925578F16AE8A37C37AD67F0099EBFBAAC31B344B852D10A3589CEBF37E2823DECEA67CE8A63C338350C9B0228B8991FA4F436678BB2C592D788E509D8D874F4A78C17117";      
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;      
                            break;   
                        case 10: 
                        IdealResult =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";  
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break; 
                        case 11: 
                        IdealResult =  "2A36B166787F96A5764B429A827B016A1B3F54383479F3621D4C8D900FA2604D202787693F59EB51162325A0AB08A53F02D8DD7CC2076961470FB575D51B0481FDC6E6FF8EFFBC5D29E3138831DFE793B6CE4ABE1AC5D23F7132CB0BA41C04AD";  
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break; 
                        case 12: 
                        IdealResult =  "EEA240A63ADB4F65E1A9510B5C174FB937B0C88F05D166F876DB17BF718DC78F4B8371A8F4D45D43D0542BC91EB8E0F54B84F1C002FB7D14247553A4A56CC9403D9F296DFFD4738EE5F8B708BA6D0CB1D24E04777C7D591702A063765E5583AD";  
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break; 
                        case 13: 
                        IdealResult =  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";  
                        point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;                                                                                   
                        default:
                            break;
                    }              
                StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
				if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
					printf("pkamPointMul fail\n");
				else
                {
                    pka_sts = 0x01<<pkamPointMul;
					printf("pkamPointMul sucess\n");
                }
				break;

			default:
				break;
        }   
            break;

            case 6:   //modexp
                if(ModeCount == 4)  
                    BitNum = 256;
                else if(ModeCount == 5)
                    BitNum = 384;
                else if(ModeCount == 6)  
                    BitNum = 512;
                StringToHex(rsa_res[k],Hex_IdealResult,&ByteNum);
                if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                    printf("pkamPointMul fail\n"); 
                else
                {
                    sucess_num++;
                    pka_sts = 0x01<<pkaModExp;
                    printf("pkamPointMul sucess\n");
                }
            break;

            case 7:  //SM2
            point_sts = 0;
                switch(pkaOpera)
                {
                case pkaAdd:
                    IdealResult ="9EB7F33EAFFB8A677EEF7828E10D7B61D1A301C275E955176DB1B65DBA1D3A1F";
                    cedar_carry = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_ADDER_OVER_STS;
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaAdd fail\n");
                    else
                    {
                        printf("pkaAdd sucess\n");
                        pka_sts = 0x01<<pkaAdd;
                    }
                    break;
                case pkaSub:
                    IdealResult ="026F69C136E11C9A7913D32CC2BF51510EB8CE5C31B435D5FEB85FEAA6680A8D";
                    cedar_carry = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_SUB_OVER_STS;
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaSub fail\n");
                        
                    else
                    {
                        printf("pkaSub sucess\n");
                        pka_sts = 0x01<<pkaSub;
                    }
                        
                    break;
                case pkaMul:
                    IdealResult ="A7F463322176048D8C65A0704C3F37F8F1F60742B27F4805DFD489A95937C65AFE4BB8E35738C26E16A32FD58F528DE2BBB98A0E01C2C52D90CA70A5754E2F86";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        printf("pkaMul fail\n");
                    else
                    {
                        printf("pkaMul sucess\n");
                        pka_sts = 0x01<<pkaMul;
                    }
                        
                    break;
                case pkaDiv:
                    IdealResult ="9A6EFE7C0E00BC91CC15D0FD9A85388B012D3B8834FBAA9A4B175C720C2A1CE5  ";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaDiv fail\n");   
                    else
                    {
                        printf("pkaDiv sucess\n");
                        pka_sts = 0x01<<pkaDiv;
                    }
                    break;
                case pkaMod:
                    IdealResult ="9D2BA5EFDF94E8DAF9DFC82E62B6ABA5FB31CF37D2FC790E98B93E841F8F3FFE";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaMod fail\n");                   
                    else
                    {
                        printf("pkaMod sucess\n");
                        pka_sts = 0x01<<pkaMod;
                    }
                    break;
                case pkaModAdd:
                    IdealResult ="9EB7F33FAFFB8A677EEF7828E10D7B61D1A301C375E955166DB1B65DBA1D3A20";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,(outputEnc1),BitNum))
                        printf("pkaModAdd fail\n");                    
                    else
                    {
                        printf("pkaModAdd sucess\n");
                        pka_sts = 0x01<<pkaModAdd;
                    }
                    break;
                case pkaModSub:
                    IdealResult ="FD90963DC91EE36586EC2CD33D40AEAEF14731A2CE4BCA2B0147A0155997F572";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaModSub fail\n");
                    else
                    {
                        printf("pkaModSub sucess\n");
                        pka_sts = 0x01<<pkaModSub;
                    }
                    break;
                case pkaModMul:
                    IdealResult ="C7E03BB612993171C6E6E33E32AC5C43355C38461ADAD02B808DF1814AAF172D";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaModMul fail\n");
                    else
                    {
                        printf("pkaModMul sucess\n");
                        pka_sts = 0x01<<pkaModMul;
                    }
                    break;
                case pkaModInv:
                    IdealResult ="B82BDCC5C2CFF2D67A62A31D5CEF1D081161F17F3B078438EB81D190350604D0";
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkaModInv fail\n");   
                    else
                    {
                        printf("pkaModInv sucess\n");
                        pka_sts = 0x01<<pkaModInv;
                    }					
                    break;
                case pkaPointAdd:
                    switch (test_case)
                        {
                        case 0:
                            IdealResult = "8F9782E683E5AC90489BDC1C811B15D560C92E9F0B2DB716E627174CBF142F1C004D615A8DA149A844D7F3C4F63F21CEA292BC4B1EDA9E84A4B59F3C090D6C38";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            //IdealResult ="0A760D408284F286F64E01D39D6B559B1281BE7CE6D1B82A28F9881C993D4B56A406C2B3103A2D1523A457A9462B8F781FDD55C1BCEEC4BD9B954CB5FC5AA3C2";
                            break;
                        case 1:
                            IdealResult = "FBA2B4D6B288B1B8EE3971A9058EC4FB35F2F9304D46185B5560003606200C1078E1167231CE7D6AFC3B5C443EA037A9D5812D4214AC5DC50B7B5E8652613D6A";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 2:
                            IdealResult = "B793DC6205CC1680CC5CDB5D527047B2D00598525233A7C803468F9C4A8F83598E125229FFD05E24E8FF8D08D4723F1CAE8EBF1F9458990462C4022C09C9F802";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 3:
                            IdealResult = "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";                 
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;                        
                        default:
                            break;
                        }

                    if(!point_sts)
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                    }
                    else
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                    }

                    break;

                case pkaPointDbl:
                    switch (test_case)
                        {
                        case 0:
                            IdealResult = "59564E7C5F5400A3A586043FCF58BCD58EA1D3CC2EB8A72A6FA6366FA87A624754585C386BA7CFBA4A0EE5C795B334F19898DDD8BA0C25A55709B4BDF6E3868D";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;
                        case 1:
                            IdealResult = "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                            break;                      
                        default:
                            break;
                        }

                    if(!point_sts)
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                    }
                    else
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                    }
                        
                    break;
                case pkaPointMul:
                    switch(test_case)
                    {
                        case 0:
                            IdealResult ="A5913B75FD8A61F25830CB5FD1834AAE07CA92088349932A63B83E087EBF0DB4773C0AF080E10BC484CBBBA848506FE4C87899FA47CFAB022664366806A6F53E";
                            //IdealResult ="D65FEB0B4EEBB9C9F9E6337EF5D7F0432191DA394529C5346A4AC36FA794FB489BF72DB40F6A5A8245872961CE11BD6504AECA83F6BA82DB6AF16DC06AFD3AB6";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                        case 1:
                            IdealResult ="00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                        case 2:
                            IdealResult ="00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                        case 3:
                            IdealResult = "830CDB9183C8314B65188F5C282D24DEBC1C1B1AC48E3394DE810DE378354AC3547FE38AF8EEE8A5229ACA7F5C6A4AE8D7E2DD68C369262897E895B5ABE5A2B7";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                        break;
                        default:
                        break;
                        
                    }
                    if(!point_sts)
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                            printf("pkaPointMul fail\n");                    
                        else
                        {
                            pka_sts = 0x01<<pkaPointMul;
                            printf("pkaPointMul sucess\n");
                        }
                    }
                    else
                    {
                        StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                        if(compareBN(Hex_IdealResult,outputEnc1,BitNum*2))
                        {
                            printf("pkaPointAdd fail\n");
                        }
                        else
                        {
                            printf("pkaPointAdd sucess\n");
                            pka_sts = 0x01<<pkaPointAdd;
                        }
                        
                    }
                    
                    break;
                case pkamPointMul:
                    switch(test_case)
                        {
                            case 0:
                            IdealResult = "50F8B6339F23863158AAE5267F75AA8805E500DC2DBB87DE1981F9BB0FC1E8AC20DA0E1DFA9E0219B1680F520226941F4DDB13364418FD39C73AEF82AE5DC446";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 1:
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 2:
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000"; 
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 3:
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 4:
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 5:
                            IdealResult =  "829BA1D05DCC1E9D1FE10072AD663FE53E7775A823EBE59247EAEC867BAC348AFD5473D77A7C82F0F2CB6DB07E9220F5EB19D78856CA85D70334EF843CEEF8DE"; 
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 6:
                            IdealResult =  "829BA1D05DCC1E9D1FE10072AD663FE53E7775A823EBE59247EAEC867BAC348AFD5473D77A7C82F0F2CB6DB07E9220F5EB19D78856CA85D70334EF843CEEF8DE";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 7:
                            IdealResult =  "830CDB9183C8314B65188F5C282D24DEBC1C1B1AC48E3394DE810DE378354AC3547FE38AF8EEE8A5229ACA7F5C6A4AE8D7E2DD68C369262897E895B5ABE5A2B7";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;
                            case 8:
                            IdealResult =  "830CDB9183C8314B65188F5C282D24DEBC1C1B1AC48E3394DE810DE378354AC3547FE38AF8EEE8A5229ACA7F5C6A4AE8D7E2DD68C369262897E895B5ABE5A2B7";
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;   
                            case 9:  
                            IdealResult =  "68DB3F76C3C75DCB201DAA75834A216A2504C41A7C43DBAE97564A2F3956B31122A8106781920A354B99249C3667F85ACFF4621835FAE78A6847BA86FE2772DA";      
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;      
                                break;   
                            case 10: 
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";  
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break; 
                            case 11: 
                            IdealResult =  "84D9672C29A5CA4F5136D09FA969ECB6650BEC57C13FAAED666ECE7AF020670F9CA1F53474C71A11F3915A8AE416BED7A478EB068890B3D1C8076AE06F4ADCA5";  
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break; 
                            case 12: 
                            IdealResult =  "63930D1452AD9D8D319DC8D8AF436A7528CFB21FC36279430AB1754ED177F06A8EDD8826B24E0C60C1739E9834BA36DDB6832378B72B7624480DB5AF7F820B98";  
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break; 
                            case 13: 
                            IdealResult =  "00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";  
                            point_sts = CEDAR_CEDAR_PKA_OP_RPT & CEDAR_INFINITY_POINT_STS;
                                break;                                                                                   
                            default:
                                break;
                        }              
                    StringToHex(IdealResult,Hex_IdealResult,&ByteNum);
                    if(compareBN(Hex_IdealResult,outputEnc1,BitNum))
                        printf("pkamPointMul fail\n");
                    else
                    {
                        pka_sts = 0x01<<pkamPointMul;
                        printf("pkamPointMul sucess\n");
                    }
                    break;
                default:
                    break;
            }   
            break;

        
        default:
				break;
        }
    
    }
    free(outputEnc1);
    free(Hex_IdealResult);
    free(Hex_inputMsg);
    free(inputMsg);
    #endif

   //#define  SM2_DEC

    #if defined ECC_ENC
        uint8  ouputMsg[512] = {0};
        uint32 blen = 32;
        uint8 Hex_prikey[32] = {0};
        uint8 Hex_inputRand[32] = {0};
        uint8 Hex_publicKey[64] = {0};
        inputMsg = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123";
        char *inputRand= "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01";
        char *publicKey = "4AEDEECB75171A00AAEED60058046F46E1B7D2A2A0DBF44D5C1BF16E62A2DCFC"
                          "D167750F85D38CB69C9A16EA40DC9047979A8A1CC4195FC8B7036034A0CF586F";
        StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        StringToHex(inputRand,Hex_inputRand,&ByteNum);
        StringToHex(publicKey,Hex_publicKey,&ByteNum);    
        ce_ecc_enc(Hex_inputMsg, ouputMsg, blen, Hex_inputRand, Hex_publicKey,pkaMode);
        break;
    #elif  defined ECC_DEC
        uint8  ouputMsg[512] = {0};
        uint32 blen = 144;
        uint8 Hex_prikey[32] = {0};
        uint8 Hex_inputRand[32] = {0};
        uint8 Hex_publicKey[64] = {0};
        inputMsg = "3468B0084D607B31F5E928FAAAF1D978B334008D6C2E9FCBAE6329DE4795C32C960F07BE96B460103662D0616DDAD031723718E11DF914C8E45F897ED02525121C4442F76A7E709955BE118390DD2CDD0AA427BA5CD5B0C66ED29AE54D32BFF1F1F7EE7EE0B6D9E0775893BA745571F8F3892642527129AFE2E8A64179AFA914E49A0E49CCB8FBD3DE48B35DB931125B";
        char *priKey = "2C9F3E0B9382C501CC07229F52CBB1C8F0C337B74A3D8FF843DC505AC65B940F";
        StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        StringToHex(priKey,Hex_prikey,&ByteNum);    
        ce_ecc_dec(Hex_inputMsg, ouputMsg, blen, Hex_prikey, pkaMode);
    #elif  defined ECC_SIGNATURE
        uint8  ouputMsg[512] = {0};
        uint32 blen = 32;
        uint8 Hex_prikey[32] = {0};
        uint8 Hex_inputRand[32] = {0};
        uint8 Hex_publicKey[64] = {0};
        inputMsg = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123";
        char *priKey = "2C9F3E0B9382C501CC07229F52CBB1C8F0C337B74A3D8FF843DC505AC65B940F";
        char *inputRand= "A756FBE87979B22AEC10BDC3D2E96792D7E0671D4CA089FA28E939EA7D3C791D";
        StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        StringToHex(priKey,Hex_prikey,&ByteNum);   
        StringToHex(inputRand,Hex_inputRand,&ByteNum); 
        ce_ecc_sign(Hex_inputMsg, ouputMsg, blen, Hex_inputRand, Hex_prikey, pkaMode);

    #elif defined ECC_VERIFY
        uint8  ouputMsg[512] = {0};
        uint32 blen = 32;
        uint8 Hex_pubkey[64] = {0};
        uint8 Hex_signature[64] = {0};
        char *signature = "D9363697BFF98DBB5815BBE6363809E1157E32CEEA7D04855EC322F60E9C7C19B54CABF4DDF0E92A983434BADE1483736091B7C9BA32F6ADAB85C6F5EF4E2413";
        inputMsg = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123";
        char *pubkey = "4AEDEECB75171A00AAEED60058046F46E1B7D2A2A0DBF44D5C1BF16E62A2DCFCD167750F85D38CB69C9A16EA40DC9047979A8A1CC4195FC8B7036034A0CF586F";
        StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        StringToHex(pubkey,Hex_pubkey,&ByteNum);   
        StringToHex(signature,Hex_signature,&ByteNum);   
        ce_ecc_verify(Hex_inputMsg, Hex_signature, blen, Hex_pubkey,pkaMode);

    #elif defined SM2_ENC
        uint8  ouputMsg[512] = {0};
        uint32 blen = 32;
        uint8 Hex_prikey[32] = {0};
        uint8 Hex_inputRand[32] = {0};
        uint8 Hex_publicKey[64] = {0};
        inputMsg = "3CE5822177BB79980F1475544570735CE3004BA72C78D3D36F50F97580390C0D";
        char *inputRand= "5059E86F879F5C90DDC7106D9C1F9982E6EE06413C64DDE7A6614FB813AABACA";
        char *publicKey = "4D2DB4B89F698DA02284E93F26C846C3AD8AB2EA2E1734BFF8FD2F754A09955D"
                          "6D87184AD36E11C21AF86973961A8EF35110F3EDC5604EB2144D5C9B912FA25F";
        StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        StringToHex(inputRand,Hex_inputRand,&ByteNum);
        StringToHex(publicKey,Hex_publicKey,&ByteNum);    
        ce_sm2_enc(Hex_inputMsg, ouputMsg, blen, Hex_inputRand, Hex_publicKey);

    #elif  defined SM2_DEC
        uint8  ouputMsg[512] = {0};
        uint32 blen = 128;
        uint8 Hex_prikey[32] = {0};
        uint8 Hex_inputRand[32] = {0};
        uint8 Hex_publicKey[64] = {0};
        inputMsg = "199EE8398DEB5B684C241AC38722BF73D38ABBD14CA4039A036D392AF357EBDD11D2EF8F1B0DD687055F86707F6522C0E4DC79E6732983EE8D47DBFBB59E024D74BC93EEFAB9AADA8789A9D870CEEB6D39743984DDEE335D1D755C79F2DF03249BB23D4D8A2D409B8483CEC942248AC2477FCE192B8DC288390DC2888E694EC4";
        char *priKey = "7127C5EF0C2284A1C050CDDCECF468F19D0A8262AC4D67CBA103B0CA9F95D3C4";
        StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        StringToHex(priKey,Hex_prikey,&ByteNum);    
        ce_sm2_dec(Hex_inputMsg, ouputMsg, blen, Hex_prikey);
    #elif  defined SM2_SIGNATURE
        uint8  ouputMsg[512] = {0};
        uint32 blen = 32;
        uint8 Hex_prikey[32] = {0};
        uint8 Hex_inputRand[32] = {0};
        uint8 Hex_publicKey[32] = {0};
        inputMsg = "3CE5822177BB79980F1475544570735CE3004BA72C78D3D36F50F97580390C0D";
        char *priKey = "7127C5EF0C2284A1C050CDDCECF468F19D0A8262AC4D67CBA103B0CA9F95D3C4";
        char *inputRand= "B26F455A308830907555C9F0F041BEDDA4F4B419CD284A99841DC76981A1E32B";
        StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        StringToHex(priKey,Hex_prikey,&ByteNum);   
        StringToHex(inputRand,Hex_inputRand,&ByteNum); 
        ce_sm2_sign(Hex_inputMsg, NULL,ouputMsg, blen, Hex_inputRand, Hex_prikey);

    #elif defined SM2_VERIFY
        uint8  ouputMsg[512] = {0};
        uint32 blen = 32;
        uint8 Hex_pubkey[64] = {0};
        uint8 Hex_signature[64] = {0};
        char *signature = "854FEB1A1132A5A1E9EDD812AE53C59C4F0058561F38D00666ED61D5FE01457E6BE9ACA2758AF064BA2E27D0DC5453DD377351713C5359B15F442773F62F43F4";
        inputMsg = "3CE5822177BB79980F1475544570735CE3004BA72C78D3D36F50F97580390C0D";
        char *pubkey = "4D2DB4B89F698DA02284E93F26C846C3AD8AB2EA2E1734BFF8FD2F754A09955D6D87184AD36E11C21AF86973961A8EF35110F3EDC5604EB2144D5C9B912FA25F";
        StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        StringToHex(pubkey,Hex_pubkey,&ByteNum);   
        StringToHex(signature,Hex_signature,&ByteNum);   
        ce_sm2_verify(Hex_inputMsg,NULL,Hex_signature, blen, Hex_pubkey);

    #else
        // uint32 blen = 256;
        // uint8  ouputMsg[512] = {0};
        // inputMsg = "0CB4393DD6169BD5887934560696034AEE81CDCA566FCD8932F97A57439FFB14CA0E9C5212A4DCDD29323F962ACB0A2867EFD96EF1E9BBE00E3AC82A329DA7B3A4089D49A04A949CB27160B6B555C8BFC09E7A7CB4BD72D260914093BE32F98F1DDE5A0831AE68360B7498E6B547EAE18F8FF99ACA2DA74437470A9325A8CE0EF2D3377BBD63782773B1762A29B59BBF0AD94F0F1BFC2974254948672579C12530E5277FC18F9F26F30044106CE675F1CEEBDFD4FA65C1D1749E060D426428F8909430F1A50B2DA7C2C3159BCEBECF87ACA64C252FF98D5E787B26DB429A727051F1E6520E18A18E04F35A4069547469BAA3D41B1608FE1CB5B8FD6BCF5455C6";
        // StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        // ce_secureboot_dec(Hex_inputMsg,ouputMsg,blen);
    #endif
    

    #if 1
    uint32 cnt ,rand_i ,err_cnt = 0;
    uint32 blen = 32;
    uint32 num1 = 0,num2 =0;
    uint8 Hex_prikey[96] = {0};
    uint8 Hex_inputRand[96] = {0};
    uint8 Hex_publicKey[96] = {0};

    #if (TestMode == 1)
    uint8 inputRand[32] = {0};
    uint8 random[32] ={0};
    uint8 prikey[32] ={0};
    uint8 pubkey[64] ={0};
    uint8 test_sign[64] = {0};
    #elif (TestMode == 2)
    uint8 inputRand[96] = {0};
    uint8 random[96] ={0};
    uint8 prikey[96] ={0};
    uint8 pubkey[96] ={0};
    uint8 test_sign[96] = {0};
    #else
    uint8 *random  = (uint8*)malloc(64);
    uint8 *prikey  = (uint8*)malloc(64);
    uint8 *pubkey  = (uint8*)malloc(64);
    uint8 *inputRand  = (uint8*)malloc(64);
    uint8 *test_sign  = (uint8*)malloc(64);
    #endif

    secbt.publicKeyHash = (uint8*)malloc(48);
    if(secbt.publicKeyHash == NULL)
        return ceMemAllocErr;
    secbt.rootKey = (uint8*)malloc(48);
        if(secbt.rootKey == NULL)
        return ceMemAllocErr;
    secbt.userConfig = (uint8*)malloc(48);
        if(secbt.userConfig == NULL)
        return ceMemAllocErr;

    #if (TestMode == 1)
    uint8 sb_pubkey[64] = {0};
    uint8 sb_prikey[32] = {0};
    uint8 sb_random[32] = {0};
    uint8 sb_userConfig[32] = {0};
    uint8 sb_rootkey[32] = {0};
    uint8 sb_pubHash[32]= {0};
    uint32 sha2_Mode = HASH_CFG_256_MODE|HASH_FINAL_PART(1)|HASH_SHA2_MODE;
    uint32 sb_pkaMode = pka256bForEcc;
    pkaMode = pka256bForEcc ;
    #elif (TestMode == 2)
    uint8 sb_pubkey[96] = {0};
    uint8 sb_prikey[96] = {0};
    uint8 sb_random[96] = {0};
    uint8 sb_userConfig[32] = {0};
    uint8 sb_rootkey[32] = {0};
    uint8 sb_pubHash[32]= {0};
    uint32 sha2_Mode = HASH_CFG_384_MODE|HASH_FINAL_PART(1)|HASH_SHA2_MODE;
    uint32 sb_pkaMode = pka384bForEcc;
    pkaMode = pka384bForEcc ;
    #elif 
    uint8  *sb_pubkey = (uint8*)malloc(64);
    uint8  *sb_prikey = (uint8*)malloc(64);
    uint8  *sb_random = (uint8*)malloc(64);
    uint8  *sb_userConfig = (uint8*)malloc(64);
    uint8  *sb_rootkey = (uint8*)malloc(64);
    uint8  *sb_pubHash = (uint8*)malloc(64);
    #endif


    for(cnt = 0;cnt < 500;cnt++)
    {
        srand((unsigned)time(NULL));
        uint32 len_rand = rand()%1001;
        if(len_rand == 0)
        		continue;
        uint8  *test_inputMsg = (uint8*)malloc(len_rand+16);
        #if (TestMode == 1)
            uint8  *EncMsg = (uint8*)malloc(len_rand+96+16);
        #else
            uint8  *EncMsg = (uint8*)malloc(len_rand+144+16);
        #endif
        uint8  *DecMsg = (uint8*)malloc(len_rand+16);
        if(test_inputMsg == NULL)
            return ceMemAllocErr;
        if(EncMsg == NULL)
            return ceMemAllocErr;
        if(DecMsg == NULL)
            return ceMemAllocErr;
        memset(test_inputMsg,0,len_rand+16);
        #if (TestMode == 1)
            memset(EncMsg,0,len_rand+96+16);
        #else
            memset(EncMsg,0,len_rand+144+16);
        #endif
        memset(DecMsg,0,len_rand+16);
        uint32 sb_sts = 0;
        uint32 byte_len = 32;
        for(rand_i = 0;rand_i< byte_len;rand_i++)
        {
            inputRand[rand_i] = rand()%256;
        }
        //ce_rng_gen(inputRand,32);  
        for(rand_i = 0;rand_i<len_rand;rand_i++)
        {
            test_inputMsg[rand_i] = rand()%256;
        }

        // inputMsg = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123";
        // char *inputRand= "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01";
        // char *priKey = "2C9F3E0B9382C501CC07229F52CBB1C8F0C337B74A3D8FF843DC505AC65B940F";
        // char *publicKey = "4AEDEECB75171A00AAEED60058046F46E1B7D2A2A0DBF44D5C1BF16E62A2DCFC"
        //                  "D167750F85D38CB69C9A16EA40DC9047979A8A1CC4195FC8B7036034A0CF586F";
        //StringToHex(inputMsg,Hex_inputMsg,&ByteNum);
        //StringToHex(inputRand,Hex_inputRand,&ByteNum);
        // StringToHex(publicKey,Hex_publicKey,&ByteNum);   
        // StringToHex(priKey,Hex_prikey,&ByteNum);    

        #define ecc_enc_dec_sig_verify
        #ifdef ecc_enc_dec_sig_verify
            if(sb_sts = ce_ecc_genkey(random,pubkey,prikey,pkaMode))
                err_cnt++;
            if(ce_ecc_enc(test_inputMsg, EncMsg, len_rand, inputRand, pubkey,pkaMode))   // in function,we modify input/random/pub to little
                err_cnt++;
            if ((len_rand % 16) == 0)
            {
                num1 = 16;
                len_rand += num1;
            }
            else
            {
                num1 = 16 - (len_rand % 16) ;
                len_rand += num1;
            }
            if(sb_sts = ce_ecc_dec(EncMsg, DecMsg, (len_rand+byte_len*3), prikey, pkaMode))// in function,we modify prikey to little
                err_cnt++;
            big2little(test_inputMsg,len_rand,16); //l2b & len_rand is after padding 
            if(compareBN(test_inputMsg,DecMsg,len_rand-num1))
                err_cnt++;
            big2little(inputRand,byte_len,byte_len);
            big2little(pubkey,byte_len*2,byte_len);
            big2little(prikey,byte_len,byte_len);
            // big2little(Hex_publicKey,64,32);
            // big2little(Hex_prikey,32,32);
            //ce_ecc_sign(test_inputMsg, test_sign,  (len_rand), inputRand, prikey,pkaMode); //in function,we don't modify input
            //if(sb_sts = ce_ecc_verify(test_inputMsg, test_sign, (len_rand), pubkey, pkaMode))
            if(ce_ecc_sign(test_inputMsg, test_sign,  (len_rand-num1), inputRand, prikey,pkaMode))//in function,we don't modify input
                err_cnt++;
            if(sb_sts = ce_ecc_verify(test_inputMsg, test_sign, (len_rand-num1), pubkey, pkaMode))
                err_cnt++;
        #endif

        #ifdef sm2_enc_dec_sig_verify
        if(sb_sts = ce_sm2_genkey(random,pubkey,prikey))
        	err_cnt++;
        ce_sm2_enc(test_inputMsg, EncMsg, len_rand, inputRand, pubkey);   // in function,we modify input/random/pub to little
        if(sb_sts = ce_sm2_dec(EncMsg, DecMsg, (len_rand+byte_len*2), prikey))// in function,we modify prikey to little
        {
            err_cnt++;
        }
        if(compareBN(test_inputMsg,DecMsg,len_rand))
        {
            err_cnt++;
        }
        big2little(inputRand,32,32);
        big2little(pubkey,64,32);
        big2little(prikey,32,32);
        // big2little(Hex_publicKey,64,32);
        // big2little(Hex_prikey,32,32);
        ce_sm2_sign(test_inputMsg,NULL, test_sign,  (len_rand), inputRand, prikey); //in function,we don't modify input
        if(sb_sts = ce_sm2_verify(test_inputMsg,NULL, test_sign, (len_rand), pubkey))
        {
            err_cnt++;
        }
        // free(inputRand);
        // free(random);        
        // free(test_sign);
        // free(pubkey);
        // free(prikey);
        #endif

        #define secureboot
        #ifdef secureboot
            #ifdef ecc_enc_dec_sig_verify
                len_rand -= num1;
            #endif
        if (((len_rand + 32 * 2 + 2) % 16) == 0)
        {   
            num2 = 16;
            len_rand += num2;
        }
        else
        {
            num2 = 16 - (len_rand + 32 * 2 + 2) % 16;
            len_rand += num2;
        }

        // big2little(inputRand,32,32);
        // big2little(Hex_publicKey,64,32);
        // big2little(Hex_prikey,32,32);

        uint8  *secbt_msg = (uint8*)malloc(len_rand+130);
        uint8  *secbt_org = (uint8*)malloc(len_rand+130); //+66
        if(secbt_msg == NULL)
            return ceMemAllocErr;
        if(secbt_org == NULL)
            return ceMemAllocErr;

        //uint32 ByteNum = 0;
        // //char* str_pubKeyHash = "EB4D0C604D8BC68A4A1B11E0CFD5FD5E27924B26928E4FC98FD282965A6E3EE3";  //nist
        // //char* str_pubKeyHash = "CC439B4719B82DF96806AC5195AD5D62E78D8269782A5E96DAAA16A8460A971E";     //sm2
        //char* str_rootKey =    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01";
        //char* str_userConfig = "EEA2AA8CB8378BB5F616998578B645690C637D3B67917A80882A11425B2E67FF";
        //StringToHex(str_pubKeyHash,(uint8*)secbt.publicKeyHash,&ByteNum);
        //StringToHex(str_rootKey,(uint8*)secbt.rootKey,&ByteNum);
        //StringToHex(str_userConfig,(uint8*)secbt.userConfig,&ByteNum);
        ce_rng_gen(sb_userConfig,32);   //max4096 Byte
        ce_rng_gen(sb_rootkey,32);     
        #if 1
        ce_ecc_genkey(sb_random,sb_pubkey,sb_prikey,sb_pkaMode);
        ce_sha2(sb_pubkey,sb_pubHash,64,sha2_Mode);
        big2little(sb_pubHash,32,4); //l2b
        secbt.bootImgVer  =        32;
        secbt.bootSym     =         0;
        secbt.bootAsym    =         0;
        secbt.bootHashSel =         0;
        #else
        ce_sm2_genkey(sb_random,sb_pubkey,sb_prikey);
        ce_SM3(sb_pubkey,sb_pubHash,64);
        big2little(sb_pubHash,32,4); //l2b
        secbt.bootImgVer  =        32;
        secbt.bootSym     =         1;
        secbt.bootAsym    =         1;
        secbt.bootHashSel =         1;
        #endif

        secbt.rootKey = sb_rootkey;
        secbt.userConfig = sb_userConfig;
        secbt.publicKeyHash = sb_pubHash;

        #if 0
        ce_secureboot_gen(Hex_inputMsg, secbt_msg, 32, sb_prikey, sb_pubkey,sb_pkaMode);
        uint32 len_rand_bt = len_rand-num2;
        ce_secureboot_gen(test_inputMsg, secbt_msg, len_rand_bt, Hex_prikey, Hex_publicKey,1);
        #endif
        #if 1
        ce_secureboot_gen(test_inputMsg, secbt_msg, (len_rand-num2), sb_prikey, sb_pubkey,sb_pkaMode);
        #endif
        if(sb_sts = ce_secureboot_dec(secbt_msg,secbt_org,len_rand+130))
        {
            err_cnt++;
        }
        if(compareBN(test_inputMsg,secbt_org,len_rand-num2))
        {
            err_cnt++;
        }
        free(secbt_msg);
        free(secbt_org);
        #endif


        free(test_inputMsg);
        free(EncMsg);
        free(DecMsg);

		#if 0
        uint8 *secboot_dec_input = (uint8*)calloc(1000,1);
        uint8 *secboot_dec_output = (uint8*)calloc(1000,1);

        #if 0
        char* secboot_dec_char = "D94453587341FB85B9C43753780CAD5063C3BDF85EE6B4963B680EFEA5E582825479779C092BC21CCB8CF9ABF5F1CB784755AB328021D229F1404216715AF408429778485AB59F77EFD8006C29C144691AEF8DCDCB51DB2E9A34FF844C3C9FC2A9F8E54CC204B6BE07EEB1A9D92D488AE2E55F618D750BD5060A14738AADFFED25AB75A0B7031C6C3BF715D00729EF4934D947801276793577DCA25DCC9B090B38F40146C65067C552B5663AAE9704FBAFD864C7BC54D9E104A341DBCC36937888C757254DD28F3C5C5E5BB5CB5EE778B052175D60DB895F34A36B8F5176A14C974E718CC6E25F4277FD2C638AC1A5B0804B3974B3E6FCAB7A49008F02173BEB";
        char* str_pubKeyHash = "EB4D0C604D8BC68A4A1B11E0CFD5FD5E27924B26928E4FC98FD282965A6E3EE3";     //nist
        secbt.bootImgVer  =        32;
        secbt.bootSym     =         0;
        secbt.bootAsym    =         0;
        secbt.bootHashSel =         0;
        #else
        char* secboot_dec_char = "A5545C0477A848049FE08602872643964F661C42B87B44D90F8F71E29C8E2CF2BE910B0EC6A924B6CF4873A32D399C93CB5AFF9077EC8CADB2A33B12364C6B443D40761E8001B9241AB77F1B423EF1E40171DEEBD01F242843D02A3CDED8B39F47070BE881C8CC055AA1881C4C7B23F8B376A2CB58E8C38C74EEB832FAFA27D6653A01992BAA6BBD4041C3BAEF1B50BFB827AF9A8B688D9F65FB0557A044172DA8E6847C83FA9965342F37276B6C45DB8411B5652CEC267B5752DEF855AD12C9978A16E7A91ED87B1F27785E8DCC1ACF61E91527C18AE7D9721230D61F6FD2816B2A5D9E7C88F112671144B1D54D24EA59FD9EA0D04C285581A49EA0BDF4DE68";
        char* str_pubKeyHash = "CC439B4719B82DF96806AC5195AD5D62E78D8269782A5E96DAAA16A8460A971E";     //sm2
        secbt.bootImgVer  =        64;
        secbt.bootSym     =         1;
        secbt.bootAsym    =         1;
        secbt.bootHashSel =         1;
        #endif
        
        char* str_rootKey =    "BBDDD05D270A7610F0E43CC5999183F23ECC5EB70623FE3116C52D0864864C01";
        char* str_userConfig = "EEA2AA8CB8378BB5F616998578B645690C637D3B67917A80882A11425B2E67FF";
        
        StringToHex(str_pubKeyHash,(uint8*)secbt.publicKeyHash,&ByteNum);
        StringToHex(str_rootKey,(uint8*)secbt.rootKey,&ByteNum);
        StringToHex(str_userConfig,(uint8*)secbt.userConfig,&ByteNum);

        StringToHex(secboot_dec_char,secboot_dec_input,&ByteNum);
        
        ce_secureboot_dec(secboot_dec_input,secboot_dec_output,ByteNum);

        #endif
      }
      free(secbt.publicKeyHash);
      free(secbt.rootKey);
      free(secbt.userConfig);
      
      #if 0
      free(sb_pubkey);
      free(sb_prikey);
      free(sb_random);
      free(sb_userConfig);
      free(sb_rootkey);
      free(sb_pubHash);
      #endif
    #endif
}
#endif

#define uart_115200bps  (u32)115200

void test_uart_com()
{
    struct uart_device uart_debug_msg;
    struct uart_device *uart_debug = &uart_debug_msg;

    uart_debug->preg = (SV100_UART*)SV100_UART0_BASE;

    uart_init(uart_debug,uart_115200bps);
    uint8 str1[3] = {0x10,0x20,0x30};
    char str2[3]={0,0,0};
    HextoString(str1,str2,3);
    uint32 rec_data = 0;
    while(1)
    {   
        #if 0
        uart_puts("\n Hello, I am UART0...\r\n");
        //uart_puts(str1);
        uart_puts(str2);
        //printf("UART0 = %.3f\t UART1= %1.3fV\r\n",10.3,"adcdEF");
        //printf("AdcIn= %1.3fV\r\n",10.1);
        mcu_delay(10000);
        #else
        rec_data = uart_receive();
		#endif
	}

}

void mcu_delay(uint32 cnt)
{
    while(cnt--);
}

int HextoString(uint8* str, char* out, uint32* outlen)
{
        char ddl, ddh;
        int i;
        int blen = strlen((char*)str);
        for (i = 0; i < blen; i++)
        {
            ddh = 48 + str[i] / 16;
            ddl = 48 + str[i] % 16;
            if (ddh > 57) ddh = ddh + 7;
            if (ddl > 57) ddl = ddl + 7;
            out[i * 2] = ddh;
            out[i * 2 + 1] = ddl;
        }
        return 1;
}

#define __DEBUG__UART__
int main(int argc, char **argv)
{   
    // uint32 num = 0;
    // uint8 test_array[25] = {0x64, 0x21, 0x05, 0x19, 0xe5, 0x9c, 0x80, 0xe7, 0x0f, 0xa7, 0xe9, 0xab, 0x72, 0x24, 0x30, 0x49, 0xfe, 0xb8, 0xde, 0xec, 0xc1, 0x46, 0xb9,0x12,0x34};

    
    // uint8 test_dst[100] = {0};
    // for(num = 0;num<100;num++)
    // {
    //     test_dst[num] = 0x00;
    // }
    //memcpy((test_dst+0x0f),test_array,25);

    //(*((uint32*)0x300ffc11)) = 0x12345678;

    // uint32 test_data = 0x12345678;
    // uint32 test_data1 = 0x55aa66bb;
    // uint32 *p32 = &test_data;
    // uint8 *p8 = &test_data1;

    // test_dst[1] = (uint8)(*(p32+1));
    // test_dst[5] = *((uint8*)p32+1);
    // test_dst[16] = (*(uint8*)(p32+1));
    //memcpy(test_dst,(uint8*)p32,8);

    #ifdef  __DEBUG__ECC__
	test_ecc_simple();
    #endif



	#ifdef  __DEBUG__UART__
    //test_uart_com();
    #endif
    
    //ce_ecc_enc(uint8 *input, uint8 *output, uint32 blen, uint8 *random, uint8 *pubkey,cedarPkaMode_t pkaMode);
	printf("Hello World");

	return 0;
}





