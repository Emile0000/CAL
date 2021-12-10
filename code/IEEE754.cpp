#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std ;
typedef char Str40[40] ;

void FractionStrAnalysis( Str40 floatStr, bool &nonNegative, int &decimal, int&intOfFraction, int &numDigits ) {
    int a = 0, b = 0, arr[40] = {0} ;
    int c = 0, pon = 0 ; // positive(0) or negative(1)

    if ( floatStr[0] == '-' ) {
        nonNegative = false ;
        pon = 1 ;
    } // if

    if ( pon == 0 ) { // > 0
        while ( floatStr[a] != '.' && floatStr[a] != '\0' ) { // decimal
            arr[a] = floatStr[a] - '0' ;
            decimal = decimal * 10 + arr[a] ;
            a++ ;
        } // while

        b = a + 1 ; // b = 整數部分位數+1('.')
        a+=1;
        while ( a < strlen( floatStr ) ) {
            arr[a] = floatStr[a] - '0' ;
            intOfFraction = intOfFraction * 10 + arr[a] ;
            a++ ;
        } // while

        numDigits = strlen( floatStr ) - b ;
    } // if
    else { // < 0
        a = 1 ;
        while ( floatStr[a] != '.' && floatStr[a] != '\0' ) { // decimal
            arr[a] = floatStr[a] - '0' ;
            decimal = decimal * 10 + arr[a] ;
            a++ ;
        } // while

        b = a + 1 ; // b = 整數部分位數+1('.')
        a+=1;
        while ( a < strlen( floatStr ) ) {
            arr[a] = floatStr[a] - '0' ;
            intOfFraction = intOfFraction * 10 + arr[a] ;
            a++ ;
        } // while

        numDigits = strlen( floatStr ) - b ;
    } // else
} // function1:FractionStrAnalysis()

void DecimalToBinary( int decimal, Str40 &binary ) {
    int time = 0, temp[10] = {0} ;
    while ( decimal / 2 != 0 ) {
        temp[time] = decimal % 2 ;
        decimal = decimal / 2 ;
        time++ ;
    } // while
    
    temp[time] = decimal % 2 ;
    int a = time ;
    for ( int b = 0 ; b <= time ; b++ ) {
        binary[a] = temp[b] + '0' ;
        a-- ;
    } // for
} // function2:DecimalToBinary()

void FractionToBinary( int inputNum, int numOfInputDigits, Str40 &outputNum ) {
    float num = 1, k = 0.5 ;
    int j = 0 ;
    num = inputNum ;
    while ( numOfInputDigits > 0 ) {
        num = num / 10 ;
        numOfInputDigits-- ;
    } // while
    
    while ( num > 0 && j < 10 ) {
        if ( num >= k ) {
            num -= k ;
            outputNum[j] = '1' ;
        }
        else outputNum[j] = '0' ;
        k /= 2 ;
        j++ ;
    } // while
} // function3:FractionToBinary()

void FindMantissaExponent( Str40 &inputDecimal, Str40 &inputFraction, Str40 &mantissa, int &exponent ) {
    int a = 0, b = 0 ;
    if ( inputDecimal[0] == '0' ) {
        exponent = -1 ;
        while ( inputFraction[b] == '0' ) {
            exponent-- ;
            b++ ;
        } // while
    } // if
    else exponent = strlen( inputDecimal ) - 1 ;

    int c = 0, d = 0, e = 0 ;
    if ( exponent >= 0 ) {
        
        for ( c = 1 ; c < strlen( inputDecimal ) ; c++ ) {
            mantissa[d] = inputDecimal[c] ;
            d++ ;
        } // for
        
        for ( e = 0 ; e < strlen( inputFraction ) ; e++ ) {
            mantissa[d] = inputFraction[e] ;
            d++ ;
        } // for
        
        while ( d < 23 ) {
            mantissa[d] = '0' ;
            d++ ;
        } // while
        
    } // if
    else {
        
        while ( inputFraction[c] == '0' ) c++ ;
        c++;
        
        for ( e = c ; e < strlen ( inputFraction ) ; e++ ) {
            mantissa[a] = inputFraction[e];
            a++;
        } // for
        
        while ( a < 23 ) {
            mantissa[a] = '0' ;
            a++ ;
        } // while
        
    } // else
} // function4:FinaMantissaExponent

void DecimalToExcess127( int exponent, Str40 &temp_excess127 ) {
    int kksk = 0, mac[8] = {0} ;
    exponent = exponent + 127 ;
    int a = 0, b = 0, c = 0 ;
    
    while ( exponent / 2 != 0 ) {
        kksk = exponent % 2 ;
        mac[a] = kksk ;
        exponent = exponent / 2 ;
        a++ ;
    } // while
    
    mac[a] = exponent % 2 ;
    b = 7 - a ;
    while ( b > 0 ) {
        temp_excess127[c] = '0' ;
        c++ ;
        b-- ;
    } // while
    
    while ( a >= 0 ) {
        temp_excess127[c] = mac[a] + '0' ;
        c++ ;
        a-- ;
    } // while
} // function5:DecimalToExcess127

int main() {

    Str40 inputString = "" ;
    bool sign = true ;
    int decimal = 0 ;
    int intOfFraction = 0 ;
    int numDigits = 0 ;
    Str40 binary_decimal = "" ;
    Str40 binary_fraction = "" ;
    Str40 binary_mantissa = "" ;
    int exp = 0 ;
    Str40 temp_excess127 = "" ;
    Str40 binary_excess127 = "" ;
    
    cin >> inputString ;
    
    FractionStrAnalysis( inputString, sign, decimal, intOfFraction, numDigits ) ;
    DecimalToBinary( decimal, binary_decimal ) ;
    FractionToBinary( intOfFraction, numDigits, binary_fraction ) ;
    FindMantissaExponent( binary_decimal, binary_fraction, binary_mantissa, exp ) ;
    DecimalToExcess127( exp, temp_excess127 ) ;
    
    int count = 0 ;
    for ( count = 0 ; count < 8 - strlen( temp_excess127 ) ; count++ ) binary_excess127[count] = '0' ;
    strcat( binary_excess127, temp_excess127 ) ;

    if ( strcmp( inputString, "0" ) == 0 || strcmp( inputString, "0.0" ) == 0.0 ) cout << "0 00000000 00000000000000000000000";
    else {
        if ( sign ) cout << "0" << " " << binary_excess127 << " " << binary_mantissa ;
        else cout << "1" << " " << binary_excess127 << " " << binary_mantissa ;
    } // else
    
    return 0 ;
} // main()
