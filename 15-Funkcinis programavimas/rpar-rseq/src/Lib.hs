module Lib
    ( someFunc
    ) where

import           Control.Parallel.Strategies

someFunc :: IO ()
someFunc = do
  let (sum1, sum2) = getParallelSums [1..100000000] [100000000..200000000]
  let fullSum = sum1 + sum2
  print fullSum

getSquaredSum :: [Int] -> Int
getSquaredSum items =
  sum squares where
    squares = map (\x -> x * x) items


getParallelSums :: [Int] -> [Int] -> (Int, Int)
getParallelSums list1 list2 =
  runEval $ do
    sum1 <- rpar (getSquaredSum list1)
    sum2 <- rpar (getSquaredSum list2)
    seqSum1 <- rseq sum1
    seqSum2 <- rseq sum2
    return (seqSum1, seqSum2)
