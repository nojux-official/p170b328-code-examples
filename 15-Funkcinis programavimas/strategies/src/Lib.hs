module Lib
    ( someFunc,
    ) where

import           Control.Parallel.Strategies
import           Data.ByteString.Lazy.UTF8   as BLU
import           Data.Digest.Pure.MD5


someFunc :: IO ()
someFunc = do
  let numbers = getData
  let md5Hashes = map md5 numbers `using` parListChunk 100000 rpar
  print (maximum md5Hashes)


getData :: [ByteString]
getData =
  map BLU.fromString numbersAsStrings where
    numbers = [1..1000000]
    numbersAsStrings = map show numbers
