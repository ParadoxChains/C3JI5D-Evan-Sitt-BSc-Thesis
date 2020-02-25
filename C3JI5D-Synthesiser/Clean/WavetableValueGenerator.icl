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

instance toString ({#Char},[Real])
where
    toString (wavName,arr) = returnString
    where
        typeString = "double "
        sizeString = "[" +++ toString (length arr) +++ "]"
        equals = " = "
        valuesStringList = [toString (arr!!0) :[", " +++ toString (arr!!(index-1)) \\index<-[2..(length arr)]]]
        valuesString = foldr (+++) "" valuesStringList
        returnString = typeString +++ wavName +++ sizeString +++ equals +++ "{" +++ valuesString +++ "};\n"

// TestArr :: {Real}
// TestArr = {1.34,2.63,3.535,4.663}
// Start = toString ("Test",TestArr)
sumParallel :: [Real] [Real] -> [Real]
sumParallel x y = [a+b\\a<-x & b<-y]

sineList :: [Real]
sineList = [sin theta\\ theta <- [0.0, delta_Theta..(2.0*PI)] | theta < 2.0*PI ]

sineTuple :: ({#Char},[Real])
sineTuple = ("sineWaveTable",sineList)


Start = toString sineTuple