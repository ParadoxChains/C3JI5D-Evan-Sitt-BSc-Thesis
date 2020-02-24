module WavetableValueGenerator
import StdEnv

/*
Constants
*/
PI :: Real
PI = acos -1.0

MAX_SAMPLING_RATE :: Int
MAX_SAMPLING_RATE = 96000

LOWEST_AUDIBLE_THRESHOLD :: Real
LOWEST_AUDIBLE_THRESHOLD = 20.0

HIGHEST_AUDIBLE_CEILING :: Real
HIGHEST_AUDIBLE_CEILING = 20000.0

delta_Theta :: Real
delta_Theta = 2.0 * PI / (toReal(MAX_SAMPLING_RATE)/LOWEST_AUDIBLE_THRESHOLD)

//End constants

instance toString ({#Char}, a Real) | Array a Real
where
    toString (wavName,arr) = returnString
    where
        typeString = "float "
        sizeString = "[" +++ toString (size arr) +++ "]"
        equals = " = "
        valuesStringList = [toString arr.[0]:[", " +++ toString arr.[index-1] +++ "f"\\index<-[2..(size arr)]]]
        valuesString = foldr (+++) "" valuesStringList
        returnString = wavName +++ sizeString +++ equals +++ "{" +++ valuesString +++ "};\n"

TestArr :: {Real}
TestArr = {1.34,2.63,3.535,4.663}
Start = toString ("Test",TestArr)